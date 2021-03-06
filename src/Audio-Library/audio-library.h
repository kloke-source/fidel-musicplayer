#ifndef AUDIO_LIBRARY
#define AUDIO_LIBRARY

#include <taglib/taglib.h>
#include <gtkmm.h>
#include <dirent.h>
#include <iostream>
#include <sqlite3.h>
#include <Audio-Info/audioinfo.h>
#include <Utilities/btree.h>

using namespace std;

struct AlbumSummary{
  std::string album_name;
  btree<std::string> songs_in_album;
  std::vector<std::string> file_locations;
  int total_songs_in_album;
};

class AudioLibrary {
 public:
  static void initialize();
  static void populate_playlist();
  static std::tuple<guint8*, gsize, bool> get_album_art(std::string album_name);
  static void scan();

  static std::vector<AlbumSummary> get_album_summary();
 private:
  // initialization functions
  static void init_db();
  static void load_db();
  static void load_album_info();

  static int generic_db_callback(void *data, int total_col_num, char **value, char **fields);
  // validation functions
  static bool check_file_format(std::string input_file);
  // db functions
  static void db_ins_row(std::string ins_stmt);
  static void db_ins_blob(std::string blob_ins_stmt, guint8 *buffer, gsize buffer_size);

  static void write_lib_data(std::string file_location);
  static void write_lib_info();

  static void add_album_summ(std::string file_location);
  static void write_album_summ();
  static void write_album_info(std::string file_location);

  static void add_artist_summ(std::string file_location);
  static void write_artist_summ();
  static void write_artists(std::string file_location);

  static void load_album_index();
  static void load_album_summary();
  static void load_artist_summary();

  static int populate_playlist_cb(void *data, int total_col_num, char **value, char **fields);
  static void scan_dir(const char *dir_location);
  static int flush_to_db(sqlite3 *pInMemory, const char *file_name);
};
#endif
