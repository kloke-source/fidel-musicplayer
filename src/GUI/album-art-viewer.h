#ifndef ALBUM_ART_VIEWER
#define ALBUM_ART_VIEWER
#include <gtkmm.h>
#include <iostream>
#include <GUI/album-art.h>
#include <Utilities/util.h>
#include <Utilities/btree.h>
#include <Audio-Library/audio-library.h>

class AlbumArtViewer : public Gtk::ScrolledWindow{
public:
  AlbumArtViewer();
  ~AlbumArtViewer();
 private:
  Gtk::Grid album_grid;

  int padding = 25;
  int ideal_album_num = 8;
  int unideal_album_num = 4;
  int min_album_num = 1;

  double viewer_width;
  double min_album_width = 150;
  double ideal_album_width = 175;
  double max_block_width = 200;

  void init();
  void init_connections();
  void resize_handler(Gtk::Allocation& allocation);
};
#endif
