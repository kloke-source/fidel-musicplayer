#ifndef ALBUM_ART
#define ALBUM_ART
#include <vector>
#include <gtkmm.h>
#include <iostream>
#include <Utilities/util.h>
#include <Utilities/btree.h>
#include <GUI/album-art-viewer.h>
#include <Audio-Info/audioinfo.h>
#include <GUI/album-art-viewer.h>

using namespace std;

class AlbumArt{
public:
  AlbumArt();
  AlbumArt(vector<Glib::ustring> album_data);
  void set_album_data(vector<Glib::ustring> album_data);
  //void set_songs_and_file_locs(vector<vector<Glib::ustring> > songs_and_file_locs);
  void set_songs_in_album(vector<Glib::ustring> songs_in_album);
  void set_song_file_locs(vector<Glib::ustring> song_file_locs);
  void set_size(int width, int height);
  Gtk::Image* get_art();
  Glib::ustring get_album_name();
  vector<Glib::ustring> get_songs_in_album();
  vector<Glib::ustring> get_song_file_locs();
  vector<vector<Glib::ustring> > get_songs_and_file_locs();
  ~AlbumArt();
private:
  Gtk::Image *album_art;
  vector<Glib::ustring> album_info;
  Glib::ustring album_name;
  vector<Glib::ustring> songs_in_album;
  vector<Glib::ustring> song_file_locs;
  vector<vector<Glib::ustring> > songs_and_file_locs;
  int total_songs;
};

#endif
