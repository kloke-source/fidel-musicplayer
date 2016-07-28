#ifndef FIDEL_POPOVER_HH
#define FIDEL_POPOVER_HH
#include <gtkmm.h>
#include <iostream>
#include <vector>

class FidelPopover : public Gtk::Popover {
 public:
  FidelPopover();
  ~FidelPopover();

  void add_title(std::string title);
  void add_entry(Gtk::Image *image, std::string label_text);
  void add_entry(Gtk::Image *image, std::string prim_label_text, std::string supp_label_text);
  void add_separator();

  void pop_item();
 private:
  Gtk::Box *popover_frame;
  int default_image_size = 55;

  struct PopoverEntries {
    Gtk::Box *entry;
    Gtk::Image *image;
    Gtk::Label *prim_label;
    Gtk::Label *supp_label;
    Gtk::Separator *separator;
  };
  
  std::vector<PopoverEntries> items_in_popover;
};
#endif
