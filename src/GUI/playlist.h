#ifndef PLAYLIST_HH
#define PLAYLIST_HH

#include <vector>
#include <gtkmm.h>
#include <Audio/playback.h>
#include <Utilities/btree.h>

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
  std::vector<std::vector<std::string>> get_full_row_data();
  void link_to_search_entry(Gtk::SearchEntry *search_entry);
  // signal accessors
  typedef sigc::signal<void> type_signal_playing;
  type_signal_playing signal_playing();
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
  bool alternate_color = false;
  int file_count_iter = 0;

  Gtk::SearchEntry *playlist_search_entry;

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

  //signal functions
  void set_playing();

  // signal handlers
  void on_row_double_clicked(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn *column);
  bool on_right_click(GdkEventButton *button_event);
  void on_track_finished();
 protected:
  int total_songs;
  int curr_song_iterator;

  Playlist::Playlist_Columns playlist_columns;
  Gtk::TreeView *playlist_tree_view;
  Glib::RefPtr<Gtk::ListStore> playlist_model;
  std::vector<btree<std::string>> playlist_info_store;

  type_signal_playing m_signal_playing;
};

#endif
