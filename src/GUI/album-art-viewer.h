#ifndef ALBUM_ART_VIEWER
#define ALBUM_ART_VIEWER
#include <gtkmm.h>
#include <iostream>
#include <GUI/album-art.h>
#include <Utilities/util.h>
#include <Utilities/btree.h>
#include <Audio-Library/audio-library.h>

using namespace std;
class AlbumArtViewer{
public:
  AlbumArtViewer();
  AlbumArtViewer(Gtk::Widget *parent);
  ~AlbumArtViewer();
  Gtk::Box* get_frame();
  void init();
  void init(Gtk::Widget *parent);
  void show();
private:
  int frame_width;
  int frame_height;
  Gtk::Widget *parent;
  Gtk::Grid *album_grid;
  Gtk::Box *viewer_frame;
  Gtk::ScrolledWindow *viewer_scrolled_window;
  void connect_signals();
  void resize_children(int size);
  void set_items_per_row(int item_per_row);
  void resize_handler(Gtk::Allocation &allocation);
};
#endif
