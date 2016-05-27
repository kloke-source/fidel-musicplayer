#ifndef PLAYBACK
#define PLAYBACK

#include <iostream>
#include <gtkmm.h>
#include <gst/gst.h>
#include <GUI/singleton.h>

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

	void change_spectrum_bands(guint band, gfloat magnitude, gfloat phase_shift);
	//signal accessor
	typedef sigc::signal<void, guint, gfloat, gfloat> type_signal_spectrum_changed;
	type_signal_spectrum_changed signal_spectrum_changed();
//protected:
	type_signal_spectrum_changed m_signal_spectrum_changed;
};

typedef Singleton<playback> audio_playback;
#endif
