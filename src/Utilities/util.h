#ifndef UTIL
#define UTIL

#include <gtkmm.h>
#include <taglib/taglib.h>
#include <taglib/fileref.h>
#include <iostream>
#include <vector>
#include <Utilities/btree.h>
using namespace std;

class util{
public:
  static string get_home_dir();
  static void resize_image(Gtk::Image *image, int width, int height);
  static Glib::ustring file_to_song_name(string file);
  static Glib::ustring gen_db_ins_stmt(string file_location, string file);
  static Glib::ustring gen_ins_stmt(string table, vector<Glib::ustring> fields, vector<Glib::ustring> values);
  static Glib::ustring gen_bulk_ins_stmt(string table, vector<Glib::ustring> fields, vector<vector<Glib::ustring>> values);
  static Glib::ustring collate_ins_stmts(vector<Glib::ustring> ins_stmts);
  static int round_up(double number);
  static string escape_string(string text);
  static string escape_spaces(string text);
  static string escape_slashes(string text);
  static Glib::ustring escape_slashes(Glib::ustring text);
  static string unescape_spaces(string text);
  static string replace(string text, string find_value, string replace_value);
  static btree<Glib::ustring> vector_to_btree(vector<Glib::ustring> input_vector);
  static vector<Glib::ustring> btree_to_vector(btree<Glib::ustring> input_btree);
  static char* to_char(Glib::ustring string_value);
  static char* to_char(string string_value);
  static int to_int (string text);
  static string to_string(int value);
  static string to_string(double value);
  static int seconds_format(int hours, int minutes, int seconds);
  static string time_format(double total_seconds);
private:
};
#endif
