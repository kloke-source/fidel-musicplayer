#ifndef FIDEL_POPOVER_HH
#define FIDEL_POPOVER_HH
#include <gtkmm.h>
#include <iostream>
#include <vector>

class FidelPopover : public Gtk::Popover {
 public:
  FidelPopover();
  ~FidelPopover();

  void clear();
  
  void add_title(std::string title);
  void add_entry(Gtk::Button *button_entry);
  void add_entry(Gtk::Image *image, std::string label_text);
  void add_entry(Gtk::Image *image, std::string prim_label_text, std::string supp_label_text);
  void add_entry(std::pair<guint8*, gsize> image, std::string prim_label_text, std::string supp_label_text);
  void add_separator();
  void populate(std::vector<std::vector<std::string>> populate_data);
  void pop_item();
 private:
  Pango::FontDescription default_title_font;
  Pango::FontDescription default_prim_popover_font;
  Pango::FontDescription default_supp_popover_font;
  
  Gtk::Box *popover_frame;
  
  int default_image_size = 55;

  struct AudioData {
    std::string song_name;
    std::string artist_name;
    std::string album_name;
    std::string file_location;
  };
  
  struct PopoverEntries {
    Gtk::Button *button_entry;
    Gtk::Box *entry;
    Gtk::Image *image;
    Gtk::Label *prim_label;
    Gtk::Label *supp_label;
    Gtk::Separator *separator;
  };
  
  std::vector<PopoverEntries> items_in_popover;
};
#endif
