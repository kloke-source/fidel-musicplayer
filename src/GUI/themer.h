#ifndef THEMER
#define THEMER
#include <iostream>
#include <gtkmm.h>
#include <GUI/gui.h>

class themer{
  themer();
  ~themer();
public:
  static void set_styles();
private:
  static void init_vectors();
  static void init_fonts();
  static void init_stylesheets();
  static void set_colors();
  static void set_fonts();
};
#endif
