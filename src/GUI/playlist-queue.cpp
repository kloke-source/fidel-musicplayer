#include <GUI/playlist-queue.h>
#include <thread>
#include <chrono>

PlaylistQueue::PlaylistQueue()
{
  PlaylistQueue::initialize();
}

PlaylistQueue::PlaylistQueue(Gtk::Button *queue_overview_button)
{
  PlaylistQueue::initialize();
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

void PlaylistQueue::overview_notify_reset()
{
  this->queue_overview_button->remove();
  this->queue_overview_button->add(*queue_overview_icon);
  this->queue_overview_button->show_all();
  this->queue_overview_popover->set_relative_to(*this->queue_overview_button);      
}

void PlaylistQueue::initialize()
{
  queue_overview_popover = new FidelPopover();
  queue_overview_notify_icon = new Gtk::Image();
  queue_overview_icon = new Gtk::Image();
  overview_show_more_less_button = new Gtk::Button("Show more");
  overview_show_more_less_button->set_relief(Gtk::RELIEF_NONE);
  queue_overview_icon->set_from_resource("/fidel/Resources/icons/queue-overview.svg");
  queue_overview_notify_icon->set_from_resource("/fidel/Resources/icons/queue-overview-notify.svg");  
}

void PlaylistQueue::init_connections()
{
  this->queue_overview_button->signal_clicked().connect(sigc::mem_fun(this, &PlaylistQueue::on_overview_button_clicked));
  this->queue_overview_button->signal_activate().connect([](){std::cout << "Overview button double clicked" << std::endl;});
  this->overview_show_more_less_button->signal_clicked().connect(sigc::mem_fun(this, &PlaylistQueue::on_overview_show_more_less_clicked));  
}

std::vector<std::string> PlaylistQueue::get_up_next()
{
  std::vector<std::string> up_next_data;

  if (this->total_songs > 0)
    {
      int up_next_iter = this->curr_song_iterator + 1;
      if (curr_song_iterator == (total_songs - 1))
	up_next_iter = 0;
  
      Gtk::TreeModel::Children rows = this->playlist_model->children();
      Gtk::TreeModel::Children::iterator up_next_iterator = rows[up_next_iter];
      Gtk::TreeModel::Row up_next_row = *up_next_iterator;

      up_next_data.push_back(up_next_row[playlist_columns.col_name]);
      up_next_data.push_back(up_next_row[playlist_columns.col_artist]);
      up_next_data.push_back(up_next_row[playlist_columns.col_album]);
      up_next_data.push_back(up_next_row[playlist_columns.col_time]);
      up_next_data.push_back(up_next_row[playlist_columns.col_file_location]);

    }
  return up_next_data;
}

std::vector<std::vector<std::string>> PlaylistQueue::get_all_up_next()
{
  std::vector<std::vector<std::string>> full_up_next_data;
  Gtk::TreeModel::Children rows = this->playlist_model->children();
  size_t up_next_iter = this->curr_song_iterator + 1;
  if (curr_song_iterator == (total_songs - 1))
    up_next_iter = 0;
     
  for (size_t iter = up_next_iter; iter < this->total_songs; iter++) {
    std::vector<std::string> up_next_data;
    Gtk::TreeModel::Children::iterator up_next_iterator = rows[iter];
    Gtk::TreeModel::Row up_next_row = *up_next_iterator;

    up_next_data.push_back(up_next_row[playlist_columns.col_name]);
    up_next_data.push_back(up_next_row[playlist_columns.col_artist]);
    up_next_data.push_back(up_next_row[playlist_columns.col_album]);
    up_next_data.push_back(up_next_row[playlist_columns.col_time]);
    up_next_data.push_back(up_next_row[playlist_columns.col_file_location]);

    full_up_next_data.push_back(up_next_data);
  }
  return full_up_next_data;
}

void PlaylistQueue::overview_show()
{
  PlaylistQueue::overview_notify_reset();
  if (overview_show_prev_state == false)
    {
      if (this->show_more_less_clicked_once == true) {
	if (this->overview_show_more_less_button->get_label() == "Show more")
	  PlaylistQueue::show_all_songs();
	else
	  PlaylistQueue::show_first_song();
      }
      if (this->show_more_less_clicked_once == false) {
	if (this->overview_show_more_less_button->get_label() == "Show more")
	  PlaylistQueue::show_first_song();
	else
	  PlaylistQueue::show_all_songs();
      }
    }
  else {
    if (prev_overview_state == FULL_OVERVIEW_SHOWN)
      PlaylistQueue::show_all_songs();
    else 
      PlaylistQueue::show_first_song();      
  }
}

void PlaylistQueue::show_first_song()
{
  this->queue_overview_popover->clear();
  std::vector<std::string> up_next_song_data = PlaylistQueue::get_up_next();
  if (up_next_song_data.size() >= 1)
    {
      this->queue_overview_popover->add_text_with_widget("Next Song", overview_show_more_less_button);

      std::string song_name = up_next_song_data[Playlist::SONG_NAME];
      std::string artist = up_next_song_data[Playlist::ARTIST];  
      std::string album = up_next_song_data[Playlist::ALBUM];
      std::string file_loc = up_next_song_data[Playlist::FILE_LOC];
      std::string supp_label = artist + " \u2015 " + album; // \u2015 is the unicode character for horizontal bar

      Gtk::Image *album_art = audioinfo::get_album_art_by_name(album, file_loc);
      FidelOptions *fidel_options = new FidelOptions();
    this->queue_overview_popover->add_segmented_entry(fidel_options, album_art, default_image_size, song_name, supp_label);
      
      fidel_options->set_play_next_cb([this, up_next_song_data, fidel_options](){
	  this->append_after_current(up_next_song_data);
	  fidel_options->hide_popover();
	  this->hide();
	});
      fidel_options->set_add_to_bottom_of_queue_cb([this, up_next_song_data, fidel_options](){
	  this->append_row(up_next_song_data);
	  fidel_options->hide_popover();
	  this->hide();
	});
    }
  else
    this->queue_overview_popover->add_text("No upcoming songs");
  PlaylistQueue::overview_notify_reset();
  this->queue_overview_popover->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_NEVER);
  this->queue_overview_popover->set_size_request(200, 0);
  this->queue_overview_popover->show_all();
  this->prev_overview_state = FIRST_SONG_SHOWN;  
}

void PlaylistQueue::show_all_songs()
{
  this->queue_overview_popover->clear();
  std::vector<std::vector<std::string>> all_up_next_songs;
  all_up_next_songs = PlaylistQueue::get_all_up_next();

  std::stringstream up_next_title;
  up_next_title << "<b>Up Next: </b>" << all_up_next_songs.size() << " songs";
  this->queue_overview_popover->add_text_with_widget(up_next_title.str(), overview_show_more_less_button);
  this->queue_overview_popover->add_separator();

  for (size_t iter = 0; iter < all_up_next_songs.size(); iter++) {
    std::string song_name = all_up_next_songs[iter][Playlist::SONG_NAME];
    std::string artist = all_up_next_songs[iter][Playlist::ARTIST];  
    std::string album = all_up_next_songs[iter][Playlist::ALBUM];
    std::string file_loc = all_up_next_songs[iter][Playlist::FILE_LOC];
    std::string supp_label = artist + " \u2015 " + album; // \u2015 is the unicode character for horizontal bar

    Gtk::Image *album_art = audioinfo::get_album_art_by_name(album, file_loc);
    FidelOptions* fidel_options = new FidelOptions();

    this->queue_overview_popover->add_segmented_entry(fidel_options, album_art, default_image_size, song_name, supp_label);

    fidel_options->set_play_next_cb([this, all_up_next_songs, iter, fidel_options](){
	this->append_after_current(all_up_next_songs[iter]);
	fidel_options->hide_popover();
	this->queue_overview_popover->hide();
      });

    fidel_options->set_add_to_bottom_of_queue_cb([this, all_up_next_songs, iter, fidel_options](){
	this->append_row(all_up_next_songs[iter]);
	fidel_options->hide_popover();
	this->queue_overview_popover->hide();	    
      });
  }
  this->queue_overview_popover->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
  this->queue_overview_popover->set_size_request(350, 500);
  this->queue_overview_popover->show_all();
  this->prev_overview_state = FULL_OVERVIEW_SHOWN;  
}

// signal handlers
void PlaylistQueue::on_overview_button_enter()
{
  //  PlaylistQueue::show_first_song();
}

void PlaylistQueue::on_overview_button_clicked()
{
  if (this->show_more_less_clicked_once == true)
    this->overview_show_prev_state = true;
  PlaylistQueue::overview_show();
}

void PlaylistQueue::on_overview_show_more_less_clicked()
{
  this->overview_show_prev_state = false;      
  if (show_more_less_click_inconsistency == false) {
    if (this->show_more_less_clicked_once == false) {
      this->show_more_less_clicked_once = true;
      PlaylistQueue::overview_show();
      this->overview_show_more_less_button->set_label("Show less");
    }
    else if (this->overview_show_more_less_button->get_label() == "Show more") {
      PlaylistQueue::overview_show();
      this->overview_show_more_less_button->set_label("Show less");	  
    }
    else {
      PlaylistQueue::overview_show();
      this->overview_show_more_less_button->set_label("Show more");   		  
    }
  }
  if (show_more_less_click_inconsistency != true)
    show_more_less_click_inconsistency = true;
  else
    show_more_less_click_inconsistency = false;
}  
/*  
    std::string song_name = all_up_next_songs[Playlist::SONG_NAME];  
    std::string file_loc = all_up_next_songs[Playlist::FILE_LOC];
    std::string time = all_up_next_songs[Playlist::TIME];

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
    fidel_options->set_play_next_cb([this, all_up_next_songs](){this->append_after_current(all_up_next_songs);});
    fidel_options->set_add_to_bottom_of_queue_cb([this, all_up_next_songs](){this->append_row(all_up_next_songs);});

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
