#ifndef ALBUM_ART
#define ALBUM_ART
#include <gtkmm.h>
#include <iostream>
#include <Utilities/util.h>
#include <Utilities/btree.h>
#include <GUI/album-art-viewer.h>
#include <Audio-Info/audioinfo.h>
#include <GUI/album-art-viewer.h>
#include <Audio-Library/audio-library.h>

class AlbumArt : public Gtk::Box{
public:
  AlbumArt();
  AlbumArt(AlbumSummary album_summ);

  std::string album_name;
  
  void set(AlbumSummary album_summ);
  void set_size(double width, double height);

  Gtk::Image* get_art();
  std::string get_album_name();
 private:
  Gtk::Image *album_art;
  Glib::RefPtr<Gdk::Pixbuf> original_pixbuf;
  Glib::RefPtr<Gdk::Pixbuf> scaled_pixbuf;

  btree<std::string> songs_in_album;
  std::vector<std::string> file_locations;
  int total_songs_in_album;
};

#endif
