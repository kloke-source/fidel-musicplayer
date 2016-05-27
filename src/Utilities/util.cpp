#include <gtkmm.h>
#include <sstream>
#include <iostream>
#include <string.h>
//#include <taglib/taglib.h>
#include <Utilities/util.h>
//#include <Utilities/btree.h>
//#include <Audio-Info/audioinfo.h>

const char *BACK_SLASH_ESC  = "\\";

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
