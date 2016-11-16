#ifndef UTIL
#define UTIL

#include <gtkmm.h>
#include <GUI/gui.h>
//#include <taglib/taglib.h>
//#include <taglib/fileref.h>
#include <iostream>
#include <vector>
#include <sstream>
//#include <Utilities/btree.h>

class util{
 public:
  static std::string get_home_dir();
  static Gtk::Image* resize_image(Gtk::Image* image, int width, int height);
  //  static void resize_image(Gtk::Image& image, int width, int height);
  static void create_folder(std::string location);
  static void set_source_rgb(const Cairo::RefPtr<Cairo::Context>& cr, std::string hex_color);
  static std::vector<double> hex_to_rgb(std::string hex_val);
  static double hex_to_dec(std::string hex_val);
  
  static std::string gen_ins_stmt(std::string table_name, std::vector<std::string> fields, std::vector<std::string> values);
  static std::string file_to_song_name(std::string file);
  static std::string replace(std::string text, std::string find_value, std::string replace_value);
  static std::string escape_string(std::string text);
  static std::string escape_spaces(std::string text);
  static std::string escape_slashes(std::string text);
  static std::string unescape_spaces(std::string text);

  static std::pair<bool, int> search_vect(std::vector<std::string> vect, std::string search_param);
  static bool has_text(std::string base_string, std::string search_value);
  static bool check_file_format(std::string file, std::string file_format);
  static char *to_char(std::string string_value);
  static int to_int (std::string text);

  template<class T>
    static std::string to_string(T input) {
    std::stringstream conv_stream;
    conv_stream << input;
    return conv_stream.str();
  }

  static int round_up(double input_num);
  static int seconds_format(int hours, int minutes, int seconds);
  static std::string time_format(double total_seconds);
};
#endif
