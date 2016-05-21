#ifndef SEEKER
#define SEEKER
#include <GUI/singleton.h>
#include <gtkmm.h>
class seeker : public Gtk::Window
{
public:
  seeker();
  ~seeker();
  static void show(Gtk::Window *parent);
private:
  static void kill();
  static void init();
  static void init_connections();
  static void init_builder();
  static void seek();
  static void set_entry_focus();
  static bool on_seek_button_focused(GdkEventFocus* event);
  static bool on_seek_button_unfocused(GdkEventFocus* event);
  static bool on_seek_button_hover(GdkEventCrossing* event);
  static bool on_seek_button_leave(GdkEventCrossing* event);
  static bool on_cancel_button_focused(GdkEventFocus* event);
  static bool on_cancel_button_unfocused(GdkEventFocus* event);
  static bool on_cancel_button_hover(GdkEventCrossing* event);
  static bool on_cancel_button_leave(GdkEventCrossing* event);
  static void data_validator(Glib::ustring text,int *character_num, Gtk::Entry *data_entry_widget);
  static void hours_tenths_handler(const Glib::ustring& text,int* character_num);
  static void hours_units_handler(const Glib::ustring& text,int* character_num);
  static void minutes_tenths_handler(const Glib::ustring& text,int* character_num);
  static void minutes_units_handler(const Glib::ustring& text,int* character_num);
  static void seconds_tenths_handler(const Glib::ustring& text,int* character_num);
  static void seconds_units_handler(const Glib::ustring& text,int* character_num);
};
//typedef Singleton<seeker> audio_seeker;
#endif
