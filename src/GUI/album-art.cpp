#include <gtkmm.h>
#include <iostream>
#include <GUI/album-art.h>
#include <Utilities/util.h>
#include <Utilities/btree.h>
#include <GUI/album-art-viewer.h>
#include <Audio-Info/audioinfo.h>
#include <GUI/album-art-viewer.h>
#include <Audio-Library/audio-library.h>

AlbumArt::AlbumArt(){}

AlbumArt::AlbumArt(AlbumSummary album_summ)
{
  AlbumArt::set(album_summ);
}

void AlbumArt::set(AlbumSummary album_summ)
{
  this->album_name = album_summ.album_name;
  this->songs_in_album = album_summ.songs_in_album;
  this->file_locations = album_summ.file_locations;
  this->total_songs_in_album  = album_summ.total_songs_in_album;

  std::cout << "Album Art test " << this->album_name << std::endl;
  std::cout << "Album Art test " << this->total_songs_in_album  << std::endl;

  this->album_art = audioinfo::get_album_art_by_name(this->album_name);
  this->original_pixbuf = this->album_art->get_pixbuf();
  this->scaled_pixbuf = this->album_art->get_pixbuf();

  this->pack_start(*this->album_art, Gtk::PACK_EXPAND_WIDGET);
  this->show_all();
}

void AlbumArt::set_size(double width, double height)
{
  this->scaled_pixbuf = this->original_pixbuf;
  this->scaled_pixbuf = scaled_pixbuf->scale_simple(width, height, Gdk::INTERP_BILINEAR);
  this->album_art->set(scaled_pixbuf);
  this->set_size_request(width, height);
}

Gtk::Image* AlbumArt::get_art()
{
  return this->album_art;
}

std::string AlbumArt::get_album_name()
{
  return this->album_name;
}
