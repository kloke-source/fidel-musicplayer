#include <gtkmm.h>
#include <iostream>
#include <GUI/album-art.h>
#include <Utilities/util.h>
#include <Utilities/btree.h>
#include <GUI/album-art-viewer.h>
#include <Audio-Info/audioinfo.h>
#include <GUI/album-art-viewer.h>

using namespace std;

//string home_dir = util::get_home_dir();

enum album_fields
{
  ID,
  ALBUM_NAME,
  ALBUM_ART_LOCATION,
  SONGS_IN_ALBUM = 2,
  FILE_LOCATION = 3
};

AlbumArt::AlbumArt(){}

AlbumArt::~AlbumArt(){}

AlbumArt::AlbumArt(vector<Glib::ustring> album_data)
{
  album_art = new Gtk::Image();
  AlbumArt::set_album_data(album_data);
}

void AlbumArt::set_album_data(vector<Glib::ustring> album_data)
{
  album_art = new Gtk::Image();
  album_info = album_data;
  album_name = album_data[ALBUM_NAME];
  if (album_data[ALBUM_ART_LOCATION] != "No Album Art"){
    cout << "ALBUM ART set " << album_data[ALBUM_ART_LOCATION] << endl;
    album_art->set(album_data[ALBUM_ART_LOCATION]);
  }
  else {
    album_art->set(Glib::get_home_dir() + "/fidel/Resources/Icons/library-icons/blank-albumart-icon.svg");
  }
  //album_art->show();
}
/*
void AlbumArt::set_songs_and_file_locs(vector<vector<Glib::ustring>> songs_and_file_locs)
{
this->songs_and_file_locs = songs_and_file_locs;
songs_in_album = songs_and_file_locs[0];
cout << "size of songs_and_file_locs " << songs_and_file_locs.size() << endl;
//song_file_locs = songs_and_file_locs[0];
}
*/

void AlbumArt::set_songs_in_album(vector<Glib::ustring> songs_in_album)
{
  this->songs_in_album = songs_in_album;
}
void AlbumArt::set_song_file_locs(vector<Glib::ustring> song_file_locs)
{
  this->song_file_locs = song_file_locs;
}

void AlbumArt::set_size(int width, int height)
{
  util::resize_image(album_art, width, height);
}

Glib::ustring AlbumArt::get_album_name()
{
  return album_name;
}

Gtk::Image* AlbumArt::get_art()
{
  return album_art;
}

vector<Glib::ustring> AlbumArt::get_songs_in_album()
{
  return songs_in_album;
}

vector<Glib::ustring> AlbumArt::get_song_file_locs()
{
  return song_file_locs;
}

vector<vector<Glib::ustring>> AlbumArt::get_songs_and_file_locs()
{
  return songs_and_file_locs;
}
