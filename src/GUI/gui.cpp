#include "gui.h"
#include <vector>
#include <gtkmm.h>
#include <iostream>
#include <gio/gio.h>
#include <GUI/fidel-resources.h>
//#include <GUI/seeker.h>
#include <Utilities/util.h>
//#include <Utilities/btree.h>
#include <Audio/playback.h>
//#include <Spectrum/spectrum.h>
//#include <Audio-Info/audioinfo.h>
//#include <GUI/album-art-viewer.h>
//#include <Audio-Library/audio-library.h>

gui::gui(){}
gui::~gui(){}

GResource *fidel_resources;
Builder builder;
ApplicationWindow *window;

Toolbar *toolbar;
ImageMenuItem *open_action;
Notebook *view_switcher;
Entry *playlist_search_entry;

Label *split_view_label;
Label *playlist_view_label;
Label *library_view_label;
Label *spectrum_view_label;
Label *idle_status_label;
Label *playback_timer;
Label *playback_endtime;
Label *sidebar_name_label;
Label *sidebar_artist_label;
Label *sidebar_album_label;
Label *sidebar_song_name;
Label *sidebar_song_artist;
Label *sidebar_song_album;

Box *split_view_layout;
Box *split_view_spectrum;
Box *split_view_playlist;
Box *library_view_frame;
Box *playback_frame;
Box *playlist_view;
Box *playback_slider_frame;
Box *sidebar_layout;
Box *sidebar_albumart;
Box *spectrum_view_layout;

Grid *sidebar_audioinfo_layout;
Scale *playback_slider;

Button *previous_button;
Button *play_button;
Button *next_button;
Button *sidebar_hider;

bool audio_file_chosen = false;

void gui::initialize(int argc, char **argv)
{
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "anorak.fidel");
  gui::init_builder();
  gui::get_widgets();
  gui::init_connections();
  window->maximize();

  app->run(*window);
  //delete window;
  //std::cout << window << std::endl;
  //g_resources_unregister(fidel_resources);
  g_resource_unref(fidel_resources);
}

void gui::get_widgets()
{
  builder->get_widget("window", window);
  builder->get_widget("toolbar", toolbar);
  builder->get_widget("open_action", open_action);
  builder->get_widget("view_switcher", view_switcher);
  builder->get_widget("playlist_search_entry", playlist_search_entry);

  builder->get_widget("split_view_label", split_view_label);
  builder->get_widget("playlist_view_label", playlist_view_label);
  builder->get_widget("library_view_label", library_view_label);
  builder->get_widget("spectrum_view_label", spectrum_view_label);
  builder->get_widget("idle_status_label", idle_status_label);
  builder->get_widget("sidebar_name_label", sidebar_name_label);
  builder->get_widget("sidebar_artist_label", sidebar_artist_label);
  builder->get_widget("sidebar_album_label", sidebar_album_label);
  builder->get_widget("playback_timer", playback_timer);
  builder->get_widget("playback_endtime", playback_endtime);
  builder->get_widget("sidebar_song_name", sidebar_song_name);
  builder->get_widget("sidebar_song_artist", sidebar_song_artist);
  builder->get_widget("sidebar_song_album", sidebar_song_album);

  builder->get_widget("split_view_layout", split_view_layout);
  builder->get_widget("split_view_spectrum", split_view_spectrum);
  builder->get_widget("split_view_playlist", split_view_playlist);
  builder->get_widget("library_view_frame", library_view_frame);
  builder->get_widget("playback_frame", playback_frame);
  builder->get_widget("playlist_view", playlist_view);
  builder->get_widget("playback_slider_frame", playback_slider_frame);
  builder->get_widget("sidebar_layout", sidebar_layout);
  builder->get_widget("sidebar_albumart", sidebar_albumart);
  builder->get_widget("spectrum_view_layout", spectrum_view_layout);

  builder->get_widget("sidebar_audioinfo_layout", sidebar_audioinfo_layout);
  builder->get_widget("previous_button", previous_button);
  builder->get_widget("play_button", play_button);
  builder->get_widget("next_button", next_button);
  builder->get_widget("sidebar_hider", sidebar_hider);
}

void gui::init_connections()
{
  window->signal_delete_event().connect(sigc::mem_fun(this, &gui::on_window_closed));
  open_action->signal_activate().connect(sigc::mem_fun(this, &gui::on_file_open_triggered));
  audio_playback::Instance()->signal_spectrum_changed().connect(sigc::mem_fun(this, &gui::testhandler));
}

void gui::testhandler(guint band, gfloat magnitude, gfloat phase_shift)
{
  std::cout << "Band -> " << band << " Magn dB -> " << magnitude << " phase -> " << phase_shift << std::endl;
}

bool gui::on_window_closed(GdkEventAny* event)
{
  return false;
}

void gui::on_file_open_triggered()
{
  Gtk::FileChooserDialog fileOpenDialog("Please choose a file",
  Gtk::FILE_CHOOSER_ACTION_OPEN);
  fileOpenDialog.set_transient_for(*window);
  fileOpenDialog.set_position(Gtk::WIN_POS_CENTER);
  fileOpenDialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
  fileOpenDialog.add_button("_Open", Gtk::RESPONSE_OK);

  FileFilter audio_file_filter = Gtk::FileFilter::create();
  audio_file_filter->set_name("Audio Files");
  audio_file_filter->add_pattern("*.flac");
  audio_file_filter->add_pattern("*.mp3");
  audio_file_filter->add_pattern("*.wav");
  audio_file_filter->add_pattern("*.ogg");
  audio_file_filter->add_pattern("*.m4a");
  audio_file_filter->add_pattern("*.m4p");
  fileOpenDialog.add_filter(audio_file_filter);

  int result = fileOpenDialog.run();

  switch(result)
  {
    case(Gtk::RESPONSE_OK):
    {
      std::cout << "Open clicked." << std::endl;
      std::string filesrc = fileOpenDialog.get_filename();
      std::cout << "filesrc: " << filesrc << std::endl;
      char *audio_file_src = util::to_char(filesrc);

      if (audio_file_chosen == false)
      {
        audio_file_chosen = true;
        fileOpenDialog.~FileChooserDialog();
        audio_playback::Instance()->audio_file(audio_file_src);
      }
      else{
        audio_playback::Instance()->kill_curr_stream();
        audio_file_chosen = true;
        fileOpenDialog.~FileChooserDialog();
        audio_playback::Instance()->audio_file(audio_file_src);
      }
      delete audio_file_src;
      break;
    }
    case(Gtk::RESPONSE_CANCEL):
    {
      std::cout << "Cancel clicked." << std::endl;
      break;
    }
    default:
    {
      std::cout << "Unexpected button clicked." << std::endl;
      break;
    }
  }
}

void gui::init_builder()
{
  builder = Gtk::Builder::create();
  fidel_resources = Resource::fidel_get_resource();
  g_resources_register(fidel_resources);
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
