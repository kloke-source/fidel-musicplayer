#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <gtkmm.h>
#include <Audio/playback.h>
#include <GUI/fidel-popover.h>
#include <vector>

class Playlist : public Gtk::ScrolledWindow {
 public:
  Playlist();
  ~Playlist();

  enum {
    SONG_NAME,
    ARTIST,
    ALBUM,
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

  void add_list_store_row(std::vector<std::string> row_data);
  void link_to_search_entry(Gtk::SearchEntry *search_entry);
 private:
  // variables
  int total_songs;
  int curr_song_iterator;
  Gtk::SearchEntry *playlist_search_entry;

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
  void on_double_click_handler(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn *column);
  void on_track_finished();
};
typedef Singleton<FidelPopover> fidel_popover;
#endif
