#include "seeker.h"
#include <gtkmm.h>
#include <iostream>
#include <Utilities/util.h>
#include <Audio/playback.h>
#include <Audio-Info/audioinfo.h>

seeker::seeker(){}
seeker::~seeker(){}

using namespace std;

Glib::RefPtr<Gtk::Builder> seeker_builder;
Gtk::Dialog *seeker_dialog;

Gtk::Label *hours_label;
Gtk::Label *minutes_label;
Gtk::Label *seconds_label;
Gtk::Label *colon1;
Gtk::Label *colon2;
Gtk::Label *error_label;

Gtk::Button *seek_button;
Gtk::Button *cancel_button;

Gtk::Entry *hours_tenths_entry;
Gtk::Entry *hours_units_entry;
Gtk::Entry *minutes_tenths_entry;
Gtk::Entry *minutes_units_entry;
Gtk::Entry *seconds_tenths_entry;
Gtk::Entry *seconds_units_entry;

bool hours_deleted;
bool minutes_deleted;

void seeker::kill()
{
  delete seeker_dialog;
  if (hours_deleted == false){
    delete colon1;
    delete hours_label;
    delete hours_tenths_entry;
    delete hours_units_entry;
  }
  if (minutes_deleted == false){
    delete colon2;
    delete minutes_label;
    delete minutes_tenths_entry;
    delete minutes_units_entry;
  }
  delete seconds_label;
  delete error_label;
  delete seek_button;
  delete cancel_button;
  delete seconds_tenths_entry;
  delete seconds_units_entry;
}
void seeker::show(Gtk::Window *parent)
{
  seeker::init();
  seeker_dialog->set_transient_for(*parent);
  seeker_dialog->run();
}

void seeker::seek()
{
  int hours=0, minutes=0, seconds=0;
  if (hours_deleted == false){
    hours = util::to_int(hours_tenths_entry->get_text() + "0") + util::to_int(hours_units_entry->get_text());
  }
  if (minutes_deleted == false){
    minutes = util::to_int(minutes_tenths_entry->get_text() + "0") + util::to_int(minutes_units_entry->get_text());
  }
  seconds = util::to_int(seconds_tenths_entry->get_text() + "0") + util::to_int(seconds_units_entry->get_text());

  int seek_value = util::seconds_format(hours, minutes, seconds);

  if (seek_value <= audioinfo::duration()){
    seeker::kill();
    playback::seek(seek_value, "seeker");
  }
  if (seek_value > audioinfo::duration()) {
    cout << "called this fkjafeal" << endl;
    if (hours_deleted == false){
      hours_tenths_entry->set_text("");
      hours_units_entry->set_text("");
    }
    if (minutes_deleted == false){
      minutes_tenths_entry->set_text("");
      minutes_units_entry->set_text("");
    }
    seconds_tenths_entry->set_text("");
    seconds_units_entry->set_text("");
    error_label->set_text("The entered seek value is too big");
    seeker::set_entry_focus();
  }
}

void seeker::init()
{
  seeker_builder = Gtk::Builder::create();
  seeker::init_builder();

  hours_deleted = false;
  minutes_deleted = false;

  //initalize elements
  seeker_builder->get_widget("seeker_dialog", seeker_dialog);
  seeker_builder->get_widget("hours_label", hours_label);
  seeker_builder->get_widget("minutes_label", minutes_label);
  seeker_builder->get_widget("seconds_label", seconds_label);
  seeker_builder->get_widget("error_label", error_label);
  seeker_builder->get_widget("colon1", colon1);
  seeker_builder->get_widget("colon2", colon2);
  seeker_builder->get_widget("cancel_button", cancel_button);
  seeker_builder->get_widget("seek_button", seek_button);
  seeker_builder->get_widget("hours_tenths_entry", hours_tenths_entry);
  seeker_builder->get_widget("hours_units_entry", hours_units_entry);
  seeker_builder->get_widget("minutes_tenths_entry", minutes_tenths_entry);
  seeker_builder->get_widget("minutes_units_entry", minutes_units_entry);
  seeker_builder->get_widget("seconds_tenths_entry", seconds_tenths_entry);
  seeker_builder->get_widget("seconds_units_entry", seconds_units_entry);
  //end of initialization

  //initialize connections
  seeker::init_connections();
  //end

  //set up fonts
  Pango::FontDescription digital_font;
  digital_font.set_family("DS-Digital");
  digital_font.set_size(120 * PANGO_SCALE);

  Pango::FontDescription digital_button_font;
  digital_button_font.set_family("DS-Digital");
  digital_button_font.set_size(25 * PANGO_SCALE);

  Pango::FontDescription digital_label_font;
  digital_label_font.set_family("DS-Digital");
  digital_label_font.set_size(40 * PANGO_SCALE);

  Pango::FontDescription error_font;
  error_font.set_family("Open Sans");
  error_font.set_size(14 * PANGO_SCALE);
  //end of setup

  //set element fonts
  hours_label->override_font(digital_label_font);
  minutes_label->override_font(digital_label_font);
  seconds_label->override_font(digital_label_font);
  error_label->override_font(error_font);

  seek_button->override_font(digital_button_font);
  cancel_button->override_font(digital_button_font);

  hours_tenths_entry->override_font(digital_font);
  hours_units_entry->override_font(digital_font);
  minutes_tenths_entry->override_font(digital_font);
  minutes_units_entry->override_font(digital_font);
  seconds_tenths_entry->override_font(digital_font);
  seconds_units_entry->override_font(digital_font);
  //end

  //set element background colors
  seeker_dialog->override_background_color(Gdk::RGBA("#2D2D2D"));

  colon1->override_color(Gdk::RGBA("#000000"));
  colon2->override_color(Gdk::RGBA("#000000"));

  hours_tenths_entry->override_background_color(Gdk::RGBA("#000000"));
  hours_units_entry->override_background_color(Gdk::RGBA("#000000"));
  minutes_tenths_entry->override_background_color(Gdk::RGBA("#000000"));
  minutes_units_entry->override_background_color(Gdk::RGBA("#000000"));
  seconds_tenths_entry->override_background_color(Gdk::RGBA("#000000"));
  seconds_units_entry->override_background_color(Gdk::RGBA("#000000"));
  //end

  //set widget colors
  hours_label->override_color(Gdk::RGBA("#ffffff"));
  minutes_label->override_color(Gdk::RGBA("#ffffff"));
  seconds_label->override_color(Gdk::RGBA("#ffffff"));
  error_label->override_color(Gdk::RGBA("#ff0000"));

  hours_tenths_entry->override_color(Gdk::RGBA("#ffffff"));
  hours_units_entry->override_color(Gdk::RGBA("#ffffff"));
  minutes_tenths_entry->override_color(Gdk::RGBA("#ffffff"));
  minutes_units_entry->override_color(Gdk::RGBA("#ffffff"));
  seconds_tenths_entry->override_color(Gdk::RGBA("#ffffff"));
  seconds_units_entry->override_color(Gdk::RGBA("#ffffff"));
  //end

  //set element cursor colors
  hours_tenths_entry->override_cursor(Gdk::RGBA("#ee2e2e"), Gdk::RGBA("#ee2e2e"));
  hours_units_entry->override_cursor(Gdk::RGBA("#ee2e2e"), Gdk::RGBA("#ee2e2e"));
  minutes_tenths_entry->override_cursor(Gdk::RGBA("#ee2e2e"), Gdk::RGBA("#ee2e2e"));
  minutes_units_entry->override_cursor(Gdk::RGBA("#ee2e2e"), Gdk::RGBA("#ee2e2e"));
  seconds_tenths_entry->override_cursor(Gdk::RGBA("#ee2e2e"), Gdk::RGBA("#ee2e2e"));
  seconds_units_entry->override_cursor(Gdk::RGBA("#ee2e2e"), Gdk::RGBA("#ee2e2e"));
  //end

  seeker::set_entry_focus();
}

void seeker::init_builder()
{
  string ui_filelocation = Glib::get_home_dir() + "/fidel/Resources/UI/seeker.ui";
  try
  {
    seeker_builder->add_from_file(ui_filelocation);
  }
  catch(const Glib::FileError& ex)
  {
    std::cerr << "FileError: " << ex.what() << std::endl;
    std::cout << "Try running configure script again " << endl;
  }
  catch(const Glib::MarkupError& ex)
  {
    std::cerr << "MarkupError: " << ex.what() << std::endl;
  }
  catch(const Gtk::BuilderError& ex)
  {
    std::cerr << "BuilderError: " << ex.what() << std::endl;
  }
}

void seeker::init_connections()
{
  seek_button->signal_clicked().connect(sigc::ptr_fun(seeker::seek));
  seek_button->signal_focus_in_event().connect(sigc::ptr_fun(seeker::on_seek_button_focused));
  seek_button->signal_focus_out_event().connect(sigc::ptr_fun(seeker::on_seek_button_unfocused));
  seek_button->signal_enter_notify_event().connect(sigc::ptr_fun(seeker::on_seek_button_hover));
  seek_button->signal_leave_notify_event().connect(sigc::ptr_fun(seeker::on_seek_button_leave));
  cancel_button->signal_clicked().connect(sigc::ptr_fun(seeker::kill));
  cancel_button->signal_focus_in_event().connect(sigc::ptr_fun(seeker::on_cancel_button_focused));
  cancel_button->signal_focus_out_event().connect(sigc::ptr_fun(seeker::on_cancel_button_unfocused));
  cancel_button->signal_enter_notify_event().connect(sigc::ptr_fun(seeker::on_cancel_button_hover));
  cancel_button->signal_leave_notify_event().connect(sigc::ptr_fun(seeker::on_cancel_button_leave));
  hours_tenths_entry->signal_insert_text().connect(sigc::ptr_fun(seeker::hours_tenths_handler));
  hours_units_entry->signal_insert_text().connect(sigc::ptr_fun(seeker::hours_units_handler));
  minutes_tenths_entry->signal_insert_text().connect(sigc::ptr_fun(seeker::minutes_tenths_handler));
  minutes_units_entry->signal_insert_text().connect(sigc::ptr_fun(seeker::minutes_units_handler));
  seconds_tenths_entry->signal_insert_text().connect(sigc::ptr_fun(seeker::seconds_tenths_handler));
  seconds_units_entry->signal_insert_text().connect(sigc::ptr_fun(seeker::seconds_units_handler));
}

bool seeker::on_seek_button_focused(GdkEventFocus* event)
{
  seek_button->override_background_color(Gdk::RGBA("#242624"));
  return true;
}

bool seeker::on_seek_button_unfocused(GdkEventFocus* event)
{
  seek_button->override_background_color(Gdk::RGBA("#F0F0F0"));
  return true;
}

bool seeker::on_seek_button_hover(GdkEventCrossing* event)
{
  seek_button->override_background_color(Gdk::RGBA("#242624"));
  return true;
}

bool seeker::on_seek_button_leave(GdkEventCrossing* event)
{
  seek_button->override_background_color(Gdk::RGBA("#F0F0F0"));
  return true;
}

bool seeker::on_cancel_button_focused(GdkEventFocus* event)
{
  cancel_button->override_background_color(Gdk::RGBA("#db2c2c"));
  return true;
}

bool seeker::on_cancel_button_unfocused(GdkEventFocus* event)
{
  cancel_button->override_background_color(Gdk::RGBA("#F0F0F0"));
  return true;
}

bool seeker::on_cancel_button_hover(GdkEventCrossing* event)
{
  cancel_button->override_background_color(Gdk::RGBA("#db2c2c"));
  return true;
}

bool seeker::on_cancel_button_leave(GdkEventCrossing* event)
{
  cancel_button->override_background_color(Gdk::RGBA("#F0F0F0"));
  return true;
}

void seeker::set_entry_focus()
{
  cout << "set_entry_focus called " << endl;
  cout << "Duration" << audioinfo::duration() << endl;

  if (audioinfo::duration() <= (9*3600) && audioinfo::duration() > (59*60)){
    hours_units_entry->grab_focus();
  }
  if (audioinfo::duration() <= (59*60)){
    delete colon1;
    delete hours_label;
    delete hours_tenths_entry;
    delete hours_units_entry;
    hours_deleted = true;
  }
  if (audioinfo::duration() <= (59*60) && audioinfo::duration() > (9*60)){
    minutes_tenths_entry->grab_focus();
  }
  if (audioinfo::duration() <= (9*60) && audioinfo::duration() > 60){
    minutes_units_entry->grab_focus();
  }
  if (audioinfo::duration() <= 60 && audioinfo::duration() > 9){
    delete colon2;
    delete minutes_label;
    delete minutes_tenths_entry;
    delete minutes_units_entry;
    minutes_deleted = true;
    seconds_tenths_entry->grab_focus();
  }
  if (audioinfo::duration() <= 9){
    delete colon2;
    delete minutes_label;
    delete minutes_tenths_entry;
    delete minutes_units_entry;
    minutes_deleted = true;
    seconds_units_entry->grab_focus();
  }
}

void seeker::data_validator(Glib::ustring text,
  int *character_num, Gtk::Entry *data_entry_widget)
  {
    try {
      int value = util::to_int(text);
      if (util::to_string(value) != text)
      {
        throw 0;
      }
    }
    catch (int exception)
    {
      data_entry_widget->delete_text(0,1);
    }
  }

  //initialize data entry handlers
  void seeker::hours_tenths_handler(const Glib::ustring& text,int* character_num)
  {
    if (error_label->get_text() != ""){
      error_label->set_text("");
    }
    seeker::data_validator(text, character_num, hours_tenths_entry);
  }
  void seeker::hours_units_handler(const Glib::ustring& text,int* character_num)
  {
    if (error_label->get_text() != ""){
      error_label->set_text("");
    }
    seeker::data_validator(text, character_num, hours_units_entry);
  }
  void seeker::minutes_tenths_handler(const Glib::ustring& text,int* character_num)
  {
    if (error_label->get_text() != ""){
      error_label->set_text("");
    }
    seeker::data_validator(text, character_num, minutes_tenths_entry);
  }
  void seeker::minutes_units_handler(const Glib::ustring& text,int* character_num)
  {
    if (error_label->get_text() != ""){
      error_label->set_text("");
    }
    seeker::data_validator(text, character_num, minutes_units_entry);
  }
  void seeker::seconds_tenths_handler(const Glib::ustring& text,int* character_num)
  {
    if (error_label->get_text() != ""){
      error_label->set_text("");
    }
    seeker::data_validator(text, character_num, seconds_tenths_entry);
  }
  void seeker::seconds_units_handler(const Glib::ustring& text,int* character_num)
  {
    if (error_label->get_text() != ""){
      error_label->set_text("");
    }
    seeker::data_validator(text, character_num, seconds_units_entry);
  }
  //end of initialization
