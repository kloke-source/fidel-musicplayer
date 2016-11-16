#include <vector>
#include <iostream>
#include <Utilities/util.h>
#include <Utilities/btree.h>
#include <GUI/fidel-popover.h>
#include <Audio-Info/audioinfo.h>
#include <Audio-Library/audio-library.h>
#include <chrono>

FidelPopover::FidelPopover()
{
  this->popover_frame = new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5);
  this->popover_scrolled_window = new Gtk::ScrolledWindow();
  this->popover_scrolled_window->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_NEVER);
  this->set_size_request(350, 500);
  this->popover_scrolled_window->add(*popover_frame);
  this->add(*popover_scrolled_window);

  default_title_font.set_family("Open Sans Light");
  default_title_font.set_size(12.5 * PANGO_SCALE);

  default_prim_popover_font.set_family("Open Sans Light");
  default_prim_popover_font.set_size(11 * PANGO_SCALE);

  default_supp_popover_font.set_family("Open Sans Light");
  default_supp_popover_font.set_size(10.5 * PANGO_SCALE);
}

FidelPopover::~FidelPopover()
{
  std::cout << "Fidel Popover Destructor" << std::endl;
  FidelPopover::clear();

  while (widgets_in_popover.size())
    delete widgets_in_popover[widgets_in_popover.size()];
  while (images_in_popover.size())
    delete images_in_popover[images_in_popover.size()];
  while (fidel_options_vect.size())
    delete fidel_options_vect[fidel_options_vect.size()];
  while (toplevel_popover_entries.size())
    delete toplevel_popover_entries[toplevel_popover_entries.size()];

  delete popover_frame;
  delete popover_scrolled_window;
  delete this;
}

void FidelPopover::show_all()
{
  Gtk::Popover::show_all();
  for (size_t iter = 0; iter < fidel_options_vect.size(); iter++) {
    fidel_options_vect[iter]->hide();
  }
}

void FidelPopover::clear()
{
  while (toplevel_popover_entries.size())
    FidelPopover::pop_item();
}

void FidelPopover::set_policy(Gtk::PolicyType hscrollbar_policy, Gtk::PolicyType vscrollbar_policy)
{
  this->popover_scrolled_window->set_policy(hscrollbar_policy, vscrollbar_policy);
}

void FidelPopover::add_text(std::string text)
{
  Gtk::Box *frame = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL);
  Gtk::Label *label = new Gtk::Label();

  //  text = Glib::Markup::escape_text(text);
  label->set_markup(text);
  label->set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_CENTER);
  label->set_margin_left(7);
  label->override_font(default_title_font);

  frame->pack_start(*label, Gtk::PACK_EXPAND_WIDGET);
  popover_frame->pack_start(*frame, Gtk::PACK_SHRINK);

  toplevel_popover_entries.push_back(frame);
  widgets_in_popover.push_back(label);
}

void FidelPopover::add_text_with_widget(std::string text, Gtk::Widget *widget)
{
  Gtk::Box *frame = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL);
  Gtk::Label *label = new Gtk::Label();

  label->set_markup(text);
  label->set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_CENTER);
  label->set_margin_left(7);
  label->override_font(default_title_font);

  frame->pack_start(*label, Gtk::PACK_EXPAND_WIDGET);
  frame->pack_start(*widget, Gtk::PACK_EXPAND_WIDGET);
  popover_frame->pack_start(*frame, Gtk::PACK_SHRINK);

  toplevel_popover_entries.push_back(frame);
  widgets_in_popover.push_back(label);
  widgets_in_popover.push_back(widget);
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

void FidelPopover::add_top_entry(Gtk::Button *button_entry)
{
  popover_frame->pack_end(*button_entry, Gtk::PACK_EXPAND_WIDGET);
  toplevel_popover_entries.push_back(button_entry);
}

void FidelPopover::add_entry(Gtk::Widget *widget)
{
  popover_frame->pack_start(*widget, Gtk::PACK_EXPAND_WIDGET);
  toplevel_popover_entries.push_back(widget);
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
    image = util::resize_image(image, default_image_size, default_image_size);
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

FidelOptions* FidelPopover::add_entry(Gtk::Image *image, std::string prim_label_text, std::string supp_label_text)
{
  return FidelPopover::add_entry(image, default_image_size, prim_label_text, supp_label_text);
}

FidelOptions* FidelPopover::add_entry(Gtk::Image *image, int image_size, std::string prim_label_text, std::string supp_label_text)
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
    image = util::resize_image(image, image_size, image_size);
    image->set_margin_left(15);
    image->set_margin_right(5);

    Gtk::Image *fidel_options_icon = fidel_options->get_icon();
    fidel_options->set_relative_to(*button_entry);
    fidel_options->set_position(Gtk::POS_RIGHT);
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
    fidel_options_vect.push_back(fidel_options_icon);
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

void FidelPopover::add_segmented_entry(FidelOptions *segmented_options, Gtk::Image *image, int image_size, std::string prim_label_text, std::string supp_label_text)
{
  Gtk::Box *frame = new Gtk::Box();
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

  /*
    bool image_exists = false;
    for (size_t iter = 0; iter < images_in_popover.size(); iter++) {
    if (image == images_in_popover[iter]) {
    image_exists = true;
    break;
    }
    }
  */
  //  if (image_exists == false) {
  image = util::resize_image(image, image_size, image_size);
  image->set_margin_left(15);
  image->set_margin_right(5);

  segmented_options->set_relative_to(*button_entry);
  segmented_options->set_position(Gtk::POS_RIGHT);

  button_entry->signal_enter().connect([segmented_options](){segmented_options->show();});
  segmented_options->signal_leave().connect([segmented_options](){segmented_options->hide();});
  segmented_options->signal_clicked().connect([segmented_options](){segmented_options->show_popover();});

  content_frame->pack_start(*image, Gtk::PACK_SHRINK);

  label_container->pack_start(*prim_label, Gtk::PACK_EXPAND_WIDGET);
  label_container->pack_end(*supp_label, Gtk::PACK_EXPAND_WIDGET);

  content_frame->pack_end(*label_container, Gtk::PACK_EXPAND_WIDGET);

  button_entry->add(*content_frame);

  frame->pack_start(*segmented_options, Gtk::PACK_SHRINK);
  frame->pack_start(*button_entry, Gtk::PACK_EXPAND_WIDGET);

  toplevel_popover_entries.push_back(frame);
  images_in_popover.push_back(image);
  fidel_options_vect.push_back(segmented_options);
  widgets_in_popover.push_back(button_entry);
  widgets_in_popover.push_back(content_frame);
  widgets_in_popover.push_back(segmented_options);
  widgets_in_popover.push_back(label_container);
  widgets_in_popover.push_back(prim_label);
  widgets_in_popover.push_back(supp_label);

  popover_frame->pack_start(*frame, Gtk::PACK_SHRINK);
  //  }
  //  if (image_exists == true) {
  //    std::cerr << "Error image pointer already in use\n";
  //  }
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
  std::chrono::high_resolution_clock::time_point start_point = std::chrono::high_resolution_clock::now();

  auto clear_job = std::async(std::launch::async, [this](){FidelPopover::clear();});

  std::vector<std::function<void()>> popover_song_entries;
  std::vector<std::function<void()>> popover_album_entries;

  btree<std::string> added_artists;
  btree<std::string> added_albums;

  std::vector<std::string> grouped_artists;
  std::vector<Gtk::Image*> grouped_raw_album_art;

  std::vector<int> num_songs_artist;

  if (populate_data.size() >= 1) {
    // Add songs to popover

    //    std::string current_album;
    std::vector<std::vector<std::string>> full_row_data;

    for (size_t iter = 0; iter < populate_data[Playlist::FILE_LOC].size(); iter++) {

      std::vector<std::string> row_data;
      row_data.push_back(Glib::Markup::escape_text(populate_data[Playlist::SONG_NAME][iter]));
      row_data.push_back(populate_data[Playlist::ARTIST][iter]);
      row_data.push_back(populate_data[Playlist::ALBUM][iter]);
      row_data.push_back(populate_data[Playlist::TIME][iter]);
      row_data.push_back(populate_data[Playlist::FILE_LOC][iter]);
      full_row_data.push_back(row_data);

      std::string song_name = Glib::Markup::escape_text(populate_data[Playlist::SONG_NAME][iter]);
      std::string artist = Glib::Markup::escape_text(populate_data[Playlist::ARTIST][iter]);
      std::string album = Glib::Markup::escape_text(populate_data[Playlist::ALBUM][iter]);
      std::string time = Glib::Markup::escape_text(populate_data[Playlist::TIME][iter]);
      std::string file_loc = populate_data[Playlist::FILE_LOC][iter];
      std::string supp_label = artist + " \u2015 " + album; // \u2015 is the unicode character for horizontal bar

      // Artist section 
      auto artist_retrieval_job = std::async(std::launch::async, [&](){
          if (added_artists.check(artist) == false) {
            added_artists.insert(artist);
            num_songs_artist.push_back(1);
            grouped_raw_album_art.push_back(audioinfo::get_album_art_by_name(album));
          }
          else {
            int artist_pos = added_artists.get_search_id();
            num_songs_artist[artist_pos]++;
          }
        });

      // Albums section
      auto album_retrieval_job = std::async(std::launch::async,[&]() {
          if (added_albums.check(album) == false) {
            added_albums.insert(album);

            std::function<void()> album_entry = [this, album, file_loc,
                                                 full_row_data, supp_label]() {
              Gtk::Image *album_art = audioinfo::get_album_art_by_name(album);

              FidelOptions *fidel_options = FidelPopover::add_entry(album_art, album, supp_label);
              PlaylistQueue *queue_playlist = fidel_ui::Instance()->get_playlist_queue();

              fidel_options->set_play_next_cb([this, queue_playlist, full_row_data, fidel_options](){
                  for (size_t iter = 0; iter < full_row_data.size(); iter++) {
                    queue_playlist->append_after_current(full_row_data[iter]);
                  }
                  queue_playlist->overview_notify();
                  fidel_options->hide_popover();
                  this->hide();
                });

              fidel_options->set_add_to_bottom_of_queue_cb([this, queue_playlist, full_row_data, fidel_options](){
                  for (size_t iter = 0; iter < full_row_data.size(); iter++) {
                    queue_playlist->append_row(full_row_data[iter]);
                  }
                  queue_playlist->overview_notify();
                  fidel_options->hide_popover();
                  this->hide();
                });
            };
            popover_album_entries.push_back(album_entry);
          }
        });

      // Song section
      if (iter <= 3) {
        std::function<void()> song_entry = [this, song_name, artist, album, time,
                                            file_loc, supp_label, full_row_data, iter]{

          Gtk::Image *album_art = audioinfo::get_album_art_by_name(album);

          FidelOptions *fidel_options = FidelPopover::add_entry(album_art, song_name, supp_label);
          PlaylistQueue *queue_playlist = fidel_ui::Instance()->get_playlist_queue();

          fidel_options->set_play_next_cb([this, queue_playlist, full_row_data,
                                           iter, fidel_options](){
                                            queue_playlist->append_after_current(full_row_data[iter]);
                                            fidel_options->hide_popover();
                                            this->hide();
                                          });

          fidel_options->set_add_to_bottom_of_queue_cb([this, queue_playlist,
                                                        full_row_data, iter, fidel_options](){
                                                         queue_playlist->append_row(full_row_data[iter]);
                                                         fidel_options->hide_popover();
                                                         this->hide();
                                                       });
        };

        popover_song_entries.push_back(song_entry);
      }

      artist_retrieval_job.get();
      album_retrieval_job.get();
    }

    clear_job.get();

    FidelPopover::add_title("Songs");
    for (size_t iter=0; iter < popover_song_entries.size(); iter++) {
      popover_song_entries[iter]();
      if (iter == 3)
        break;
    }

    FidelPopover::add_title("Artists");
    grouped_artists = added_artists.inorder();
    for (size_t iter = 0; iter < grouped_artists.size(); iter++) {
      Gtk::Image *album_art = grouped_raw_album_art[iter];

      FidelOptions *fidel_options = FidelPopover::add_entry(album_art, grouped_artists[iter], util::to_string(num_songs_artist[iter]));
      PlaylistQueue *queue_playlist = fidel_ui::Instance()->get_playlist_queue();
      fidel_options->set_play_next_cb([this, queue_playlist, full_row_data, fidel_options](){
          for (size_t iter = 0; iter < full_row_data.size(); iter++) {
            queue_playlist->append_after_current(full_row_data[iter]);
          }
          queue_playlist->overview_notify();
          fidel_options->hide_popover();
          this->hide();
        });
      fidel_options->set_add_to_bottom_of_queue_cb([this, queue_playlist, full_row_data, fidel_options](){
          for (size_t iter = 0; iter < full_row_data.size(); iter++) {
            queue_playlist->append_row(full_row_data[iter]);
          }
          queue_playlist->overview_notify();
          fidel_options->hide_popover();
          this->hide();
        });

      if (iter == 3)
        break;
    }

    FidelPopover::add_title("Albums");
    for (size_t iter=0; iter < popover_album_entries.size(); iter++) {
      popover_album_entries[iter]();
      if (iter == 2)
        break;
    }

  }
  std::chrono::high_resolution_clock::time_point end_point = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>( end_point - start_point ).count();

  std::cout << "Search Function Time: " << duration << std::endl;
}

void FidelPopover::pop_from_top()
{
  size_t pop_position = 0;
  popover_frame->remove(*toplevel_popover_entries[pop_position]);
  delete toplevel_popover_entries[pop_position];
  toplevel_popover_entries.erase(toplevel_popover_entries.begin() + pop_position);
}

void FidelPopover::pop_item()
{
  size_t pop_position = toplevel_popover_entries.size() - 1;
  popover_frame->remove(*toplevel_popover_entries[pop_position]);
  delete toplevel_popover_entries[pop_position];
  toplevel_popover_entries.erase(toplevel_popover_entries.begin() + pop_position);
}
