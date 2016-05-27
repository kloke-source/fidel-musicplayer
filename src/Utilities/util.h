#ifndef UTIL
#define UTIL

#include <gtkmm.h>
//#include <taglib/taglib.h>
//#include <taglib/fileref.h>
#include <iostream>
#include <vector>
//#include <Utilities/btree.h>

class util{
public:
  static char *to_char(std::string string_value);
  static int to_int (std::string text);
  static std::string to_string(int value);
  static std::string to_string(double value);
  static int seconds_format(int hours, int minutes, int seconds);
  static std::string time_format(double total_seconds);
};
#endif
