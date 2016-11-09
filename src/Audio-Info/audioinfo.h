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

enum {
  SONG_NAME,
  ARTIST,
  ALBUM,
  DURATION_SECONDS,
  TIME
};

class audioinfo{
public:
  audioinfo();
  ~audioinfo();

  static void init(char *filesrc);
  static std::string get_info(int enum_field);
  static std::string get_info(std::string field);
  static double tag_duration();
  static void set_duration(double duration);
  static void set_duration_from_tag();
  static double duration();
  //static Gtk::Image* get_album_art(char *file_location, int width, int height);
  //static string extract_album_art(char *file_location);
  static void add_album_art_to_index(Gtk::Image* album_art, std::string album_name);
  static Gtk::Image* get_album_art(std::string file_location);
  static Gtk::Image* get_album_art_by_name(std::string album_name, std::string file_location);
  static std::tuple<guint8*, gsize, bool> extract_album_art(std::string file_location);  
private:
  static void set_data();
  static bool init_checker(char *filesrc);
};
#endif
