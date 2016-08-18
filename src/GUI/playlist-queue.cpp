#include <GUI/playlist-queue.h>
#include <thread>
#include <chrono>

PlaylistQueue::PlaylistQueue()
{
  queue_overview_popover = new FidelPopover();
  queue_overview_notify_icon = new Gtk::Image();
  queue_overview_icon = new Gtk::Image();  
  queue_overview_notify_icon->set_from_resource("/fidel/Resources/icons/queue-overview-notify.svg");
  queue_overview_icon->set_from_resource("/fidel/Resources/icons/queue-overview.svg");  
}

PlaylistQueue::PlaylistQueue(Gtk::Button *queue_overview_button)
{
  queue_overview_popover = new FidelPopover();
  queue_overview_notify_icon = new Gtk::Image();
  queue_overview_icon = new Gtk::Image();  
  queue_overview_notify_icon->set_from_resource("/fidel/Resources/icons/queue-overview-notify.svg");
  queue_overview_icon->set_from_resource("/fidel/Resources/icons/queue-overview.svg");
  PlaylistQueue::set_overview_button(queue_overview_button);
  queue_overview_popover->set_relative_to(*this->queue_overview_button);
  PlaylistQueue::init_connections();
}

PlaylistQueue::~PlaylistQueue(){}

void PlaylistQueue::set_overview_button(Gtk::Button *queue_overview_button)
{
  this->queue_overview_button = queue_overview_button;
  PlaylistQueue::init_connections();
}

void PlaylistQueue::overview_notify()
{
  this->queue_overview_button->remove();
  this->queue_overview_button->add(*queue_overview_notify_icon);
  this->queue_overview_popover->set_relative_to(*this->queue_overview_button);
  this->queue_overview_button->show_all();
}

void PlaylistQueue::overview_reset()
{
  this->queue_overview_button->remove();
  this->queue_overview_button->add(*queue_overview_icon);
  this->queue_overview_button->show_all();
  this->queue_overview_popover->set_relative_to(*this->queue_overview_button);      
}

void PlaylistQueue::init_connections()
{
  this->queue_overview_button->signal_clicked().connect(sigc::mem_fun(this, &PlaylistQueue::on_overview_button_clicked));  
  this->queue_overview_button->signal_enter().connect(sigc::mem_fun(this, &PlaylistQueue::on_overview_button_enter));
}

void PlaylistQueue::show_first_song()
{
  this->queue_overview_popover->clear();
  std::vector<std::vector<std::string>> all_songs_in_queue = this->get_full_row_data();
  if (all_songs_in_queue.size() >= 1)
    {
      std::vector<std::string> first_song_in_queue = all_songs_in_queue[0];      
      this->queue_overview_popover->add_title("Next Song");

      std::string song_name = first_song_in_queue[Playlist::SONG_NAME];
      std::string artist = first_song_in_queue[Playlist::ARTIST];  
      std::string album = first_song_in_queue[Playlist::ALBUM];
      std::string file_loc = first_song_in_queue[Playlist::FILE_LOC];
      std::string supp_label = artist + " \u2015 " + album; // \u2015 is the unicode character for horizontal bar

      Gtk::Image *album_art = audioinfo::get_album_art(file_loc);
      FidelOptions *fidel_options = this->queue_overview_popover->add_entry(album_art, song_name, supp_label);
	
      fidel_options->set_play_next_cb([this, first_song_in_queue, fidel_options](){
	  this->append_after_current(first_song_in_queue);
	  fidel_options->hide_popover();
	  this->hide();
	});
      fidel_options->set_add_to_bottom_of_queue_cb([this, first_song_in_queue, fidel_options](){
	  this->append_row(first_song_in_queue);
	  fidel_options->hide_popover();
	  this->hide();
	});
    }
  else
    this->queue_overview_popover->add_text("No upcoming songs");
  PlaylistQueue::overview_reset();
  this->queue_overview_popover->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_NEVER);
  this->queue_overview_popover->set_size_request(200, 0);  
  this->queue_overview_popover->show_all();
}

// signal handlers
void PlaylistQueue::on_overview_button_enter()
{
  PlaylistQueue::show_first_song();
}

void PlaylistQueue::on_overview_button_clicked()
{
  PlaylistQueue::overview_reset();  
  if (this->popover_hidden == true)
    {
      this->popover_hidden = false;
      this->queue_overview_popover->clear();
  
      std::vector<std::vector<std::string>> all_songs_in_queue;
      all_songs_in_queue = this->get_full_row_data();

      std::stringstream up_next_title;
      up_next_title << "<b>Up Next: </b>" << all_songs_in_queue.size() << " songs";
      this->queue_overview_popover->add_text(up_next_title.str());
      this->queue_overview_popover->add_separator();

      for (size_t iter = 0; iter < all_songs_in_queue.size(); iter++) {
	std::string song_name = all_songs_in_queue[iter][Playlist::SONG_NAME];
	std::string artist = all_songs_in_queue[iter][Playlist::ARTIST];  
	std::string album = all_songs_in_queue[iter][Playlist::ALBUM];
	std::string file_loc = all_songs_in_queue[iter][Playlist::FILE_LOC];
	std::string supp_label = artist + " \u2015 " + album; // \u2015 is the unicode character for horizontal bar

	Gtk::Image *album_art = audioinfo::get_album_art(file_loc);
	FidelOptions *fidel_options = this->queue_overview_popover->add_entry(album_art, default_image_size, song_name, supp_label);

	fidel_options->set_play_next_cb([this, all_songs_in_queue, iter, fidel_options](){
	    this->append_after_current(all_songs_in_queue[iter]);
	    fidel_options->hide_popover();
	    this->queue_overview_popover->hide();
	  });
	fidel_options->set_add_to_bottom_of_queue_cb([this, all_songs_in_queue, iter, fidel_options](){
	    this->append_row(all_songs_in_queue[iter]);
	    fidel_options->hide_popover();
	    this->queue_overview_popover->hide();	    
	  });
	
      }
      this->queue_overview_popover->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
      this->queue_overview_popover->set_size_request(350, 500);        
      this->queue_overview_popover->show_all();  
      /*  
	  std::string song_name = all_songs_in_queue[Playlist::SONG_NAME];  
	  std::string file_loc = all_songs_in_queue[Playlist::FILE_LOC];
	  std::string time = all_songs_in_queue[Playlist::TIME];

	  Gtk::Box *frame = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5);  
	  FidelOptions *fidel_options = new FidelOptions();
	  Gtk::Image *album_art = util::resize_image(audioinfo::get_album_art(file_loc), default_image_size, default_image_size);
	  Gtk::Image *fidel_options_icon = fidel_options->get_icon();
  
	  Gtk::Separator *album_art_separator = new Gtk::Separator(Gtk::ORIENTATION_VERTICAL);
	  Gtk::Separator *song_separator = new Gtk::Separator(Gtk::ORIENTATION_VERTICAL);
  
	  Gtk::Button *button_entry = new Gtk::Button();
	  Gtk::Label *song_label = new Gtk::Label(song_name);
	  Gtk::Label *time_label = new Gtk::Label(time);

	  frame->pack_start(*fidel_options_icon, Gtk::PACK_SHRINK);
	  frame->pack_start(*album_art, Gtk::PACK_SHRINK);
	  frame->pack_start(*album_art_separator, Gtk::PACK_SHRINK);
	  frame->pack_start(*song_label, Gtk::PACK_EXPAND_WIDGET);
	  frame->pack_start(*song_separator, Gtk::PACK_SHRINK);
	  frame->pack_start(*time_label, Gtk::PACK_SHRINK);

	  button_entry->add(*frame);
	  button_entry->set_relief(Gtk::RELIEF_NONE);
	  button_entry->signal_enter().connect([fidel_options_icon](){fidel_options_icon->show();});
	  button_entry->signal_leave().connect([fidel_options_icon](){fidel_options_icon->hide();});
	  button_entry->signal_clicked().connect([fidel_options](){fidel_options->show_popover();});

	  fidel_options->set_relative_to(*button_entry);
	  fidel_options->set_position(Gtk::POS_RIGHT);
	  fidel_options->set_play_next_cb([this, all_songs_in_queue](){this->append_after_current(all_songs_in_queue);});
	  fidel_options->set_add_to_bottom_of_queue_cb([this, all_songs_in_queue](){this->append_row(all_songs_in_queue);});

	  this->queue_entries.push_back(button_entry);
	  this->option_icons.push_back(fidel_options_icon);  
	  this->child_widgets.push_back(frame);
	  this->child_widgets.push_back(album_art);
	  this->child_widgets.push_back(album_art_separator);
	  this->child_widgets.push_back(song_separator);  
	  this->child_widgets.push_back(song_label);
	  this->child_widgets.push_back(time_label);
  
	  this->queue_overview_popover->add_entry(button_entrdefault_album_art_size, y);
      */
    }
  else {
    this->popover_hidden = true;
    this->queue_overview_popover->hide();
  }
}
