#include <gtkmm.h>
#include <sstream>
#include <iostream>
#include <string.h>
#include <vector>
//#include <taglib/taglib.h>
#include <Utilities/util.h>
//#include <Utilities/btree.h>
//#include <Audio-Info/audioinfo.h>

const char *BACK_SLASH_ESC  = "\\";

enum {
  RED,
  GREEN,
  BLUE
};

std::string util::get_home_dir()
{
  return Glib::get_home_dir();
}

void util::resize_image(Gtk::Image *image, int width, int height)
{
  Glib::RefPtr<Gdk::Pixbuf> image_pixbuf = image->get_pixbuf();
  image_pixbuf = image_pixbuf->scale_simple(width, height, Gdk::INTERP_BILINEAR);
  image->set(image_pixbuf);
}

void util::create_folder(std::string location)
{
#if defined(_WIN32)
  _mkdir(location.c_str());
#else
  mkdir(location.c_str(), 0777);
#endif
}

void util::set_source_rgb(const Cairo::RefPtr<Cairo::Context>& cr, std::string hex_color)
{
  std::vector<double> rgb_vect = util::hex_to_rgb(hex_color);
  std::vector<double> cairo_rgb_vect;
  for (size_t iter = 0; iter < rgb_vect.size(); iter++) {
    double primary_color = (double) 1/(255/rgb_vect[iter]);
    cairo_rgb_vect.push_back(primary_color);
  }
  cr->set_source_rgb(cairo_rgb_vect[RED], cairo_rgb_vect[GREEN], cairo_rgb_vect[BLUE]);
}

std::vector<double> util::hex_to_rgb(std::string hex_val)
{
  std::vector<double> rgb_vect;
  hex_val = hex_val.substr(1, hex_val.length()); //remove # from hexadecimal code
  for (size_t iter = 0; iter < hex_val.size(); iter+=2) {
    if (iter != hex_val.size() - 1){
      std::string hex_sub_sec;// = (std::string) hex_val[iter];// + hex_val[iter+1];
      std::stringstream char_conv;
      char_conv << hex_val[iter];
      char_conv << hex_val[iter+1];
      char_conv >> hex_sub_sec;
      rgb_vect.push_back(util::hex_to_dec(hex_sub_sec));
    }
  }
  return rgb_vect;
}

double util::hex_to_dec(std::string hex_val)
{
  unsigned int dec_val;
  std::stringstream ss;
  ss << std::hex << hex_val;
  ss >> dec_val;
  return static_cast<double>(dec_val);
}

std::string util::gen_ins_stmt(std::string table_name, std::vector<std::string> fields, std::vector<std::string> values)
{
  std::stringstream fields_stream;
  std::stringstream values_stream;

  if (fields.size() == values.size()) {
    fields_stream <<  "INSERT INTO " << table_name << " (";

    for (size_t iter = 0; iter < fields.size(); iter++) {
      if (iter != fields.size() - 1) {
	fields_stream << fields[iter] << ", ";
	values_stream << util::escape_string(values[iter]) <<  "', '";
      }
      else {
	fields_stream << fields[iter] << ") VALUES('";
	values_stream << util::escape_string(values[iter]) << "');";
      }
    }
    fields_stream << values_stream.str();
  }
  else
    return "Error number of fields don't match number of values";

  return fields_stream.str();
}

std::string util::file_to_song_name(std::string file)
{
  std::string file_formats[] = {"flac","mp3","wav","ogg","m4a","m4p"};
  int formats_num = 6;
  int slash_pos;
  bool is_file_location = false;
  slash_pos = file.find_last_of("/");
  is_file_location = true;

  if (is_file_location == true){
    file.erase(0, slash_pos + 1);
  }
  for (int iter = 0; iter < formats_num; iter++) {
    if (file.substr(file.find_last_of(".") + 1) == file_formats[iter]){
      std::string file_format = "." + file_formats[iter];
      file.erase((file.length() - (file_formats[iter].length() + 1)),
      (file.length() + (file_formats[iter].length() + 1)));
      break;
    }
  }
  return file;
}

std::string util::replace(std::string text, std::string find_value, std::string replace_value)
{
  std::stringstream replaced_text;
  for (size_t iter = 0; iter < text.size(); iter++){
    if (text[iter] != *util::to_char(find_value))
      replaced_text << text[iter];
    else
      replaced_text << replace_value;
  }
  return replaced_text.str();
}

std::string util::escape_string(std::string text)
{
  text = util::replace(text, "'", "''");
  return text;
}

std::string util::escape_spaces(std::string text)
{
  text = util::replace(text, " ", "\\ ");
  return text;
}

std::string util::escape_slashes(std::string text)
{
  text = util::replace(text, "/", "-");
  return text;
}

std::string util::unescape_spaces(std::string text)
{
  text = util::replace(text, "\\ ", "");
  return text;
}

std::pair<bool, int> util::search_vect(std::vector<std::string> vect, std::string search_param)
 {
   bool found = false;
   int found_pos;
   for (size_t iter = 0; iter < vect.size(); iter++) {
     if (vect[iter] == search_param) {
       found = true;
       found_pos = iter;
       break;
     }
   }
   return std::make_pair(found, found_pos);
 }

bool util::has_text(std::string base_string, std::string search_value)
{
  if (base_string.find(search_value) != std::string::npos)
    return true;
  else
    return false;
}

bool util::check_file_format(std::string file, std::string file_format)
{
  if (file.substr(file.find_last_of(".") + 1) == file_format)
    return true;
  else return false;
}

char* util::to_char(std::string string_value)
{
  std::string conv_string_value = (std::string) string_value;
  char *char_value = new char[conv_string_value.size() + 1];
  memcpy(char_value, conv_string_value.c_str(), conv_string_value.size() + 1);
  return char_value;
}

int util::to_int(std::string text)
{
  int value = atoi(text.c_str());
  return value;
}

std::string util::to_string(int value)
{
  std::string string_value;
  std::stringstream out;
  out << value;
  string_value = out.str();
  return string_value;
}

std::string util::to_string(double value)
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
std::string util::time_format(double total_seconds)
{
  int hours = total_seconds/3600;
  int minutes = total_seconds/60 - (hours * 60);
  int seconds = total_seconds - ((hours * 3600) + (minutes * 60));

  std::string hours_format_value;
  std::string minutes_format_value;
  std::string seconds_format_value;

  std::string time_format;

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
