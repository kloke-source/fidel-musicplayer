#ifndef ALBUM_ART_VIEWER
#define ALBUM_ART_VIEWER
#include <gtkmm.h>
#include <iostream>
#include <vector>
#include <GUI/album-art.h>
#include <Utilities/util.h>
#include <Utilities/btree.h>
#include <Audio-Library/audio-library.h>

class AlbumArt;

class AlbumArtViewer : public Gtk::ScrolledWindow{
public:
  AlbumArtViewer();
  ~AlbumArtViewer();
 private:
  Gtk::Grid album_grid;

  bool initialized = false;
  int padding = 25;
  int curr_items_per_row = 0;
  int curr_row_amt = 0;
  int ideal_album_num = 8;
  int min_album_num = 1;

  double viewer_width;
  double min_album_width = 150;
  double ideal_album_width = 175;
  double max_block_width = 200;

  std::vector<AlbumArt> full_album_art;

  void init();
  void init_connections();
  void resize_handler(Gtk::Allocation& allocation);
  void set_items_per_row(int item_per_row);
};
#endif
