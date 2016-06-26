#ifndef UTIL
#define UTIL

#include <gtkmm.h>
#include <GUI/gui.h>
//#include <taglib/taglib.h>
//#include <taglib/fileref.h>
#include <iostream>
#include <vector>
//#include <Utilities/btree.h>

class util{
public:
  static void set_source_rgb(const Cairo::RefPtr<Cairo::Context>& cr, std::string hex_color);
  static std::vector<double> hex_to_rgb(std::string hex_val);
  static double hex_to_dec(std::string hex_val);
  static char *to_char(std::string string_value);
  static int to_int (std::string text);
  static std::string to_string(int value);
  static std::string to_string(double value);
  static int seconds_format(int hours, int minutes, int seconds);
  static std::string time_format(double total_seconds);

  template <typename T>
  static std::string get_var_type(T variable)
  {
    std::string variable_type;
    if (typeid(T) == typeid(double))
    variable_type = "double";
    else if (typeid(T) == typeid(bool))
    variable_type = "bool";
    else if (typeid(T) == typeid(int))
    variable_type = "int";
    else if (typeid(T) == typeid(float))
    variable_type = "float";
    else if (typeid(T) == typeid(ApplicationWindow*))
    variable_type = "ApplicationWindow*";
    else if (typeid(T) == typeid(Toolbar*))
    variable_type = "Toolbar*";
    else if (typeid(T) == typeid(ImageMenuItem*))
    variable_type = "ImageMenuItem*";
    else if (typeid(T) == typeid(Notebook*))
    variable_type = "Notebook*";
    else if (typeid(T) == typeid(Entry*))
    variable_type = "Entry*";
    else if (typeid(T) == typeid(Image*))
    variable_type = "Image*";
    else if (typeid(T) == typeid(Label*))
    variable_type = "Label*";
    else if (typeid(T) == typeid(Box*))
    variable_type = "Box*";
    else if (typeid(T) == typeid(Grid*))
    variable_type = "Grid*";
    else if (typeid(T) == typeid(Scale*))
    variable_type = "Scale*";
    else if (typeid(T) == typeid(Button*))
    variable_type = "Button*";

    return variable_type;
  }

  template <typename A, typename B>
  static bool var_type_comparison(A first_var, B second_var)
  {
    if (util::get_var_type(first_var) == util::get_var_type(second_var))
    return true;
    else
    return false;
  }
};
#endif
