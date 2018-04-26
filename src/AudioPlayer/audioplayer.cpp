#include "audioplayer.h"

AudioPlayer::AudioPlayer() {
  main_loop = Glib::MainLoop::create();
  pipeline = Gst::Pipeline::create();
  pipeline->get_bus()->add_watch(
      sigc::mem_fun(*this, &AudioPlayer::on_bus_message));

  for (size_t iter = 0; iter < this->spect_bands; iter++)
    this->band_magnitudes.push_back(0);
}

AudioPlayer::~AudioPlayer() {}

void AudioPlayer::init() {
  audiobin = Glib::RefPtr<Gst::Bin>::cast_dynamic(Gst::Parse::create_bin(
      "filesrc name=\"filesrc\" ! decodebin ! audioconvert ! spectrum "
      "name=\"spectrum\" ! autoaudiosink",
      false));
  source = Glib::RefPtr<Gst::FileSrc>::cast_dynamic(
      audiobin->get_element("filesrc"));
  spectrum = audiobin->get_element("spectrum");
  spectrum->set_property("bands", this->spect_bands);
  spectrum->set_property("post-messages", true);
  spectrum->set_property("threshold", -80);
  pipeline->add(audiobin);
}

void AudioPlayer::play_file(const std::string &filename) {
  init();
  this->playing = true;
  source->property_location() = filename;
  pipeline->set_state(Gst::STATE_PLAYING);
  main_loop->run();
  pipeline->set_state(Gst::STATE_NULL);
}

void AudioPlayer::kill_stream() {
  // main_loop->quit();
  pipeline->set_state(Gst::STATE_NULL);
}

void AudioPlayer::pause() { pipeline->set_state(Gst::STATE_PAUSED); }

void AudioPlayer::resume() { pipeline->set_state(Gst::STATE_PLAYING); }

bool AudioPlayer::is_playing() {
  return this->playing;
}
void AudioPlayer::set_band_mag_chd_cb(std::function<void(int, double)> cb) {
  this->band_mag_chgd_cb = cb;
}

bool AudioPlayer::on_bus_message(const Glib::RefPtr<Gst::Bus> &,
                                 const Glib::RefPtr<Gst::Message> &message) {
  switch (message->get_message_type()) {
  case Gst::MESSAGE_EOS:
    std::cout << std::endl << "End of stream" << std::endl;
    main_loop->quit();
    return false;
  case Gst::MESSAGE_ERROR:
    std::cerr
        << "Error."
        << Glib::RefPtr<Gst::MessageError>::cast_static(message)->parse_debug()
        << std::endl;
    main_loop->quit();
    return false;
    break;
  default:
    break;
  }

  if (message->get_message_type() == Gst::MESSAGE_ELEMENT) {
    auto msg_struct = message->get_structure();
    GstStructure *msg_struct_gobj = msg_struct.gobj();
    const GValue *magnitudes =
        gst_structure_get_value(msg_struct_gobj, "magnitude");

    for (int iter = 0; iter < this->spect_bands; iter++) {
      // freq = (gdouble) ((AUDIOFREQ / 2) * iter + AUDIOFREQ / 4) /
      // spect_bands;

      const GValue *mag = gst_value_list_get_value(magnitudes, iter);
      // phase = gst_value_list_get_value (phases, iter);

      if (mag != NULL) {
        double magnitude = (double)g_value_get_float(mag);
        // this->band_magnitudes[iter] = magnitude;
        this->band_mag_chgd_cb(iter, magnitude);
        // gfloat phase_shift = g_value_get_float(phase);

        // band_magnitudes[iter] = (double)magnitude;
        // phase_shifts[iter] = (double)phase_shift;
      
      }
    }
  }

  return true;
}

void AudioPlayer::on_decoder_pad_added(const Glib::RefPtr<Gst::Pad> &pad) {
  Glib::ustring caps_format = pad->get_current_caps()->to_string().substr(0, 5);
  Glib::RefPtr<Gst::Bin> parent =
      parent.cast_dynamic(pad->get_parent()->get_parent());

  if (!parent) {
    std::cerr << "cannot get parent bin" << std::endl;
    return;
  }

  Glib::ustring factory_name;

  if (caps_format == "video") {
    factory_name = "autovideosink";
  } else if (caps_format == "audio") {
    factory_name = "autoaudiosink";
  } else {
    std::cerr << "unsupported media type: "
              << pad->get_current_caps()->to_string() << std::endl;
    return;
  }

  Glib::RefPtr<Gst::Element> element =
      Gst::ElementFactory::create_element(factory_name);

  if (!element) {
    std::cerr << "cannot create element " << factory_name << std::endl;
    return;
  }

  try {
    parent->add(element);
    element->set_state(Gst::STATE_PLAYING);
    pad->link(element->get_static_pad("sink"));
  } catch (const std::runtime_error &err) {
    std::cerr << "cannot add element to a bin: " << err.what() << std::endl;
  }
}
