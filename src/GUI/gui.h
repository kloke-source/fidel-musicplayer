#ifndef GUI
#define GUI

#include <Audio-Library/audio-library.h>
#include <Audio/playback.h>
#include <AudioPlayer/audioplayer.h>
#include <GUI/album-art-viewer.h>
#include <GUI/playlist-manager.h>
#include <GUI/playlist-queue.h>
#include <GUI/playlist.h>
#include <GUI/seeker.h>
#include <GUI/singleton.h>
#include <GUI/themer.h>
#include <Spectrum/spectrum.h>
#include <Utilities/threadpool.h>
#include <Utilities/util.h>
#include <gio/gio.h>
#include <gtkmm.h>
#include <iostream>
#include <vector>

extern "C" {
#include <GUI/fidel-resources.h>
}

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

class Playlist;
class PlaylistQueue;

class gui {
public:
  gui();
  virtual ~gui();
  void initialize(int argc, char **argv);
  void init_builder();

  void update_pb_timer(double time);
  void set_pb_endtime(int endtime);
  PlaylistQueue *get_playlist_queue();
  void append_playlist_row(std::vector<std::string> row_data);

private:
  // variables
  AlbumArtViewer *album_art_viewer;
  Glib::RefPtr<Gio::Resource> fidel_resources;
  Gtk::Image *sidebar_album_art;

  Playlist *all_songs_playlist;
  PlaylistQueue *queue_playlist;
  int sidebar_width = 200;
  int default_sidebar_size = 200;
  bool sidebar_hidden = true;

  // fonts
  Pango::FontDescription sidebar_font;

  void init_connections();
  bool keyboard_shortcuts(GdkEventKey *event);
  void init_icons();
  void init_sidebar();
  void init_spectrum();

  void init_playback_functions();
  void init_album_art_viewer();
  void init_playlist();
  void init_stack_sidebar();
  void pb_slider_val_changed();

  void set_styles();

  void get_widgets();

  void hide_sidebar();
  void show_sidebar();

  // signal handlers
  bool on_window_closed(GdkEventAny *event);
  void set_sidebar_data(char *now_playing_song);
  void on_play_button_clicked();
  void on_playback_status_changed(int status);
  void on_sidebar_hider_clicked();
  void on_test_signal(Gtk::Widget *widget);

  void on_file_open_triggered();
};

typedef Singleton<gui> fidel_ui;
typedef Singleton<ThreadPool> threadpool;
typedef Singleton<AudioPlayer> audio_player;
#endif
