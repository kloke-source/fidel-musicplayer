#include <GUI/fidel-options.h>

FidelOptions::FidelOptions()
{
  FidelOptions::initialize();
  FidelOptions::init_connections();  
}

FidelOptions::~FidelOptions(){}

void FidelOptions::initialize()
{
  options_popover = new FidelPopover();

  default_font.set_family("Open Sans Light");
  default_font.set_size(default_font_size * PANGO_SCALE);  
    
  play_next_button = new Gtk::Button();
  add_to_bottom_of_queue_button = new Gtk::Button();

  play_next_container = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5);
  add_to_bottom_of_queue_container = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5);
  
  view_more_horizontal_icon = new Gtk::Image();
  view_more_vertical_icon = new Gtk::Image();
  play_next_icon = new Gtk::Image();
  add_to_bottom_of_queue_icon = new Gtk::Image();
  
  play_next_label = new Gtk::Label("Play Next");
  add_to_bottom_of_queue_label = new Gtk::Label("Add to bottom of Queue");
  
  view_more_horizontal_icon->set_from_resource("/fidel/Resources/icons/view-more-horizontal.svg");
  view_more_vertical_icon->set_from_resource("/fidel/Resources/icons/view-more-vertical.svg");
  play_next_icon->set_from_resource("/fidel/Resources/icons/play-next.svg");
  add_to_bottom_of_queue_icon->set_from_resource("/fidel/Resources/icons/add-to-bottom-of-queue.svg");

  this->add(*view_more_vertical_icon);
  
  play_next_label->set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_CENTER);
  //play_next_label->set_margin_left(5);
  play_next_label->override_font(default_font);  
  add_to_bottom_of_queue_label->set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_CENTER);
  add_to_bottom_of_queue_label->override_font(default_font);  
  //add_to_bottom_of_queue_label->set_margin_left(5);

  play_next_container->pack_start(*play_next_icon, Gtk::PACK_SHRINK);
  add_to_bottom_of_queue_container->pack_start(*add_to_bottom_of_queue_icon, Gtk::PACK_SHRINK);  
  play_next_container->pack_end(*play_next_label, Gtk::PACK_EXPAND_WIDGET);
  add_to_bottom_of_queue_container->pack_end(*add_to_bottom_of_queue_label, Gtk::PACK_EXPAND_WIDGET);
  
  play_next_button->add(*play_next_container);
  add_to_bottom_of_queue_button->add(*add_to_bottom_of_queue_container);
  
  play_next_button->set_relief(Gtk::RELIEF_NONE);
  add_to_bottom_of_queue_button->set_relief(Gtk::RELIEF_NONE);
  this->set_relief(Gtk::RELIEF_NONE);
  
  options_popover->add_entry(play_next_button);
  options_popover->add_entry(add_to_bottom_of_queue_button);
  options_popover->set_relative_to(*this);
  options_popover->set_size_request(0, 0);
}

void FidelOptions::init_connections()
{
}

void FidelOptions::show_popover()
{
  options_popover->show_all();
}

void FidelOptions::hide_popover()
{
  options_popover->hide();
}

void FidelOptions::set_position(Gtk::PositionType position)
{
  options_popover->set_position(position);
}

void FidelOptions::set_relative_to(const Gtk::Widget& widget)
{
  options_popover->set_relative_to(widget);
}

void FidelOptions::set_pointing_to(const Gdk::Rectangle& rect)
{
  options_popover->set_pointing_to(rect);
}

void FidelOptions::set_play_next_cb(std::function<void()> cb_func)
{
  play_next_button->signal_clicked().connect(cb_func);
}

void FidelOptions::set_add_to_bottom_of_queue_cb(std::function<void()> cb_func)
{
  add_to_bottom_of_queue_button->signal_clicked().connect(cb_func);
}

Gtk::Image* FidelOptions::get_icon()
{
  Gtk::Image *icon = new Gtk::Image();
  icon->set(view_more_vertical_icon->get_pixbuf());
  return icon;
}

Gtk::Image* FidelOptions::get_icon(IconType icon_type)
{
  switch (icon_type) {
  case HORIZONTAL_ICON: {
    Gtk::Image *icon = new Gtk::Image();
    icon->set(view_more_horizontal_icon->get_pixbuf());    
    return icon;
    break;
  }
  case VERTICAL_ICON: {
    Gtk::Image *icon = new Gtk::Image();
    icon->set(view_more_vertical_icon->get_pixbuf());    
    return icon;
    break;
  }
  }
}

FidelPopover* FidelOptions::get_popover()
{
  return options_popover;
}							  

Gtk::Button* FidelOptions::get_play_next_button()
{
  return play_next_button;
}
