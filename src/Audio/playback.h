#ifndef PLAYBACK
#define PLAYBACK

#include <iostream>
#include <gtkmm.h>
#include <gst/gst.h>
#include <GUI/singleton.h>
#include <vector>

class playback{
 public:
  enum {
    PAUSED,
    PLAYING,
    IDLE
  };
  
  playback();
  void audio_file(char *filesrc);
  void kill_curr_stream();
  void kill_audio();
  bool idle_status();
  bool is_playing();
  void pause();
  void play();
  void seek(double time, std::string sender);

  //signal functions
  void start_spectrum_visualization();
  void notify_spect_bands_updated();
  void change_playback_status(int status);
  void update_pb_timer(double seek_value);
  void set_track_finished();
  
  //signal accessors
  typedef sigc::signal<void, int> type_signal_status_changed;
  type_signal_status_changed signal_status_changed();

  typedef sigc::signal<void> type_signal_start_spectrum;
  type_signal_start_spectrum signal_spectrum_start();

  typedef sigc::signal<void, std::vector<double>> type_signal_spect_bands_updated;
  type_signal_spect_bands_updated signal_spect_bands_updated();
  
  typedef sigc::signal<void, double> type_signal_pb_timer_changed;
  type_signal_pb_timer_changed signal_update_pb_timer();

  typedef sigc::signal<void> type_signal_track_finished;
  type_signal_track_finished signal_track_finished();
  
 protected:
  type_signal_start_spectrum m_signal_spectrum_start;
  type_signal_spect_bands_updated m_signal_spect_bands_updated;
  type_signal_status_changed m_signal_status_changed;
  type_signal_pb_timer_changed m_signal_update_pb_timer;
  type_signal_track_finished m_signal_track_finished;
};

typedef Singleton<playback> audio_playback;
#endif
