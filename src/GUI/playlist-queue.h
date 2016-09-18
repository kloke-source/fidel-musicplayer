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

  enum PrevOverviewState {
    OVERVIEW_HIDDEN,
    FIRST_SONG_SHOWN,
    FULL_OVERVIEW_SHOWN
  };
  
  int max_popover_entries = 5;
  int default_image_size = 40;
  bool show_more_less_click_inconsistency = false;
  bool overview_show_prev_state = false;
  bool show_more_less_clicked_once = false;

  PrevOverviewState prev_overview_state;
  
  std::vector<Gtk::Button*> queue_entries;
  std::vector<Gtk::Widget*> child_widgets;
  std::vector<Gtk::Image*> option_icons;
  Gtk::Image *queue_overview_notify_icon;
  Gtk::Image *queue_overview_icon;  
  Gtk::Button *queue_overview_button;
  Gtk::Button *overview_show_more_less_button;
  
  FidelPopover *queue_overview_popover;
  
  void initialize();
  void init_connections();
  std::vector<std::string> get_up_next();
  std::vector<std::vector<std::string>> get_all_up_next();
  void overview_notify_reset();  
  void overview_show();  
  void show_first_song();
  void show_all_songs();
  
  // signal handlers
  void on_overview_button_enter();
  void on_overview_button_clicked();
  void on_overview_show_more_less_clicked();
};
#endif
