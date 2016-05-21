#ifndef PLAYBACK
#define PLAYBACK

#include <iostream>
using namespace std;
class playback{
public:
	playback();
	static void audio_file(char *filesrc);
	static void kill_curr_stream();
	static void kill_audio();
	static bool idle_status();
	static bool is_playing();
	static void pause();
	static void play();
	static void seek(double time, string sender);
};
#endif
