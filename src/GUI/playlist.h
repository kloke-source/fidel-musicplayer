#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <gtkmm.h>
#include <Audio/playback.h>
#include <vector>

class Playlist : public Gtk::ScrolledWindow {
 public:
  Playlist();
  ~Playlist();

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
 private:
  void init_connections();
  void init_playlist();
  void on_double_click_handler(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn *column);
};

#endif