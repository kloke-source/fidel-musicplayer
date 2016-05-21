#include <gtkmm.h>
#include <sstream>
#include <iostream>
#include <string.h>
#include <taglib/taglib.h>
#include <Utilities/util.h>
#include <Utilities/btree.h>
#include <Audio-Info/audioinfo.h>
#include <ctime>
#include <future>
#include <thread>
using namespace std;

const char *BACK_SLASH_ESC  = "\\";

string util::get_home_dir()
{
    return Glib::get_home_dir();
}

void util::resize_image(Gtk::Image *image, int width, int height)
{
  Glib::RefPtr<Gdk::Pixbuf> image_pixbuf = image->get_pixbuf();
  image_pixbuf = image_pixbuf->scale_simple(width, height, Gdk::INTERP_BILINEAR);
  image->set(image_pixbuf);
}

Glib::ustring util::file_to_song_name(string file)
{
  string file_formats[] = {"flac","mp3","wav","ogg","m4a","m4p"};
  int formats_num = 6;
  cout << "file_formats num: " << formats_num << endl;
  int slash_pos;
  bool is_file_location = false;
  slash_pos = file.find_last_of("/");
  is_file_location = true;

  if (is_file_location == true){
    file.erase(0, slash_pos + 1);
  }
  for (int iter = 0; iter < formats_num; iter++) {
    cout << "file_formats: " << file_formats[iter] << endl;
    if (file.substr(file.find_last_of(".") + 1) == file_formats[iter]){
      string file_format = "." + file_formats[iter];
      file.erase((file.length() - (file_formats[iter].length() + 1)),
      (file.length() + (file_formats[iter].length() + 1)));
      break;
    }
  }
  return file;
}

Glib::ustring util::gen_db_ins_stmt(string file_location,  string file)
{
  audioinfo::init(util::to_char(file_location));
  auto escape_job = std::async(std::launch::async,	util::escape_string, file_location);
  Glib::ustring song_name = util::escape_string(audioinfo::get_info("song_name"));
  Glib::ustring artist = util::escape_string(audioinfo::get_info("artist"));
  Glib::ustring album = util::escape_string(audioinfo::get_info("album"));
  Glib::ustring duration_seconds = util::to_string(audioinfo::duration());
  Glib::ustring duration_formatted = audioinfo::get_info("duration_formatted");
  file_location = escape_job.get();

  if (song_name == "" || song_name == " "){
    file = util::file_to_song_name(file);
    song_name = util::escape_string(file);
  }
  if (artist == "" || artist == " "){
    artist = "Unknown Artist";
  }
  if (album == "" || album == " "){
    album = "Unknown Album";
  }

  Glib::ustring db_ins_stmt;
  db_ins_stmt = "BEGIN; INSERT INTO library (file_location, Name, Artist, Album, Time, duration_seconds) ";
  db_ins_stmt.append("VALUES('" + file_location + "', '" + song_name);
  db_ins_stmt.append("', '" + artist + "', '");
  db_ins_stmt.append(album + "', '" + duration_formatted);
  db_ins_stmt.append("', '" + duration_seconds + "'); COMMIT;");

  cout << db_ins_stmt << endl;
  return db_ins_stmt;
}

Glib::ustring util::gen_ins_stmt(string table, vector<Glib::ustring> fields, vector<Glib::ustring> values)
{
  Glib::ustring custom_ins_stmt = "BEGIN; INSERT INTO " + table + " (";
  for (size_t field_iter = 0; field_iter < fields.size(); field_iter++){
    if (field_iter != fields.size() - 1){
      custom_ins_stmt.append(fields[field_iter] + ", ");
    }
    else {
      custom_ins_stmt.append(fields[field_iter] + ") VALUES('");
    }
  }
  for (size_t value_iter = 0; value_iter < values.size(); value_iter++){
    if (value_iter != values.size() - 1){
      custom_ins_stmt.append(util::escape_string(values[value_iter]) + "', '");
    }
    else {
      custom_ins_stmt.append(util::escape_string(values[value_iter]) + "'); COMMIT;");
    }
  }
  return custom_ins_stmt;
}

Glib::ustring util::gen_bulk_ins_stmt(string table, vector<Glib::ustring> fields, vector<vector<Glib::ustring>> values)
{
  Glib::ustring custom_bulk_ins_stmt;// = "INSERT INTO " + table + "(";
  bool fields_appended = false;
  Glib::ustring field_portion;
  for (size_t row_iter = 0; row_iter < values.size(); row_iter++){
    custom_bulk_ins_stmt += "BEGIN; INSERT INTO " + table + "(";
    Glib::ustring values_portion;
    for (size_t col_iter = 0; col_iter < values[row_iter].size(); col_iter++){
      if (col_iter != values[row_iter].size() - 1){
        if (fields_appended == false){
          field_portion.append(fields[col_iter] + ", ");
        }
        values_portion.append(util::escape_string(values[row_iter][col_iter]) + "', '");
      }
      else {
        if (fields_appended == false){
          field_portion.append(fields[col_iter] + ") VALUES ('");
        }
        values_portion.append(util::escape_string(values[row_iter][col_iter]) + "'); END; ");
      }
    }
    custom_bulk_ins_stmt.append(field_portion);
    custom_bulk_ins_stmt.append(values_portion);
    fields_appended = true;
  }
  return custom_bulk_ins_stmt;
}

Glib::ustring util::collate_ins_stmts(vector<Glib::ustring> ins_stmts)
{
  Glib::ustring collated_stmts;
  for (size_t iter = 0; iter < ins_stmts.size(); iter++){
    if (iter != ins_stmts.size() - 1){
      collated_stmts.append(ins_stmts[iter] + "\n");
    }
    else {
      collated_stmts.append(ins_stmts[iter]);
    }
  }
  return collated_stmts;
}

int util::round_up(double number)
{
  int floored_value = (int)number;
  double decimal = number - floored_value;
  if (decimal > 0){
    return number + 1;
  }
  else {
    return number;
  }
}

string util::escape_string(string text)
{
  text = util::replace(text, "'", "''");
  return text;
}

string util::escape_spaces(string text)
{
  text = util::replace(text, " ", "\\ ");
  return text;
}

string util::unescape_spaces(string text)
{
  text = util::replace(text, "\\ ", "");
  return text;
}

string util::escape_slashes(string text)
{
  text = util::replace(text, "/", "-");
  return text;
}

Glib::ustring util::escape_slashes(Glib::ustring text)
{
  text = util::replace(text, "/", "-");
  return text;
}

string util::replace(string text, string find_value, string replace_value)
{
  stringstream replaced_text;
  for (size_t iter = 0; iter < text.size(); iter++){
    if (text[iter] != *util::to_char(find_value))
    replaced_text << text[iter];
    else
    replaced_text << replace_value;
  }
  return replaced_text.str();
}

btree<Glib::ustring> util::vector_to_btree(vector<Glib::ustring> input_vector)
{
  btree<Glib::ustring> converted_vector;
  for (size_t iter = 0; iter < input_vector.size(); iter++){
    converted_vector.insert(input_vector[iter]);
  }
  return converted_vector;
}

vector<Glib::ustring> util::btree_to_vector(btree<Glib::ustring> input_btree)
{
  vector<Glib::ustring> converted_btree = input_btree.inorder();
}

char* util::to_char(Glib::ustring string_value)
{
  string conv_string_value = (string) string_value;
  char *char_value = new char[conv_string_value.size() + 1];
  memcpy(char_value, conv_string_value.c_str(), conv_string_value.size() + 1);
  return char_value;
}

char* util::to_char(string string_value)
{
  char *char_value = new char[string_value.size() + 1];
  memcpy(char_value, string_value.c_str(), string_value.size() + 1);
  return char_value;
}

int util::to_int(string text)
{
  int value = atoi(text.c_str());
  return value;
}

string util::to_string(int value)
{
  std::string string_value;
  std::stringstream out;
  out << value;
  string_value = out.str();
  return string_value;
}

string util::to_string(double value)
{
  std::string string_value;
  std::stringstream out;
  out << value;
  string_value = out.str();
  return string_value;
}

int util::seconds_format(int hours, int minutes, int seconds)
{
  int total_seconds = (hours * 3600) + (minutes * 60) + seconds;
  return total_seconds;
}
string util::time_format(double total_seconds)
{
  int hours = total_seconds/3600;
  int minutes = total_seconds/60 - (hours * 60);
  int seconds = total_seconds - ((hours * 3600) + (minutes * 60));

  string hours_format_value;
  string minutes_format_value;
  string seconds_format_value;

  string time_format;

  if (hours >= 10)
  {
    hours_format_value = util::to_string(hours) + ":";
  }
  if (hours < 10 && hours > 0)
  {
    hours_format_value = "0" + util::to_string(hours) + ":";
  }
  if (minutes >= 10)
  {
    minutes_format_value = util::to_string(minutes) + ":";
  }
  if (minutes < 10)
  {
    minutes_format_value = "0" + util::to_string(minutes) + ":";
  }
  if (seconds >= 10){
    seconds_format_value = util::to_string(seconds);
  }
  if (seconds < 10)
  {
    seconds_format_value = "0" + util::to_string(seconds);
  }

  time_format = hours_format_value + minutes_format_value + seconds_format_value;
  return time_format;
}
