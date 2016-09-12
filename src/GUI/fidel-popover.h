#ifndef FIDEL_POPOVER_HH
#define FIDEL_POPOVER_HH
#include <gtkmm.h>
#include <iostream>
#include <vector>
#include <GUI/fidel-options.h>

class FidelOptions;

class FidelPopover : public Gtk::Popover {
 public:
  FidelPopover();
  ~FidelPopover();

  void show_all();
  void clear();

  void set_policy(Gtk::PolicyType hscrollbar_policy, Gtk::PolicyType vscrollbar_policy);
    
  void add_text(std::string text);
  void add_text_with_widget(std::string text, Gtk::Widget *widget);
  void add_title(std::string title);
  void add_top_entry(Gtk::Button *button_entry);
  void add_entry(Gtk::Widget *widget);  
  void add_entry(Gtk::Image *image, std::string label_text);
  FidelOptions* add_entry(Gtk::Image *image, std::string prim_label_text, std::string supp_label_text);
  FidelOptions* add_entry(Gtk::Image *image, int image_size, std::string prim_label_text, std::string supp_label_text);
  void add_segmented_entry(FidelOptions *segmented_options, Gtk::Image *image, int image_size, std::string prim_label_text, std::string supp_label_text);
  void add_separator();
  void populate(std::vector<std::vector<std::string>> populate_data);
  
  void pop_from_top();
  void pop_item();
  
 private:
  Pango::FontDescription default_title_font;
  Pango::FontDescription default_prim_popover_font;
  Pango::FontDescription default_supp_popover_font;
  
  Gtk::Box *popover_frame;
  Gtk::ScrolledWindow *popover_scrolled_window;
  
  int default_image_size = 55;
  std::vector<Gtk::Widget*> toplevel_popover_entries;
  std::vector<Gtk::Widget*> widgets_in_popover;
  std::vector<Gtk::Widget*> fidel_options_vect;
  std::vector<Gtk::Image*> images_in_popover;
};
#endif
