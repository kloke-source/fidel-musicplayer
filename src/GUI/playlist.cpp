#include <GUI/playlist.h>
#include <iostream>
#include <Utilities/util.h>
#include <Audio/playback.h>
#include <GUI/fidel-popover.h>

typedef Singleton<FidelPopover> fidel_popover;

Playlist::Playlist()
{
  for (int iter=0; iter < 4; iter++){
    btree<std::string> col_btree;
    playlist_info_store.push_back(col_btree);
  }
  Playlist::init_playlist();
  Playlist::init_connections();
}

Playlist::~Playlist(){}

void Playlist::init_connections()
{
  playlist_tree_view->set_events(Gdk::BUTTON_PRESS_MASK);
  playlist_tree_view->signal_row_activated().connect(sigc::mem_fun(this, &Playlist::on_row_double_clicked));
  playlist_tree_view->signal_button_release_event().connect(sigc::mem_fun(this, &Playlist::on_right_click));
  this->signal_size_allocate().connect(sigc::mem_fun(this, &Playlist::resize_handler));
  track_finished_connection = audio_playback::Instance()->signal_track_finished().connect(sigc::mem_fun(this, &Playlist::on_track_finished));
}

void Playlist::init_playlist()
{
  playlist_tree_view = new Gtk::TreeView();
  playlist_tree_view->override_color(Gdk::RGBA("#d7d7d7"));

  string style_sheet = "GtkTreeView:selected {background: #36D7B7; color: black;}\n";

  Glib::RefPtr<Gtk::StyleContext> stylecontext = playlist_tree_view->get_style_context();
  Glib::RefPtr<Gtk::CssProvider> cssprov = Gtk::CssProvider::create();
  cssprov->load_from_data(style_sheet);
  stylecontext->add_provider(cssprov, GTK_STYLE_PROVIDER_PRIORITY_USER);
  stylecontext->context_save();

  default_font.set_family("Open Sans Light");
  default_font.set_size(default_font_size * PANGO_SCALE);

  playlist_tree_view->override_font(default_font);

  this->add(*playlist_tree_view);
  this->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);

  playlist_model = Gtk::ListStore::create(playlist_columns);
  playlist_tree_view->set_model(playlist_model);
  // playlist_tree_view->set_headers_visible(false);

  playlist_tree_view->append_column("Name", playlist_columns.col_name);
  playlist_tree_view->append_column("Artist", playlist_columns.col_artist);
  playlist_tree_view->append_column("Album", playlist_columns.col_album);
  playlist_tree_view->append_column("Time", playlist_columns.col_time);
  
  for (int col_iter = 0; col_iter < 4; col_iter++) {
    Gtk::TreeViewColumn *column = playlist_tree_view->get_column(col_iter);
    Gtk::CellRenderer *cell_renderer = playlist_tree_view->get_column_cell_renderer(col_iter);
    column->add_attribute(cell_renderer->property_cell_background(), playlist_columns.col_color);
  }
}

void Playlist::enable()
{
  std::cout << "Playlist enable " << std::endl;
  track_finished_connection = audio_playback::Instance()->signal_track_finished().connect(sigc::mem_fun(this, &Playlist::on_track_finished));
}

void Playlist::disable()
{
  std::cout << "Playlist disabled " << std::endl;
  track_finished_connection.disconnect();
}

void Playlist::prepend_row(std::vector<std::string> row_data)
{
  total_songs++;
  Gtk::TreeModel::Row row = *(playlist_model->prepend());
  row[playlist_columns.col_name] = row_data[COL_NAME];
  row[playlist_columns.col_artist] = row_data[COL_ARTIST];
  row[playlist_columns.col_album] = row_data[COL_ALBUM];
  row[playlist_columns.col_time] = row_data[COL_TIME];
  row[playlist_columns.col_file_location] = row_data[COL_FILE_LOC];
  
  for(int iter=0; iter < 4; iter++){
    playlist_info_store[iter].insert(row_data[iter], file_count_iter);
  }
  
  file_count_iter++;
  if (alternate_color == false){
    row[playlist_columns.col_color] = "#464545";
    alternate_color = true;    
  }
  else {
    row[playlist_columns.col_color] = "#373535";
    alternate_color = false;    
  }  
}

void Playlist::append_after_current(std::vector<std::string> row_data)
{
  Gtk::TreeModel::Children rows = playlist_model->children();
  Gtk::TreeModel::Children::iterator after_curr_iterator = rows[curr_song_iterator];
  total_songs++;
  Gtk::TreeModel::Row row = *(playlist_model->insert_after(after_curr_iterator));
  
  row[playlist_columns.col_name] = row_data[COL_NAME];
  row[playlist_columns.col_artist] = row_data[COL_ARTIST];
  row[playlist_columns.col_album] = row_data[COL_ALBUM];
  row[playlist_columns.col_time] = row_data[COL_TIME];
  row[playlist_columns.col_file_location] = row_data[COL_FILE_LOC];
  
  file_count_iter++;
  if (alternate_color == false){
    row[playlist_columns.col_color] = "#464545";
    alternate_color = true;    
  }
  else {
    row[playlist_columns.col_color] = "#373535";
    alternate_color = false;    
  }  
}

void Playlist::append_row(std::vector<std::string> row_data)
{
  total_songs++;
  Gtk::TreeModel::Row row = *(playlist_model->append());
  row[playlist_columns.col_name] = row_data[COL_NAME];
  row[playlist_columns.col_artist] = row_data[COL_ARTIST];
  row[playlist_columns.col_album] = row_data[COL_ALBUM];
  row[playlist_columns.col_time] = row_data[COL_TIME];
  row[playlist_columns.col_file_location] = row_data[COL_FILE_LOC];
  
  for(int iter=0; iter < 4; iter++) {
    playlist_info_store[iter].insert(row_data[iter], file_count_iter);
  }
  
  file_count_iter++;
  if (alternate_color == false){
    row[playlist_columns.col_color] = "#464545";
    alternate_color = true;    
  }
  else {
    row[playlist_columns.col_color] = "#373535";
    alternate_color = false;    
  }
}

void Playlist::append_row()
{
  total_songs++;
  Gtk::TreeModel::Row row = *(playlist_model->append());
  row[playlist_columns.col_name] = "";
  row[playlist_columns.col_artist] = "";
  row[playlist_columns.col_album] = "";
  row[playlist_columns.col_time] = "";
  row[playlist_columns.col_file_location] = "";
  
  if (alternate_color == false){
    row[playlist_columns.col_color] = "#464545";
  }
  else {
    row[playlist_columns.col_color] = "#373535";
  }

  if (alternate_color == false)
    alternate_color = true;
  else
    alternate_color = false;
}

void Playlist::link_to_search_entry(Gtk::SearchEntry *search_entry)
{
  this->playlist_search_entry = search_entry;
  fidel_popover::Instance()->set_relative_to(*search_entry);
  fidel_popover::Instance()->set_position(Gtk::POS_BOTTOM);
  fidel_popover::Instance()->set_modal(false);
  search_entry->signal_insert_text().connect(sigc::mem_fun(this, &Playlist::on_insert_text));
  search_entry->signal_delete_text().connect(sigc::mem_fun(this, &Playlist::on_delete_text));
}

void Playlist::on_insert_text(const std::string& text, int* character_num)
{
  Playlist::search_playlist(this->playlist_search_entry->get_text());
}

void Playlist::on_delete_text(int start_pos, int end_pos)
{
  std::string search_term = playlist_search_entry->get_text();
  Playlist::search_playlist(search_term);
}

void Playlist::search_playlist(std::string search_term)
{
  Gtk::TreeModel::Children rows = playlist_model->children();
  Glib::RefPtr<Gtk::TreeView::Selection> selection = playlist_tree_view->get_selection();
  Gtk::TreeModel::Children::iterator iterator = selection->get_selected();
  selection->unselect(iterator);
  std::vector<std::vector<std::string>> full_search_results;
  std::vector<std::string> search_results;
  std::vector<std::string> found_info;
  std::vector<int> search_ids;

  bool found = false;
  int search_options = 2;
  
  enum {
    REC_SEARCH,
    ITER_SEARCH
  };
  
  for (size_t search_type = 0; search_type < search_options; search_type++) {
    for (size_t iter = 0; iter < 3; iter++) {
      if (search_type == REC_SEARCH) {
	search_results = playlist_info_store[iter].rec_search(search_term);
	search_ids = playlist_info_store[iter].get_search_ids();
      }
      if (search_type == ITER_SEARCH) {
	search_results = playlist_info_store[iter].iterative_search(search_term);
	search_ids = playlist_info_store[iter].get_iterated_ids();      
      }
      if (search_results.size() > 0) {
	found = true;
	iterator = rows[search_ids[0]];
	playlist_tree_view->scroll_to_row(playlist_model->get_path(iterator));
	selection->select(iterator);

	std::vector<std::string> song_name_search_results;
	std::vector<std::string> artist_search_results;
	std::vector<std::string> album_search_results;
	std::vector<std::string> file_loc_search_results;

	for (size_t iter = 0; iter < search_ids.size(); iter++) {
	  song_name_search_results.push_back(rows[search_ids[iter]].get_value(playlist_columns.col_name));
	  std::string artist_name = rows[search_ids[iter]].get_value(playlist_columns.col_artist);
	  std::string album_name = rows[search_ids[iter]].get_value(playlist_columns.col_album);
	  artist_search_results.push_back(artist_name);
	  album_search_results.push_back(album_name);	    
	  file_loc_search_results.push_back(rows[search_ids[iter]].get_value(playlist_columns.col_file_location));
	}
	full_search_results.push_back(song_name_search_results);
	full_search_results.push_back(artist_search_results);
	full_search_results.push_back(album_search_results);
	full_search_results.push_back(file_loc_search_results);
	break;
      }
    }
    if (found == true)
      break;
  }
  fidel_popover::Instance()->populate(full_search_results);
  fidel_popover::Instance()->show_all();
  /*  
      for (size_t prim_iter = 0; prim_iter < full_search_results.size(); prim_iter++) {
      //std::cout << found_info[prim_iter] << " ---> " << std::endl;
      switch (prim_iter) {
      case COL_NAME:
      std::cout << "Songs --->" << std::endl;
      break;
      case COL_ARTIST:
      std::cout << "Artists --->" << std::endl;
      break;
      case COL_ALBUM:
      std::cout << "Albums --->" << std::endl;
      break;
      case 3:
      std::cout << "File Locations --->" << std::endl;
      break;
      }
      for (size_t sec_iter = 0; sec_iter < full_search_results[prim_iter].size(); sec_iter++) {
      std::cout << full_search_results[prim_iter][sec_iter] << std::endl;
      }
      }
  */
}

void Playlist::resize_handler(Gtk::Allocation &allocation)
{
  int window_width = allocation.get_width();
  int window_height = allocation.get_height();

  // cout << "Window width: " << window_width << endl;
  // cout << "Window height: " << window_height << endl;

  playlist_tree_view->get_column(0)->set_max_width(.55 * window_width);
  playlist_tree_view->get_column(1)->set_max_width(.15 * window_width);
  playlist_tree_view->get_column(2)->set_max_width(.15 * window_width);
  playlist_tree_view->get_column(3)->set_max_width(.05 * window_width);

  // cout << "Column 1 width : " << .55 * window_width << endl;
  // cout << "Column 2 width : " << .15 * window_width << endl;
  // cout << "Column 3 width : " << .15 * window_width << endl;
  // cout << "Column 4 width : " << .05 * window_width << endl;

  for (int col_iter = 0; col_iter < 4; col_iter++) {
    playlist_tree_view->get_column(col_iter)->set_expand(true);
    Gtk::CellRendererText* playlist = dynamic_cast<Gtk::CellRendererText*>(playlist_tree_view->get_column_cell_renderer(col_iter));
    playlist->property_ellipsize() = Pango::ELLIPSIZE_END;
  }
}

void Playlist::on_row_double_clicked(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn *column)
{
  cout << "double clicked signal emitted" << endl;
  Glib::RefPtr<Gtk::TreeSelection> selection = playlist_tree_view->get_selection();
  
  Gtk::TreeModel::iterator selected_row = selection->get_selected();
  //curr_song_iterator = (int)selected_row;
  Gtk::TreeModel::Row row = *selected_row;
  Gtk::TreeModel::Path selected_path = playlist_model->get_path(selected_row);
  
  curr_song_iterator = util::to_int(selected_path.to_string());
  
  std::string file_location = row.get_value(playlist_columns.col_file_location);
  fflush(stdout);
  printf("\nselected file_location: %s", file_location.data());
  audio_playback::Instance()->audio_file(util::to_char(file_location));
  fflush(stdout);
}

bool Playlist::on_right_click(GdkEventButton *button_event)
{
  if (button_event->button == RIGHT_CLICK) {
    std::cout << "Right clicked " << std::endl;
    Glib::RefPtr<Gtk::TreeView::Selection> selection = playlist_tree_view->get_selection();
    Gtk::TreeModel::iterator selected_row = selection->get_selected();  
    Gtk::TreeModel::Row row = *selected_row;
  
    FidelOptions fidel_options;

    std::vector<std::string> row_data;
    row_data.push_back((row[playlist_columns.col_name]));
    row_data.push_back((row[playlist_columns.col_artist]));
    row_data.push_back((row[playlist_columns.col_album]));
    row_data.push_back((row[playlist_columns.col_time]));
    row_data.push_back((row[playlist_columns.col_file_location]));

    FidelPopover *options_popover = fidel_options.get_popover();

    Playlist* queue = fidel_ui::Instance()->get_playlist_queue();
    std::function<void()> play_next_cb_func = [row_data, queue, options_popover](){
      queue->append_after_current(row_data);
      options_popover->hide();
    };
      
    std::function<void()> add_to_bottom_of_queue_cb_func = [row_data, queue, options_popover](){
      queue->append_row(row_data);
      options_popover->hide();      
    };

    fidel_options.set_add_to_bottom_of_queue_cb(add_to_bottom_of_queue_cb_func);
    fidel_options.set_play_next_cb(play_next_cb_func);

    const Gdk::Rectangle pointing_area(button_event->x, button_event->y, 1, 1);
    options_popover->set_pointing_to(pointing_area);
    options_popover->set_relative_to(*this);
    options_popover->show_all();
  }
  return true;
}


void Playlist::on_track_finished()
{
  std::cout << "Track has finished" << std::endl;
  if (curr_song_iterator != (total_songs - 1))
    curr_song_iterator++;
  else
    curr_song_iterator = 0;
  
  Glib::RefPtr<Gtk::TreeView::Selection> selection = playlist_tree_view->get_selection();
  Gtk::TreeModel::Children::iterator iterator = selection->get_selected();

  // unselect finished track
  selection->unselect(iterator);

  Gtk::TreeModel::Children rows = playlist_model->children();
  
  // select next track
  iterator = rows[curr_song_iterator];
  playlist_tree_view->scroll_to_row(playlist_model->get_path(iterator));
  selection->select(iterator);

  std::string file_location = rows[curr_song_iterator].get_value(playlist_columns.col_file_location);  
  audio_playback::Instance()->audio_file(util::to_char(file_location));
}
