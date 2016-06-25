#ifndef PLAYBACK
#define PLAYBACK

#include <iostream>
#include <gtkmm.h>
#include <gst/gst.h>
#include <GUI/singleton.h>
#include <vector>

class playback{
public:
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
	void change_playback_status(bool is_playing);
	void update_pb_timer(double seek_value);

	//signal accessors
	typedef sigc::signal<void, bool> type_signal_status_changed;
	type_signal_status_changed signal_status_changed();

	typedef sigc::signal<void> type_signal_start_spectrum;
	type_signal_start_spectrum signal_spectrum_start();

	typedef sigc::signal<void, double> type_signal_pb_timer_changed;
	type_signal_pb_timer_changed signal_update_pb_timer();

	protected:
	type_signal_start_spectrum m_signal_spectrum_start;
	type_signal_status_changed m_signal_status_changed;
	type_signal_pb_timer_changed m_signal_update_pb_timer;
};

typedef Singleton<playback> audio_playback;
#endif
