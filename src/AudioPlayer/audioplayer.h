#ifndef AUDIO_PLAYER
#define AUDIO_PLAYER

#include <functional>
#include <glibmm/main.h>
#include <gstreamermm.h>
#include <iostream>
#include <vector>

class AudioPlayer {
private:
bool playing = false;
  int spect_bands = 250;
  std::vector<double> band_magnitudes;
  std::function<void(int, double)> band_mag_chgd_cb;

  Glib::RefPtr<Glib::MainLoop> main_loop;
  Glib::RefPtr<Gst::Pipeline> pipeline;
  Glib::RefPtr<Gst::Bin> audiobin;
  Glib::RefPtr<Gst::Element> spectrum;
  Glib::RefPtr<Gst::FileSrc> source;

  bool on_bus_message(const Glib::RefPtr<Gst::Bus> &,
                      const Glib::RefPtr<Gst::Message> &message);
  void on_decoder_pad_added(const Glib::RefPtr<Gst::Pad> &pad);

  void init();

public:
  AudioPlayer();
  ~AudioPlayer();

  void play_file(const std::string &filename);
  void kill_stream();
  void pause();
  void resume();
  bool is_playing();
  void set_band_mag_chd_cb(std::function<void(int, double)> cb);
};

#endif
