#include <gtkmm.h>
#include <sstream>
#include <iostream>
#include <string.h>
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
  //std::cout << static_cast<double>(dec_val) << std::endl; // output it as a signed type
  return static_cast<double>(dec_val);
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
