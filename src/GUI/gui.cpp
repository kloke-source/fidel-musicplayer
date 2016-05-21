#include "gui.h"
#include <gtkmm.h>
#include <iostream>
#include <gio/gio.h>
#include <GUI/fidel-resources.h>
//#include <GUI/seeker.h>
//#include <Utilities/util.h>
//#include <Utilities/btree.h>
//#include <Audio/playback.h>
//#include <Spectrum/spectrum.h>
//#include <Audio-Info/audioinfo.h>
//#include <GUI/album-art-viewer.h>
//#include <Audio-Library/audio-library.h>

gui::gui(){}
gui::~gui(){}

Glib::RefPtr<Gtk::Builder> builder;
Gtk::Window *window;

Gtk::Button *play_button;
Gtk::Image *play_icon;


void gui::initialize(int argc, char **argv)
{
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "anorak.fidel");
  builder = Gtk::Builder::create();
  g_resources_register(Resource::fidel_get_resource());

  gui::init_builder();
  builder->get_widget("window", window);

  builder->get_widget("play_button", play_button);
  play_icon = new Gtk::Image();
  play_icon->set_from_resource("/fidel/Resources/playback-play.svg");
  play_button->add(*play_icon);

  play_icon->show();
  play_button->show();

  window->maximize();
  app->run(*window);
}

void gui::init_builder()
{
  try
  {
    //g_resources_register(Resource::fidel_get_resource());
    builder->add_from_resource("/fidel/Resources/fidel.ui");
  }
  catch(const Glib::FileError& ex)
  {
    std::cerr << "FileError: " << ex.what() << std::endl;
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
