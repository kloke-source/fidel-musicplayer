#include "gui.h"
#include <vector>
#include <gtkmm.h>
#include <iostream>
#include <gio/gio.h>
extern "C" {
#include <GUI/fidel-resources.h>
}
#include <GUI/seeker.h>
#include <GUI/themer.h>
#include <GUI/playlist.h>
#include <GUI/fidel-popover.h>
#include <Utilities/util.h>
//#include <Utilities/btree.h>
#include <Audio/playback.h>
#include <Spectrum/spectrum.h>
//#include <Audio-Info/audioinfo.h>
//#include <GUI/album-art-viewer.h>
#include <Audio-Library/audio-library.h>

gui::gui(){}
gui::~gui(){}

Builder builder;
ApplicationWindow *window;

Toolbar *toolbar;
ImageMenuItem *open_action;
Notebook *view_switcher;

Image *previous_icon, *play_icon, *pause_icon, *next_icon;

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

//Gtk::SearchBar *fidel_search_bar;
Gtk::SearchEntry *fidel_search_entry;

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
Glib::RefPtr<Gtk::Adjustment> playback_slider_adjustment;
bool pb_slider_usr_moved = false;

Button *previous_button;
Button *play_button;
Button *next_button;
Button *sidebar_hider;

std::vector<Button*> all_buttons;

bool audio_file_chosen = false;

void gui::initialize(int argc, char **argv)
{
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "anorak.fidel");
  gui::init_builder();
  gui::get_widgets();
  gui::init_connections();
  gui::init_icons();
  gui::init_playback_functions();
  gui::init_playlist();
  gui::init_spectrum();
  gui::set_styles();
  window->set_size_request(800, 450);
  
  FidelPopover fidel_popover;
  fidel_popover.set_relative_to(*fidel_search_entry);
  fidel_popover.add_title("Hello");
  fidel_popover.add_title("Hello again");
  fidel_popover.add_separator();

  Gtk::Image *image = new Gtk::Image();
  Gtk::Image *image_copy = new Gtk::Image();
  
  image->set("/home/tashrif/Downloads/album-art-test.jpg");
  image_copy->set("/home/tashrif/Downloads/album-art-test.jpg");
  fidel_popover.add_entry(image, "Hello image");
  fidel_popover.add_entry(image_copy, "Hello image", "Supp text");
  fidel_popover.pop_item();
  fidel_popover.show_all();

  window->maximize();
  app->run(*window);
}

void gui::get_widgets()
{
  builder->get_widget("window", window);
  builder->get_widget("toolbar", toolbar);
  builder->get_widget("open_action", open_action);
  builder->get_widget("view_switcher", view_switcher);

  // builder->get_widget("fidel_search_bar", fidel_search_bar);
  builder->get_widget("fidel_search_entry", fidel_search_entry);
  
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
  window->signal_key_press_event().connect(sigc::mem_fun(this, &gui::keyboard_shortcuts));
  open_action->signal_activate().connect(sigc::mem_fun(this, &gui::on_file_open_triggered));
  audio_playback::Instance()->signal_update_pb_timer().connect(sigc::mem_fun(this, &gui::update_pb_timer));
}

bool gui::keyboard_shortcuts(GdkEventKey* event)
{
  if((event->keyval == GDK_KEY_o) &&
     (event->state & (GDK_CONTROL_MASK)))
    {
      gui::on_file_open_triggered();
    }
  if((event->keyval == GDK_KEY_s) &&
     (event->state & (GDK_CONTROL_MASK)))
    {
      seeker::show(window);
    }
  if((event->keyval == GDK_KEY_p) &&
     (event->state & (GDK_CONTROL_MASK)))
    {

      AudioLibrary::scan();
    }
  return true;
}

void gui::init_spectrum()
{
  audio_playback::Instance()->signal_spectrum_start().connect(sigc::mem_fun(*spectrum_visualizer::Instance(), &spectrum::start_visualization));
  spectrum_view_layout->pack_start(*spectrum_visualizer::Instance(), Gtk::PACK_EXPAND_WIDGET);
  spectrum_visualizer::Instance()->set_double_buffered(true);
  window->show_all();
}

void gui::init_icons()
{
  previous_icon = new Image();
  play_icon = new Image();
  pause_icon = new Image();
  next_icon = new Image();

  previous_icon->set_from_resource("/fidel/Resources/icons/playback-previous.svg");
  play_icon->set_from_resource("/fidel/Resources/icons/playback-play.svg");
  next_icon->set_from_resource("/fidel/Resources/icons/playback-next.svg");

  previous_button->add(*previous_icon);
  play_button->add(*play_icon);
  next_button->add(*next_icon);

  previous_icon->show();
  play_icon->show();
  next_icon->show();
}

void gui::init_playback_functions()
{
  idle_status_label->set_text("Idle");
  playback_slider_adjustment = Gtk::Adjustment::create(0.0, 0.0, 1, 0.1, 1.0, 1.0);
  //Note: This adjustment is used when the player is in idle. It doesn't really matter as a new one is created depending on the length of the audio track
  playback_slider = new Gtk::Scale(playback_slider_adjustment, Gtk::ORIENTATION_HORIZONTAL);
  playback_slider->set_draw_value(false);
  playback_slider_frame->pack_start(*playback_slider, Gtk::PACK_SHRINK);
  playback_slider->show();
}

void gui::init_playlist()
{
  AudioLibrary::populate_playlist();
  gui_playlist::Instance()->link_to_search_entry(fidel_search_entry);
  playlist_view->pack_start(*gui_playlist::Instance(), Gtk::PACK_EXPAND_WIDGET);
  window->show_all();
}

void gui::pb_slider_val_changed()
{
  if (pb_slider_usr_moved == true)
    {
      audio_playback::Instance()->seek(playback_slider->get_value(), "fidel_ui");
    }
}

void gui::update_pb_timer(double time)
{
  //Also updates playback timer label
  pb_slider_usr_moved = false;
  playback_slider->set_value(time);
  playback_timer->set_text(util::time_format(time));
  pb_slider_usr_moved = true;
}

void gui::set_pb_endtime(int endtime)
{
  delete playback_slider;
  idle_status_label->set_text("");
  playback_endtime->set_text(util::time_format(endtime));
  playback_slider_adjustment = Gtk::Adjustment::create(0.0, 0.0, (endtime + 1), 0.1, 1.0, 1.0);
  //parameters for Gtk::Adjustment::create inorder
  // Value, lower, upper, step_increment, page_increment, page_size:
  // Note that the page_size value only makes a difference for
  // scrollbar widgets, and the highest value you'll get is actually
  // (upper - page_size).
  playback_slider = new Gtk::Scale(playback_slider_adjustment, Gtk::ORIENTATION_HORIZONTAL);
  playback_slider->signal_value_changed().connect(sigc::mem_fun(this, &gui::pb_slider_val_changed));
  playback_slider->set_draw_value(false);
  playback_slider_frame->pack_start(*playback_slider, Gtk::PACK_EXPAND_WIDGET);
  themer::set_styles();
  playback_slider->show();
}

void gui::set_styles()
{
  themer::set_styles();
}

bool gui::on_window_closed(GdkEventAny* event)
{
  audio_playback::Instance()->kill_audio();
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

extern G_GNUC_INTERNAL GResource *fidel_get_resource(void);

void gui::init_builder()
{
  builder = Gtk::Builder::create();
  fidel_resources = Glib::wrap(fidel_get_resource(), false);
  fidel_resources->register_global();
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
