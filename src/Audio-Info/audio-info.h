#ifndef AUDIOINFO
#define AUDIOINFO

#include <taglib.h>
#include <taglib/fileref.h>
#include <id3v2tag.h>
#include <mpegfile.h>
#include <flacfile.h>
#include <id3v2frame.h>
#include <id3v2header.h>
#include <attachedpictureframe.h>
#include <cstdio>
#include <string.h>
#include <iostream>
#include <gtkmm.h>

using namespace std;

class AudioInfo{
public:
  AudioInfo();
  ~AudioInfo();

  static void init(char *filesrc);
  static Glib::ustring get_info(std::string field);
  static double tag_duration();
  static void set_duration(double duration);
  static void set_duration_from_tag();
  static double duration();
  static Gtk::Image* get_album_art(char *file_location, int width, int height);
  static string extract_album_art(char *file_location);
  static Gtk::Image* get_extracted_album_art(char *file_location, int width, int height);
  static vector<Gtk::Image*> get_all_album_art(int width, int height);
  //static void testprint();
private:
  static void setData();
  static bool init_checker(char *filesrc);
};
#endif
