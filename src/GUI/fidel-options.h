#ifndef FIDEL_OPTIONS_HH
#define FIDEL_OPTIONS_HH

#include <gtkmm.h>
#include <GUI/gui.h>
#include <Utilities/util.h>
#include <GUI/fidel-popover.h>

class FidelOptions : public Gtk::Button {
 public:
  FidelOptions();
  ~FidelOptions();

  // enums
  enum IconType {
    HORIZONTAL_ICON,
    VERTICAL_ICON
  };
  
  void initialize();
  void init_connections();
 private:
  int default_font_size = 11;
  bool popover_hidden = true;
  Pango::FontDescription default_font;
  
  Gtk::Button *play_next_button;
  Gtk::Button *add_to_bottom_of_queue_button;
  
  Gtk::Box *play_next_container;
  Gtk::Box *add_to_bottom_of_queue_container;
  
  Gtk::Image *view_more_horizontal_icon;
  Gtk::Image *view_more_vertical_icon;
  Gtk::Image *play_next_icon;
  Gtk::Image *add_to_bottom_of_queue_icon;
  
  Gtk::Label *play_next_label;
  Gtk::Label *add_to_bottom_of_queue_label;
  FidelPopover *options_popover;

  //signal handlers
  void on_clicked() override;
};
#endif
