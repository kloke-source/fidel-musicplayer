#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <vector>
#include <gtkmm.h>
#include <Audio/playback.h>
#include <Utilities/btree.h>
#include <GUI/fidel-options.h>

//class gui;
class FidelOptions;

class Playlist : public Gtk::ScrolledWindow {
 public:
  Playlist();
  ~Playlist();

  enum {
    SONG_NAME,
    ARTIST,
    ALBUM,
    TIME,
    FILE_LOC
  };

  class Playlist_Columns : public Gtk::TreeModel::ColumnRecord
  {
  public:

    Playlist_Columns()
      {add(col_name); add(col_artist); add(col_album); add(col_time); add(col_color);  add (col_file_location);}

    Gtk::TreeModelColumn<std::string> col_name;
    Gtk::TreeModelColumn<std::string> col_artist;
    Gtk::TreeModelColumn<std::string> col_album;
    Gtk::TreeModelColumn<std::string> col_time;
    Gtk::TreeModelColumn<std::string> col_color;
    Gtk::TreeModelColumn<std::string> col_file_location;
  };

  void enable();
  void disable();
  void prepend_row(std::vector<std::string> row_data);    
  void append_after_current(std::vector<std::string> row_data);
  void append_row(std::vector<std::string> row_data);
  void append_row();  
  void link_to_search_entry(Gtk::SearchEntry *search_entry);
 private:
  // connections
  sigc::connection track_finished_connection;

  // enums
  enum {
    LEFT_CLICK = 1,
    MIDDLE_CLICK = 2,
    RIGHT_CLICK  = 3
  };
  
  // variables
  int total_songs;
  int curr_song_iterator;

  bool alternate_color = false;
  int file_count_iter = 0;

  Gtk::SearchEntry *playlist_search_entry;

  Playlist::Playlist_Columns playlist_columns;
  Gtk::TreeView *playlist_tree_view;
  Glib::RefPtr<Gtk::ListStore> playlist_model;
  std::vector<btree<std::string>> playlist_info_store;


  // fonts
  Pango::FontDescription default_font;
  int default_font_size = 13;

  // enums
  enum {
    COL_NAME,
    COL_ARTIST,
    COL_ALBUM,
    COL_TIME,
    COL_FILE_LOC
  };

  // functions
  void init_connections();
  void init_playlist();
  void resize_handler(Gtk::Allocation &allocation);
  void on_insert_text(const std::string& text, int* character_num);
  void on_delete_text(int start_pos, int end_pos);
  void search_playlist(std::string search_term);
  
  // signal handlers
  void on_row_double_clicked(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn *column);
  bool on_right_click(GdkEventButton *button_event);  
  void on_track_finished();
};

#endif
