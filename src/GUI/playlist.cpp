#include <GUI/playlist.h>
#include <iostream>
#include <Utilities/util.h>
#include <Audio/playback.h>
#include <Utilities/btree.h>
#include <vector>

enum {
  COL_NAME,
  COL_ARTIST,
  COL_ALBUM,
  COL_TIME,
  COL_FILE_LOC
};

Playlist::Playlist_Columns playlist_columns;
Gtk::TreeView *playlist_tree_view;
Glib::RefPtr<Gtk::ListStore> playlist_model;
std::vector<btree<std::string>> playlist_info_store;

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
  playlist_tree_view->signal_row_activated().connect(sigc::mem_fun(this, &Playlist::on_double_click_handler));
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

  //playlist_font.set_family("DS-Digital");
  //playlist_font.set_size(20 * PANGO_SCALE);

  //playlist_tree_view->override_font(playlist_font);

  this->add(*playlist_tree_view);
  this->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);

  playlist_model = Gtk::ListStore::create(playlist_columns);
  playlist_tree_view->set_model(playlist_model);
  playlist_tree_view->set_headers_visible(false);

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

bool alternate_color = false;
int file_count_iter = 0;

void Playlist::add_list_store_row(std::vector<std::string> row_data)
{
  Gtk::TreeModel::Row row = *(playlist_model->append());
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
  }
  else {
    row[playlist_columns.col_color] = "#373535";
  }

  bool skip = false;
  if (alternate_color == false){
    alternate_color = true;
    skip = true;
  }
  if (alternate_color == true && skip == false){
    alternate_color = false;
  }
}

void Playlist::on_double_click_handler(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn *column)
{
  cout << "double clicked signal emitted" << endl;
  Glib::RefPtr<Gtk::TreeSelection> selection = playlist_tree_view->get_selection();
  Gtk::TreeModel::iterator selected_row = selection->get_selected();
  Gtk::TreeModel::Row row = *selected_row;
  Glib::ustring file_location = row.get_value(playlist_columns.col_file_location);
  fflush(stdout);
  printf("\nselected file_location: %s", file_location.data());
  audio_playback::Instance()->audio_file(util::to_char(file_location));
  fflush(stdout);
}
