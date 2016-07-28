#include <GUI/fidel-popover.h>
#include <Utilities/util.h>
#include <vector>
#include <iostream>

FidelPopover::FidelPopover()
{
  this->popover_frame = new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5);
  this->add(*popover_frame);
}

FidelPopover::~FidelPopover()
{
  std::cout << "Fidel popover destructor called" << std::endl;
  std::cout << "Destructor popping" << std::endl;
  for (size_t iter = 0; iter < items_in_popover.size(); iter++) {
    FidelPopover::pop_item();      
  }
}

void FidelPopover::add_title(std::string title)
{
  Gtk::Box *entry = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL);
  Gtk::Label *label = new Gtk::Label();
  
  label->set_text(title);
  label->set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_CENTER);
  
  entry->pack_start(*label, Gtk::PACK_EXPAND_WIDGET);
  popover_frame->pack_start(*entry, Gtk::PACK_SHRINK);
  items_in_popover.emplace_back(PopoverEntries{entry, NULL, label, NULL, NULL});
}

void FidelPopover::add_entry(Gtk::Image *image, std::string label_text)
{
  Gtk::Box *entry = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5);
  Gtk::Label *label = new Gtk::Label();
  label->set_text(label_text);
  label->set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_CENTER);
  
  bool image_exists = false;
  for (size_t iter=0; iter < items_in_popover.size(); iter++) {
    if (image == items_in_popover[iter].image) {
      image_exists = true;
      break;
    }
  }

  if (image_exists == false) {
    util::resize_image(image, default_image_size, default_image_size);
    entry->pack_start(*image, Gtk::PACK_SHRINK);
    entry->pack_end(*label, Gtk::PACK_EXPAND_WIDGET);
    popover_frame->pack_start(*entry, Gtk::PACK_SHRINK);
    items_in_popover.emplace_back(PopoverEntries{entry, image, label, NULL, NULL});
  }
  if (image_exists == true) {
    std::cerr << "Error image pointer already in use\n";
  }
}

void FidelPopover::add_entry(Gtk::Image *image, std::string prim_label_text, std::string supp_label_text)
{
  Gtk::Box *entry = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5);
  Gtk::Box *label_container = new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 4);

  Gtk::Label *prim_label = new Gtk::Label();
  Gtk::Label *supp_label = new Gtk::Label();
  
  prim_label->set_text(prim_label_text);
  prim_label->set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_END);

  supp_label->set_text(supp_label_text);
  supp_label->set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_START);
  
  bool image_exists = false;
  for (size_t iter=0; iter < items_in_popover.size(); iter++) {
    if (image == items_in_popover[iter].image) {
      image_exists = true;
      break;
    }
  }

  if (image_exists == false) {
    util::resize_image(image, default_image_size, default_image_size);
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
  popover_frame->pack_start(*separator, Gtk::PACK_SHRINK);
  items_in_popover.emplace_back(PopoverEntries{NULL, NULL, NULL, NULL, separator});
}

void FidelPopover::pop_item()
{
  size_t pop_position = items_in_popover.size() - 1;
  Gtk::Box *removed_entry = items_in_popover[pop_position].entry;
  popover_frame->remove(*removed_entry);

  items_in_popover.erase(items_in_popover.begin() + pop_position - 1);
}
