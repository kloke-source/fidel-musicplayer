#ifndef PLAYLIST_QUEUE_HH
#define PLAYLIST_QUEUE_HH

#include <vector>
#include <gtkmm.h>
#include <GUI/playlist.h>
#include <GUI/fidel-popover.h>
#include <Utilities/util.h>

class FidelPopover;
class FidelOptions;

class PlaylistQueue : public Playlist{
 public:
  PlaylistQueue();
  PlaylistQueue(Gtk::Button *queue_overview_button);
  ~PlaylistQueue();

  void set_overview_button(Gtk::Button *queue_overview_button);
  void overview_notify();
 private:
  int max_popover_entries = 5;
  int default_image_size = 40;
  bool popover_hidden = false;
  
  std::vector<Gtk::Button*> queue_entries;
  std::vector<Gtk::Widget*> child_widgets;
  std::vector<Gtk::Image*> option_icons;
  Gtk::Image *queue_overview_notify_icon;
  Gtk::Image *queue_overview_icon;  
  Gtk::Button *queue_overview_button;
  FidelPopover *queue_overview_popover;

  void overview_reset();
  void init_connections();
  void show_first_song();
  
  // signal handlers
  void on_overview_button_enter();
  void on_overview_button_clicked();
};
#endif
