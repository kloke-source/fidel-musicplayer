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


void gui::initialize(int argc, char **argv)
{
  /*
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");

    Gtk::Window window;
    window.set_default_size(200, 200);

    app->run(window);
    */

    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "anorak.fidel");
  	builder = Gtk::Builder::create();
    gui::init_builder();
    builder->get_widget("window", window);
    app->run(*window);
}

void gui::init_builder()
{
  string ui_file_location = Glib::get_home_dir() + "/fidel/Resources/UI/fidel.ui";
  try
  {
    //builder->add_from_file(ui_file_location);
    //system("pwd");
    //Glib::RefPtr<Gio::Resource> fidel_res = Gio::Resource::create_from_file("src/GUI/fidel.gresource"); //works
    //Glib::RefPtr<Gio::Resource> fidel_res = (Gio::Resource*)fidel_get_resource();
    g_resources_register(Resource::fidel_get_resource());
      //fidel_res->register_global();
      builder->add_from_resource("/anorak/fidel/fidel.ui");
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
