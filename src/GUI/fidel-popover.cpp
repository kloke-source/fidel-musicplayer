#include <GUI/fidel-popover.h>
#include <Utilities/util.h>
#include <Utilities/btree.h>
#include <Audio-Info/audioinfo.h>
#include <Audio-Library/audio-library.h>
#include <vector>
#include <iostream>

FidelPopover::FidelPopover()
{
  this->popover_frame = new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5);
  this->set_size_request(300, 0);
  this->add(*popover_frame);

  default_title_font.set_family("Open Sans Light");
  default_title_font.set_size(12.5 * PANGO_SCALE);
  
  default_prim_popover_font.set_family("Open Sans Light");
  default_prim_popover_font.set_size(11 * PANGO_SCALE);

  default_supp_popover_font.set_family("Open Sans Light");
  default_supp_popover_font.set_size(10.5 * PANGO_SCALE);
}

FidelPopover::~FidelPopover()
{
  std::cout << "Fidel popover destructor called" << std::endl;
  std::cout << "Destructor popping" << std::endl;
  FidelPopover::clear();

  while (widgets_in_popover.size())
    widgets_in_popover[widgets_in_popover.size()];
  while (images_in_popover.size())
    images_in_popover[images_in_popover.size()];
}

void FidelPopover::show_all()
{
  Gtk::Popover::show_all();
  for (size_t iter = 0; iter < fidel_option_icons_vect.size(); iter++) {
    fidel_option_icons_vect[iter]->hide();
  }
}

void FidelPopover::clear()
{
  while (toplevel_popover_entries.size())
    FidelPopover::pop_item();
}

void FidelPopover::add_title(std::string title)
{
  Gtk::Box *frame = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL);
  Gtk::Label *label = new Gtk::Label();
  
  label->set_markup("<b>" + title + "</b>");
  label->set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_CENTER);
  label->set_margin_left(7);
  label->override_font(default_title_font);
  
  frame->pack_start(*label, Gtk::PACK_EXPAND_WIDGET);
  popover_frame->pack_start(*frame, Gtk::PACK_SHRINK);

  toplevel_popover_entries.push_back(frame);
  widgets_in_popover.push_back(label);
  FidelPopover::add_separator();
}

void FidelPopover::add_entry(Gtk::Button *button_entry)
{
  popover_frame->pack_start(*button_entry, Gtk::PACK_EXPAND_WIDGET);
  toplevel_popover_entries.push_back(button_entry);
}

void FidelPopover::add_entry(Gtk::Image *image, std::string label_text)
{
  Gtk::Box *frame = new Gtk::Box();
  Gtk::Button *button_entry = new Gtk::Button();
  button_entry->set_relief(Gtk::RELIEF_NONE);
  Gtk::Box *content_frame = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5);
  Gtk::Label *label = new Gtk::Label();
  label->set_markup("<b>" + label_text + "</b>");
  label->set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_CENTER);
  label->override_font(default_prim_popover_font);  

  bool image_exists = false;
  for (size_t iter = 0; iter < images_in_popover.size(); iter++) {
    if (image == images_in_popover[iter]) {
      image_exists = true;
      break;
    }
  }

  if (image_exists == false) {
    util::resize_image(*image, default_image_size, default_image_size);
    image->set_margin_left(15);
    content_frame->pack_start(*image, Gtk::PACK_SHRINK);
    content_frame->pack_end(*label, Gtk::PACK_EXPAND_WIDGET);
    button_entry->add(*content_frame);
    frame->pack_start(*button_entry, Gtk::PACK_EXPAND_WIDGET);

    toplevel_popover_entries.push_back(frame);
    images_in_popover.push_back(image);
    widgets_in_popover.push_back(button_entry);
    widgets_in_popover.push_back(content_frame);
    widgets_in_popover.push_back(label);
    
    popover_frame->pack_start(*frame, Gtk::PACK_SHRINK);
  }
  if (image_exists == true) {
    std::cerr << "Error image pointer already in use\n";
  }
}

void FidelPopover::add_entry(std::pair<guint8*, gsize> image, std::string prim_label_text, std::string supp_label_text)
{
  Glib::RefPtr<Gdk::PixbufLoader> loader = Gdk::PixbufLoader::create();
  loader->write(image.first, image.second);
  loader->close();
  Glib::RefPtr<Gdk::Pixbuf> pixbuf = loader->get_pixbuf();
  Gtk::Image gtk_image;
  gtk_image.set(pixbuf);
  FidelPopover::add_entry(&gtk_image, prim_label_text, supp_label_text);
}

FidelOptions* FidelPopover::add_entry(Gtk::Image *image, std::string prim_label_text, std::string supp_label_text)
{
  Gtk::Box *frame = new Gtk::Box();
  FidelOptions *fidel_options = new FidelOptions();
  Gtk::Button *button_entry = new Gtk::Button();
  button_entry->set_relief(Gtk::RELIEF_NONE);  
  Gtk::Box *content_frame = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5);
  Gtk::Box *label_container = new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 4);

  Gtk::Label *prim_label = new Gtk::Label();
  Gtk::Label *supp_label = new Gtk::Label();
  
  prim_label->set_markup("<b>" + prim_label_text + "</b>");
  prim_label->set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_END);
  prim_label->override_font(default_prim_popover_font);
  
  supp_label->set_text(supp_label_text);
  supp_label->set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_START);
  supp_label->override_color(Gdk::RGBA("#616161"));
  supp_label->override_font(default_supp_popover_font);
  
  bool image_exists = false;
  for (size_t iter = 0; iter < images_in_popover.size(); iter++) {
    if (image == images_in_popover[iter]) {
      image_exists = true;
      break;
    }
  }

  if (image_exists == false) {
    util::resize_image(*image, default_image_size, default_image_size);
    image->set_margin_left(15);
    image->set_margin_right(5);

    Gtk::Image *fidel_options_icon = fidel_options->get_icon();
    fidel_options->set_relative_to(*button_entry);
    button_entry->signal_clicked().connect([fidel_options](){fidel_options->show_popover();});    
    button_entry->signal_enter().connect([fidel_options_icon](){fidel_options_icon->show();});
    button_entry->signal_leave().connect([fidel_options_icon](){fidel_options_icon->hide();});
    
    content_frame->pack_start(*fidel_options_icon, Gtk::PACK_SHRINK);
    content_frame->pack_start(*image, Gtk::PACK_SHRINK);
	
    label_container->pack_start(*prim_label, Gtk::PACK_EXPAND_WIDGET);
    label_container->pack_end(*supp_label, Gtk::PACK_EXPAND_WIDGET);

    content_frame->pack_end(*label_container, Gtk::PACK_EXPAND_WIDGET);

    button_entry->add(*content_frame);
    frame->pack_start(*button_entry, Gtk::PACK_EXPAND_WIDGET);

    toplevel_popover_entries.push_back(frame);
    images_in_popover.push_back(image);
    widgets_in_popover.push_back(button_entry);
    widgets_in_popover.push_back(content_frame);
    widgets_in_popover.push_back(fidel_options);    
    fidel_option_icons_vect.push_back(fidel_options_icon);    
    widgets_in_popover.push_back(label_container);
    widgets_in_popover.push_back(prim_label);
    widgets_in_popover.push_back(supp_label);
      
    popover_frame->pack_start(*frame, Gtk::PACK_SHRINK);
  }
  if (image_exists == true) {
    std::cerr << "Error image pointer already in use\n";
  }
  return fidel_options;
}

void FidelPopover::add_separator()
{
  Gtk::Separator *separator = new Gtk::Separator(Gtk::ORIENTATION_HORIZONTAL);
  Gtk::Box *separator_container = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL);
  separator_container->pack_start(*separator, Gtk::PACK_EXPAND_WIDGET);
  toplevel_popover_entries.push_back(separator_container);
  widgets_in_popover.push_back(separator);
  popover_frame->pack_start(*separator_container, Gtk::PACK_SHRINK);
}

void FidelPopover::populate(std::vector<std::vector<std::string>> populate_data)
{
  FidelPopover::clear();
  
  if (populate_data.size() && populate_data.size() == 5) {
    FidelPopover::add_title("Songs");    
    // Add songs to popover

    //    std::string current_album;
    std::vector<std::vector<std::string>> full_row_data;
    Playlist *queue_playlist = fidel_ui::Instance()->get_playlist_queue();
      
    for (size_t iter = 0; iter < populate_data[Playlist::FILE_LOC].size(); iter++) {    
      std::vector<std::string> row_data;
      row_data.push_back(Glib::Markup::escape_text(populate_data[Playlist::SONG_NAME][iter]));
      row_data.push_back(populate_data[Playlist::ARTIST][iter]);
      row_data.push_back(populate_data[Playlist::ALBUM][iter]);
      row_data.push_back(populate_data[Playlist::TIME][iter]);
      row_data.push_back(populate_data[Playlist::FILE_LOC][iter]);      
      full_row_data.push_back(row_data);
    }

    
    for (size_t iter = 0; iter < populate_data[Playlist::FILE_LOC].size(); iter++) {
      std::string song_name = Glib::Markup::escape_text(populate_data[Playlist::SONG_NAME][iter]);
      std::string artist = populate_data[Playlist::ARTIST][iter];
      std::string album = populate_data[Playlist::ALBUM][iter];
      std::string time = populate_data[Playlist::TIME][iter];
      std::string file_loc = populate_data[Playlist::FILE_LOC][iter];
      std::string supp_label = artist + " \u2015 " + album; // \u2015 is the unicode character for horizontal bar

      std::cout << "Popover file_loc " << file_loc << std::endl;
      Gtk::Image *album_art = audioinfo::get_album_art(file_loc);
      FidelOptions *fidel_options = FidelPopover::add_entry(album_art, song_name, supp_label);      
      fidel_options->set_play_next_cb([queue_playlist, full_row_data, iter, fidel_options](){
	  queue_playlist->append_after_current(full_row_data[iter]);
	  fidel_options->hide_popover();	
	});
      fidel_options->set_add_to_bottom_of_queue_cb([queue_playlist, full_row_data, iter, fidel_options](){
	  queue_playlist->append_row(full_row_data[iter]);
	  fidel_options->hide_popover();	
	});
      if (iter == 3)
	break;      
    }


    if (populate_data[Playlist::SONG_NAME].size() > 1)
      {
	// Add artists and albums to popover
	FidelPopover::add_title("Artists");


	btree<std::string> added_artists;
	std::vector<std::string> grouped_artists;
	std::vector<Gtk::Image*> grouped_raw_album_art;
	std::vector<int> num_songs_artist;
    
	for (size_t iter = 0; iter < populate_data[Playlist::ARTIST].size(); iter++) {
	  std::string artist = Glib::Markup::escape_text(populate_data[Playlist::ARTIST][iter]);
	  std::string file_loc = populate_data[Playlist::FILE_LOC][iter];
	  std::string album = populate_data[Playlist::ALBUM][iter];

	  grouped_raw_album_art.push_back(audioinfo::get_album_art(file_loc));
	
	  if (added_artists.search(artist) != artist) {
	    added_artists.insert(artist);
	    num_songs_artist.push_back(1);
	  }
	  else {
	    int artist_pos = added_artists.get_search_id();
	    num_songs_artist[artist_pos]++;
	  }
	}

	grouped_artists = added_artists.inorder();
	for (size_t iter = 0; iter < grouped_artists.size(); iter++) {
	  Gtk::Image *album_art = grouped_raw_album_art[iter];
	  
	  FidelOptions *fidel_options = FidelPopover::add_entry(album_art, grouped_artists[iter], util::to_string(num_songs_artist[iter]));
	  fidel_options->set_play_next_cb([queue_playlist, full_row_data, fidel_options](){
	      for (size_t iter = 0; iter < full_row_data.size(); iter++) {
		queue_playlist->append_after_current(full_row_data[iter]);
	      }
	      fidel_options->hide_popover();	
	    });
	  fidel_options->set_add_to_bottom_of_queue_cb([queue_playlist, full_row_data, fidel_options](){
	      for (size_t iter = 0; iter < full_row_data.size(); iter++) {
		queue_playlist->append_row(full_row_data[iter]);	    
	      }
	      fidel_options->hide_popover();	
	    });	    
	  
	  if (iter == 3)
	    break;
	}
    
	// Add albums to popover
	FidelPopover::add_title("Albums");
	btree<std::string> added_albums;
    
	for (size_t iter = 0; iter < populate_data[Playlist::ALBUM].size(); iter++) {
	  std::string album = Glib::Markup::escape_text(populate_data[Playlist::ALBUM][iter]);
	  std::string supp_label = populate_data[Playlist::ARTIST][iter];
	  std::string file_loc = populate_data[Playlist::FILE_LOC][iter];
      
	  if (added_albums.check(album) == false) {
	    added_albums.insert(album);
	    
	    Gtk::Image *album_art = audioinfo::get_album_art(file_loc);
	    
	    FidelOptions *fidel_options = FidelPopover::add_entry(album_art, album, supp_label);
	    fidel_options->set_play_next_cb([queue_playlist, full_row_data, fidel_options](){
		for (size_t iter = 0; iter < full_row_data.size(); iter++) {
		  queue_playlist->append_after_current(full_row_data[iter]);
		}
		fidel_options->hide_popover();	
	      });
	    fidel_options->set_add_to_bottom_of_queue_cb([queue_playlist, full_row_data, fidel_options](){
		for (size_t iter = 0; iter < full_row_data.size(); iter++) {
		  queue_playlist->append_row(full_row_data[iter]);	    
		}
		fidel_options->hide_popover();	
	      });	    
	  }
	  if (iter == 3)
	    break;
	}
      }
  }
}

void FidelPopover::pop_item()
{
  size_t pop_position = toplevel_popover_entries.size() - 1;
  popover_frame->remove(*toplevel_popover_entries[pop_position]);
  delete toplevel_popover_entries[pop_position];
  toplevel_popover_entries.erase(toplevel_popover_entries.begin() + pop_position);
}
