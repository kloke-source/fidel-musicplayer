#include <Audio/playback.h>
#include <string.h>
#include <iostream>
#include <gst/gst.h>
#include <GUI/gui.h>
#include <vector>
//#include <Spectrum/spectrum.h>
#include <Audio-Info/audioinfo.h>

#define AUDIOFREQ 44800

int spect_bands = 250;
bool idle=true;
bool stream_killed = true;
bool playing=false;
bool duration_obtained;

GMainLoop *loop;

GstFormat fmt = GST_FORMAT_TIME;
gint64 duration;

std::vector<double> band_magnitudes;
std::vector<double> phase_shifts;

//prototypes
void query_duration();
//end

playback::playback()
{
  for (size_t iter = 0; iter < spect_bands; iter++) {
    band_magnitudes.push_back(-80);
    phase_shifts.push_back(0);
  }
}

static gboolean
bus_cb (GstBus     *bus __attribute__((unused)),
	GstMessage *message __attribute__((unused)),
	gpointer    data __attribute__((unused)))
{
  if (message->type == GST_MESSAGE_EOS){
    g_main_loop_quit(loop);
  }
  if (message->type == GST_MESSAGE_ELEMENT) {
    const GstStructure *s = gst_message_get_structure (message);
    const gchar *name = gst_structure_get_name (s);
    GstClockTime endtime;

    if (duration_obtained == false){
      query_duration();
    }

    if (strcmp (name, "spectrum") == 0) {
      const GValue *magnitudes;
      const GValue *phases;
      const GValue *mag, *phase;
      gdouble freq __attribute__((unused));
      guint iter;

      if (!gst_structure_get_clock_time (s, "endtime", &endtime))
	endtime = GST_CLOCK_TIME_NONE;

      /*
	g_print ("New spectrum message, endtime %" GST_TIME_FORMAT "\n",
	GST_TIME_ARGS (endtime));
      */

      double seek_value = (double)endtime/1000000000;
      audio_playback::Instance()->update_pb_timer(seek_value);

      magnitudes = gst_structure_get_value (s, "magnitude");
      phases = gst_structure_get_value (s, "phase");

      for (iter = 0; iter < spect_bands; iter++) {
        freq = (gdouble) ((AUDIOFREQ / 2) * iter + AUDIOFREQ / 4) / spect_bands;

        mag = gst_value_list_get_value (magnitudes, iter);
        phase = gst_value_list_get_value (phases, iter);

        if (mag != NULL && phase != NULL) {
          gfloat magnitude = g_value_get_float(mag);
          gfloat phase_shift = g_value_get_float(phase);

          band_magnitudes[iter] = (double)magnitude;
          phase_shifts[iter] = (double)phase_shift;
        }
      }
      audio_playback::Instance()->notify_spect_bands_updated();
      g_print ("\n");
    }
  }
  return TRUE;
}

GstElement *pipeline, *audio;
GstCaps *subCaps;
static void setSubCaps(GstCaps  *cap){
  subCaps=cap;
}

static void
cb_newpad (GstElement *decodebin __attribute__((unused)),
	   GstPad     *pad,
	   gpointer    data __attribute__((unused)))
{
  GstCaps *caps;
  GstStructure *str;
  GstPad *audiopad;

  audiopad = gst_element_get_static_pad (audio, "sink");
  if (GST_PAD_IS_LINKED (audiopad)) {
    g_object_unref (audiopad);
    return;
  }

  caps = gst_pad_query_caps (pad, NULL);
  str = gst_caps_get_structure (caps, 0);
  setSubCaps(caps);
  if (!g_strrstr (gst_structure_get_name (str), "audio")) {
    gst_caps_unref (caps);
    gst_object_unref (audiopad);
    return;
  }
  gst_caps_unref (caps);

  gst_pad_link (pad, audiopad);

  g_object_unref (audiopad);
}

void playback::audio_file(char *filesrc)
{
  std::cout << "Inputted filesrc: "  << filesrc << std::endl;
  if (playback::is_playing() == true || stream_killed == false){
    playback::kill_curr_stream();
  }

  stream_killed = false;
  GstElement *src, *dec, *conv, *spectrum, *sink;
  GstPad *audiopad;
  GstBus *bus;

  duration_obtained=false;
  audioinfo::init(filesrc);
  m_signal_now_playing.emit(filesrc);
  
  audio_playback::Instance()->start_spectrum_visualization();

  gst_init (NULL, NULL);
  loop = g_main_loop_new (NULL, FALSE);

  pipeline = gst_pipeline_new ("pipeline");

  bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
  gst_bus_add_watch (bus, bus_cb, loop);
  gst_object_unref (bus);

  src = gst_element_factory_make ("filesrc", "source");
  g_object_set (G_OBJECT (src), "location", filesrc, NULL);
  dec = gst_element_factory_make ("decodebin", "decoder");
  g_signal_connect (dec, "pad-added", G_CALLBACK (cb_newpad), NULL);
  gst_bin_add_many (GST_BIN (pipeline), src, dec, NULL);
  gst_element_link (src, dec);

  audio = gst_bin_new ("audiobin");
  conv = gst_element_factory_make ("audioconvert", "aconv");
  g_assert (conv);
  spectrum = gst_element_factory_make ("spectrum", "spectrum");
  g_object_set (G_OBJECT (spectrum), "bands", spect_bands, "threshold", -80,
		"post-messages", TRUE, "message-phase", TRUE, NULL);

  audiopad = gst_element_get_static_pad (conv, "sink");
  sink = gst_element_factory_make ("alsasink", "sink");
  g_object_set (G_OBJECT (sink), "sync", TRUE, NULL);

  gst_bin_add_many (GST_BIN (audio), conv, spectrum, sink, NULL);

  gst_element_link_filtered(conv, spectrum, subCaps);
  gst_element_link(spectrum, sink);
  gst_caps_unref(subCaps);
  gst_element_add_pad (audio,
		       gst_ghost_pad_new ("sink", audiopad));
  gst_object_unref (audiopad);
  gst_bin_add (GST_BIN (pipeline), audio);
  idle=false;
  playback::change_playback_status(playback::IDLE);
  playback::play();
  g_main_loop_run (loop);
  playback::set_track_finished();
  playback::kill_audio();
}

void query_duration()
{
  duration_obtained = true;
  gint64 duration_nanoseconds;
  gst_element_query_duration (pipeline, GST_FORMAT_TIME, &duration_nanoseconds);
  double duration = ((double)duration_nanoseconds)/1000000000;

  std::cout << "Duration -> " << duration << std::endl;
  //std::cout << "Test tag dur -> " << audioinfo::tag_duration() << std::endl;

  if ((int)duration == audioinfo::tag_duration()){
    audioinfo::set_duration(duration);
    fidel_ui::Instance()->set_pb_endtime(duration);
  }
  if ((int)duration > audioinfo::tag_duration() && (int)duration >= 3600)
    {
      std::cout << "Duration > tag" << std::endl;
      audioinfo::set_duration_from_tag();
      fidel_ui::Instance()->set_pb_endtime(audioinfo::duration());
    }
  if (audioinfo::tag_duration() > (int)duration && audioinfo::tag_duration() >=3600)
    {
      std::cout << "tag > duration" << std::endl;
      audioinfo::set_duration(duration);
      fidel_ui::Instance()->set_pb_endtime(duration);
    }
  if ((int)duration == 0 || (int)duration < 0)
    {
      std::cout << "Duration == 0 || < 0" << std::endl;
      audioinfo::set_duration_from_tag();
      fidel_ui::Instance()->set_pb_endtime(audioinfo::duration());
    }
}

void playback::kill_curr_stream()
{
  if (idle==false){
    stream_killed = true;
    //idle=true;
    /*
      g_main_loop_quit(loop);
      gst_element_set_state (pipeline, GST_STATE_NULL);
    */
    // --(deprecated)-- fidel_ui::Instance()->delete_sidebar_data();
    //idle=true;
    g_main_loop_quit(loop);
    gst_element_set_state (pipeline, GST_STATE_NULL);
    gst_object_unref (GST_OBJECT(pipeline));
    gst_object_unref(GST_OBJECT(audio));
    //gst_object_unref (GST_OBJECT (audio));
    subCaps = NULL;
    duration_obtained = false;

    //gst_object_unref (GST_OBJECT (subCaps));


    //playback::kill_audio();
  }
}

void playback::kill_audio()
{
  if (idle==false){
    idle=true;
    g_main_loop_quit(loop);
    gst_element_set_state (pipeline, GST_STATE_NULL);
    gst_object_unref (GST_OBJECT (pipeline));
    g_main_loop_unref(loop);
  }
}

bool playback::idle_status()
{
  return idle;
}

bool playback::is_playing()
{
  return playing;
}

void playback::pause()
{
  if (idle == false){
    playing = false;
    playback::change_playback_status(playback::PAUSED);
    gst_element_set_state(pipeline, GST_STATE_PAUSED);
  }
}

void playback::play()
{
  if (idle == false){
    playing = true;
    playback::change_playback_status(playback::PLAYING);
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
  }
}

void playback::seek(double time, std::string sender)
{
  double seekvalue = time * 1000000000;
  if (sender == "seeker"){
    // --(deprecated)-- fidel_ui::Instance()->update_pb_timer(&time);
  }
  gst_element_seek (pipeline, 1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH,
		    GST_SEEK_TYPE_SET, seekvalue,
		    GST_SEEK_TYPE_NONE, GST_CLOCK_TIME_NONE);
}


//--- start of signal functions ---

playback::type_signal_now_playing playback::signal_now_playing()
{
  return m_signal_now_playing;
}

/* start of playback status signal functions */
playback::type_signal_status_changed playback::signal_status_changed()
{
  return m_signal_status_changed;
}

void playback::change_playback_status(int status)
{
  playback::m_signal_status_changed.emit(status);
}

/* start of spectrum start visualization signal functions */
playback::type_signal_start_spectrum playback::signal_spectrum_start()
{
  return m_signal_spectrum_start;
}

void playback::start_spectrum_visualization()
{
  playback::m_signal_spectrum_start.emit();
}

void playback::notify_spect_bands_updated()
{
  playback::m_signal_spect_bands_updated.emit(band_magnitudes);
}

playback::type_signal_spect_bands_updated playback::signal_spect_bands_updated()
{
  return m_signal_spect_bands_updated;
}
  
/* start of update playback slider position signal functions */
playback::type_signal_pb_timer_changed playback::signal_update_pb_timer()
{
  return m_signal_update_pb_timer;
}

void playback::update_pb_timer(double seek_value)
{
  playback::m_signal_update_pb_timer.emit(seek_value);
}

playback::type_signal_track_finished playback::signal_track_finished()
{
  return m_signal_track_finished;
}

void playback::set_track_finished()
{
  playback::m_signal_track_finished.emit();
}
