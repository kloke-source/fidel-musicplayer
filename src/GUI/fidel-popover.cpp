#include <GUI/fidel-popover.h>
#include <Utilities/util.h>
#include <Audio-Info/audioinfo.h>
#include <Audio-Library/audio-library.h>
#include <vector>
#include <iostream>

FidelPopover::FidelPopover()
{
  this->popover_frame = new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5);
  this->set_size_request(300, 0);
  this->add(*popover_frame);

  default_title_font.set_family("Open Sans Light");
  default_title_font.set_size(12.5 * PANGO_SCALE);
  
  default_prim_popover_font.set_family("Open Sans Light");
  default_prim_popover_font.set_size(11 * PANGO_SCALE);

  default_supp_popover_font.set_family("Open Sans Light");
  default_supp_popover_font.set_size(10.5 * PANGO_SCALE);
}

FidelPopover::~FidelPopover()
{
  std::cout << "Fidel popover destructor called" << std::endl;
  std::cout << "Destructor popping" << std::endl;
  FidelPopover::clear();
}

void FidelPopover::clear()
{
  while (items_in_popover.size())
    FidelPopover::pop_item();
}

void FidelPopover::add_title(std::string title)
{
  Gtk::Box *entry = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL);
  Gtk::Label *label = new Gtk::Label();
  
  label->set_markup("<b>" + title + "</b>");
  label->set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_CENTER);
  label->set_margin_left(7);
  label->override_font(default_title_font);
  
  entry->pack_start(*label, Gtk::PACK_EXPAND_WIDGET);
  popover_frame->pack_start(*entry, Gtk::PACK_SHRINK);
  items_in_popover.emplace_back(PopoverEntries{entry, NULL, label, NULL, NULL});
  FidelPopover::add_separator();
}

void FidelPopover::add_entry(Gtk::Image *image, std::string label_text)
{
  Gtk::Box *entry = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5);
  Gtk::Label *label = new Gtk::Label();
  label->set_markup("<b>" + label_text + "</b>");
  label->set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_CENTER);
  label->override_font(default_prim_popover_font);  

  bool image_exists = false;
  for (size_t iter=0; iter < items_in_popover.size(); iter++) {
    if (image == items_in_popover[iter].image) {
      image_exists = true;
      break;
    }
  }

  if (image_exists == false) {
    util::resize_image(image, default_image_size, default_image_size);
    image->set_margin_left(15);
    entry->pack_start(*image, Gtk::PACK_SHRINK);
    entry->pack_end(*label, Gtk::PACK_EXPAND_WIDGET);
    popover_frame->pack_start(*entry, Gtk::PACK_SHRINK);
    items_in_popover.emplace_back(PopoverEntries{entry, image, label, NULL, NULL});
  }
  if (image_exists == true) {
    std::cerr << "Error image pointer already in use\n";
  }
}

void FidelPopover::add_entry(std::pair<guint8*, gsize> image, std::string prim_label_text, std::string supp_label_text)
{
  Glib::RefPtr<Gdk::PixbufLoader> loader = Gdk::PixbufLoader::create();
  loader->write(image.first, image.second);
  loader->close();
  Glib::RefPtr<Gdk::Pixbuf> pixbuf = loader->get_pixbuf();
  Gtk::Image gtk_image;
  gtk_image.set(pixbuf);
  FidelPopover::add_entry(&gtk_image, prim_label_text, supp_label_text);
}

void FidelPopover::add_entry(Gtk::Image *image, std::string prim_label_text, std::string supp_label_text)
{
  Gtk::Box *entry = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5);
  Gtk::Box *label_container = new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 4);

  Gtk::Label *prim_label = new Gtk::Label();
  Gtk::Label *supp_label = new Gtk::Label();
  
  prim_label->set_markup("<b>" + prim_label_text + "</b>");
  prim_label->set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_END);
  prim_label->override_font(default_prim_popover_font);
  
  supp_label->set_text(supp_label_text);
  supp_label->set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_START);
  supp_label->override_color(Gdk::RGBA("#616161"));
  supp_label->override_font(default_supp_popover_font);
  
  bool image_exists = false;
  for (size_t iter = 0; iter < items_in_popover.size(); iter++) {
    if (image == items_in_popover[iter].image) {
      image_exists = true;
      break;
    }
  }

  if (image_exists == false) {
    util::resize_image(image, default_image_size, default_image_size);
    image->set_margin_left(15);
    image->set_margin_right(5);
    entry->pack_start(*image, Gtk::PACK_SHRINK);
	
    label_container->pack_start(*prim_label, Gtk::PACK_EXPAND_WIDGET);
    label_container->pack_end(*supp_label, Gtk::PACK_EXPAND_WIDGET);
    
    entry->pack_end(*label_container, Gtk::PACK_EXPAND_WIDGET);
    popover_frame->pack_start(*entry, Gtk::PACK_SHRINK);
    items_in_popover.emplace_back(PopoverEntries{entry, image, prim_label, supp_label, NULL});
  }
  if (image_exists == true) {
    std::cerr << "Error image pointer already in use\n";
  }  
}

void FidelPopover::add_separator()
{
  Gtk::Separator *separator = new Gtk::Separator(Gtk::ORIENTATION_HORIZONTAL);
  Gtk::Box *separator_container = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL);
  separator_container->pack_start(*separator, Gtk::PACK_EXPAND_WIDGET);
  popover_frame->pack_start(*separator_container, Gtk::PACK_SHRINK);
  items_in_popover.emplace_back(PopoverEntries{separator_container, NULL, NULL, NULL, separator});
}

void FidelPopover::populate(std::vector<std::vector<std::string>> populate_data)
{
  FidelPopover::clear();
  FidelPopover::add_title("Songs");

  if (populate_data.size() && populate_data.size() == 4) {
    for (size_t iter = 0; iter < populate_data[Playlist::FILE_LOC].size(); iter++) {
      std::string song_name = Glib::Markup::escape_text(populate_data[Playlist::SONG_NAME][iter]);
      std::string supp_label = populate_data[Playlist::ARTIST][iter] + " \u2015 " + populate_data[Playlist::ALBUM][iter]; // \u2015 is the unicode character for horizontal bar
      std::tuple<guint8*, gsize, bool> raw_image = audioinfo::extract_album_art(populate_data[Playlist::FILE_LOC][iter]);
      Gtk::Image *album_art = new Gtk::Image();
      bool album_art_exists = false;
      if (std::get<2>(raw_image) == true) {
	Glib::RefPtr<Gdk::PixbufLoader> loader = Gdk::PixbufLoader::create();
	loader->write(std::get<0>(raw_image), std::get<1>(raw_image));
	loader->close();
	Glib::RefPtr<Gdk::Pixbuf> pixbuf = loader->get_pixbuf();
	album_art->set(pixbuf);
	album_art_exists = true;
      }
      if (album_art_exists == false)
	album_art->set_from_resource("/fidel/Resources/icons/blank-albumart.svg");      
      FidelPopover::add_entry(album_art, song_name, supp_label);
    if (iter == 3)
      break;      
    }
  }
}

void FidelPopover::pop_item()
{
  size_t pop_position = items_in_popover.size() - 1;
  Gtk::Box *removed_entry = items_in_popover[pop_position].entry;
  popover_frame->remove(*removed_entry);

  items_in_popover.erase(items_in_popover.begin() + pop_position);
}
