#ifndef GUI
#define GUI
#include <vector>
#include <gtkmm.h>
#include <iostream>
#include <GUI/singleton.h>
#include <GUI/playlist.h>

typedef Glib::RefPtr<Gtk::Builder> Builder;
typedef Glib::RefPtr<Gtk::FileFilter> FileFilter;
typedef Gtk::ApplicationWindow ApplicationWindow;
typedef Gtk::Toolbar Toolbar;
typedef Gtk::ImageMenuItem ImageMenuItem;
typedef Gtk::Image Image;
typedef Gtk::Notebook Notebook;
typedef Gtk::Entry Entry;
typedef Gtk::Label Label;
typedef Gtk::Box Box;
typedef Gtk::Grid Grid;
typedef Gtk::Scale Scale;
typedef Gtk::Button Button;

class gui{
 public:
  gui();
  virtual ~gui();
  void initialize(int argc, char **argv);
  void init_builder();

  void update_pb_timer(double time);
  void set_pb_endtime(int endtime);
 private:
  Glib::RefPtr<Gio::Resource> fidel_resources;
  void init_connections();
  bool keyboard_shortcuts(GdkEventKey* event);
  void init_icons();
  void init_spectrum();

  void init_playback_functions();
  void init_playlist();
  void pb_slider_val_changed();

  void set_styles();
  bool on_window_closed(GdkEventAny* event);
  void on_play_button_clicked();
  void on_playback_status_changed(int status);
  void get_widgets();
  void on_file_open_triggered();
};

typedef Singleton<gui> fidel_ui;
typedef Singleton<Playlist> all_songs;
#endif
