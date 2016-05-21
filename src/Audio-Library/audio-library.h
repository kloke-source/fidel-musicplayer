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
  struct LIBRARY_DATA;
  static void init();
  static void scan();
  static void open_db();
  static void close_db();

  static void update_library_db(string table_name, string db_field, string db_data, string position);
  //static void update_library_db(string table_name, string db_field, Glib::ustring db_data, string position);
  static void update_library_db(string table_name, Glib::ustring db_data_string);
  static bool overwrite_check(string file_location);
  static bool exists_in_lib(Glib::ustring file_location);
  static int get_song_num();
  static Glib::ustring get_db_field_data(string table_name, Glib::ustring field, Glib::ustring where_id, bool definite);
  static Glib::ustring get_db_field_data(string table_name, Glib::ustring field, Glib::ustring where_field, Glib::ustring where_id, bool definite);
  static void populate_playlist();
  static vector<vector<Glib::ustring>> batch_collect_info(string table_name);
  static vector<btree<Glib::ustring>> batch_collect_btree(string table_name);
  static vector<Glib::ustring> get_db_row(Glib::ustring field, Glib::ustring where_id);
  static void write_lib_info();
  static void add_lib_data(Glib::ustring ins_stmt);
  static void add_album_info(string file_location);
  static void add_album_summ(string file_location);
  static void add_artist_info(string file_location);
  static void add_artist_summ(string file_location);
  static void flush_to_db();
  static void write_album_summ();
  static void write_artist_summ();
  static void write_album_info(string field, string value, string album_art_location);
  static void write_artist_info(string field, string value);
  static void write(string table_name, Glib::ustring db_data_string);
  static void write(string table_name, string db_field, string db_data);
  static void write(string table_name, string db_field, Glib::ustring db_data);
  static void bulk_write(string table_name, Glib::ustring bulk_ins_stmt);
private:
  static int get_table_pos(string table_name);
  static int populate_playlist_cb(void *data, int total_col_num, char **value, char **fields);
  static int bulk_write_cb(void *data, int total_col_num, char **value, char **fields);
  static void batch_collect_info_backend(string table_name);
  static int batch_collect_info_cb(void *data, int total_col_num, char **value, char **fields);
  static void batch_collect_btree_backend(string table_name);
  static int batch_collect_btree_cb(void *data, int total_col_num, char **value, char **fields);
  static bool file_validator(string file_location);
  static bool db_field_validate(string field);
  //directory scanning functions
  static void scan_dir(const char *dir_location);
  static void process_directory(std::string directory);
  static void process_file(std::string file);
  static void process_entity(struct dirent* entity);
};
#endif
