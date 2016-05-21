#include "playback.h"
#include <string.h>
#include <iostream>
#include <gst/gst.h>
#include <GUI/gui.h>
#include <Spectrum/spectrum.h>
#include <Audio-Info/audioinfo.h>

#define AUDIOFREQ 44100

using namespace std;
static guint spect_bands = 35;
bool idle=true;
bool stream_killed = true;
bool playing=false;
bool duration_obtained;

GMainLoop *loop;
playback::playback(){}

GstFormat fmt = GST_FORMAT_TIME;
gint64 duration;

//prototypes
void query_duration();
//end

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

      double seekvalue = (double)endtime/1000000000;
      // --(deprecated)-- fidel_ui::Instance()->update_pb_slider_pos(&seekvalue);

      magnitudes = gst_structure_get_value (s, "magnitude");
      phases = gst_structure_get_value (s, "phase");

      for (iter = 0; iter < spect_bands; iter++) {
        freq = (gdouble) ((AUDIOFREQ / 2) * iter + AUDIOFREQ / 4) / spect_bands;
        mag = gst_value_list_get_value (magnitudes, iter);
        phase = gst_value_list_get_value (phases, iter);

        if (mag != NULL && phase != NULL) {
          gfloat magnitude = g_value_get_float(mag);

          Spectrum::Instance()->setBandMagn(&iter, &magnitude);
          /*
          g_print ("band %d (freq %g): magnitude %f dB phase %f\n", i, freq,
          g_value_get_float (mag), g_value_get_float (phase));
          */
        }
      }
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
  cout << "Inputted filesrc: "  << filesrc << endl;
  if (playback::is_playing() == true || stream_killed == false){
    playback::kill_curr_stream();
  }
  stream_killed = false;
  GstElement *src, *dec, *conv, *spectrum, *sink;
  GstPad *audiopad;
  GstBus *bus;

  duration_obtained=false;
  audioinfo::init(filesrc);
  vector<Glib::ustring> song_data;
  song_data.push_back(audioinfo::get_info("song_name"));
  song_data.push_back(audioinfo::get_info("artist"));
  song_data.push_back(audioinfo::get_info("album"));
  // --(deprecated)-- fidel_ui::Instance()->set_sidebar_data(audioinfo::get_album_art(filesrc, 200, 200), song_data);

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
    playback::play();
    g_main_loop_run (loop);
  }

  void query_duration()
  {
    duration_obtained = true;
    gint64 duration_nanoseconds;
    gst_element_query_duration (pipeline, GST_FORMAT_TIME, &duration_nanoseconds);
    double duration = ((double)duration_nanoseconds)/1000000000;

    cout << "Duration -> " << duration << endl;
    cout << "Test tag dur -> " << audioinfo::tag_duration() << endl;

    if ((int)duration == audioinfo::tag_duration()){
      audioinfo::set_duration(duration);
      // --(deprecated)-- fidel_ui::Instance()->set_pb_slider_endtime(duration);
    }
    if ((int)duration > audioinfo::tag_duration() && (int)duration >= 3600)
    {
      cout << "Duration > tag" << endl;
      audioinfo::set_duration_from_tag();
      // --(deprecated)-- fidel_ui::Instance()->set_pb_slider_endtime(audioinfo::duration());
    }
    if (audioinfo::tag_duration() > (int)duration && audioinfo::tag_duration() >=3600)
    {
      cout << "tag > duration" << endl;
      audioinfo::set_duration(duration);
      // --(deprecated)-- fidel_ui::Instance()->set_pb_slider_endtime(duration);
    }
    if ((int)duration == 0 || (int)duration < 0)
    {
      cout << "Duration == 0 || < 0" << endl;
      audioinfo::set_duration_from_tag();
      // --(deprecated)-- fidel_ui::Instance()->set_pb_slider_endtime(audioinfo::duration());
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
      cout << "called " << endl;
      // --(deprecated)-- fidel_ui::Instance()->set_paused_icon();
      gst_element_set_state(pipeline, GST_STATE_PAUSED);
    }
  }

  void playback::play()
  {
    if (idle == false){
      playing = true;

      // --(deprecated)-- fidel_ui::Instance()->set_playing_icon();
      gst_element_set_state(pipeline, GST_STATE_PLAYING);
    }
  }

  void playback::seek(double time, string sender)
  {
    double seekvalue = time * 1000000000;
    if (sender == "seeker"){
      // --(deprecated)-- fidel_ui::Instance()->update_pb_slider_pos(&time);
    }
    gst_element_seek (pipeline, 1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH,
      GST_SEEK_TYPE_SET, seekvalue,
      GST_SEEK_TYPE_NONE, GST_CLOCK_TIME_NONE);
    }
