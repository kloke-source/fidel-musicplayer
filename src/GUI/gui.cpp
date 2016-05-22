#include "gui.h"
#include <vector>
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



//Gtk::Image *play_icon;

GResource *fidel_resources;
void gui::initialize(int argc, char **argv)
{
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "anorak.fidel");

  Gtk::ApplicationWindow *window;
  Gtk::Box *main_layout;

  builder = Gtk::Builder::create();
  fidel_resources = Resource::fidel_get_resource();
  g_resources_register(fidel_resources);
  gui::init_builder();

  builder->get_widget("window", window);
  builder->get_widget("main_layout", main_layout);

  window->maximize();

  app->run(*window);
  g_resources_unregister(fidel_resources);
  //g_resource_unref(fidel_resources);
  //delete button;
  //delete window;
}

void gui::init_connections()
{
	//window->signal_delete_event().connect(sigc::mem_fun(this, &gui::on_window_closed));
}

bool gui::on_window_closed(GdkEventAny* event)
{
  //free(window);
  delete fidel_ui::Instance();
	return true;
}

void gui::init_builder()
{
  try
  {
    builder->add_from_resource("/fidel/Resources/fidel.ui");
  }
  catch(const Glib::FileError& error)
  {
    std::cerr << "FileError: " << error.what() << std::endl;
  }
  catch(const Glib::MarkupError& error)
  {
    std::cerr << "MarkupError: " << error.what() << std::endl;
  }
  catch(const Gtk::BuilderError& error)
  {
    std::cerr << "BuilderError: " << error.what() << std::endl;
  }
}
