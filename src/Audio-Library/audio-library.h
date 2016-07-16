#ifndef AUDIO_LIBRARY
#define AUDIO_LIBRARY

#include <taglib/taglib.h>
#include <gtkmm.h>
#include <dirent.h>
#include <iostream>
#include <sqlite3.h>
#include <Utilities/btree.h>

using namespace std;

class AudioLibrary{
  AudioLibrary();
  ~AudioLibrary();
public:
  static void scan_dir(const char *dir_location);
private:
  //directory scanning functions
  static void scan_dir_backend(const char *dir_location);
};
#endif
