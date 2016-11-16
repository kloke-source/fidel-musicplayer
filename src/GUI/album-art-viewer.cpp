#include <gtkmm.h>
#include <iostream>
#include<vector>
#include <GUI/album-art.h>
#include <Utilities/util.h>
#include <Utilities/btree.h>
#include <GUI/album-art-viewer.h>
#include <Audio-Info/audioinfo.h>
#include <Audio-Library/audio-library.h>

AlbumArtViewer::AlbumArtViewer()
{
  AlbumArtViewer::init();
  AlbumArtViewer::init_connections();
}

AlbumArtViewer::~AlbumArtViewer(){}

void AlbumArtViewer::init_connections()
{
  this->signal_size_allocate().connect(sigc::mem_fun(this, &AlbumArtViewer::resize_handler));
}

void AlbumArtViewer::resize_handler(Gtk::Allocation& allocation)
{
  double width = (double)allocation.get_width();
  this->viewer_width = width;

  //  if (width != viewer_width) {
  int album_num = std::round((viewer_width - padding)/(padding + ideal_album_width));
  std::cout << "Calculated album num " << album_num << std::endl;
  double album_size = (viewer_width - ((album_num - 1) * padding))/album_num; // original was -> (viewer_width - ((album_num + 1) * padding))/album_num;

  for (size_t iter = 0 ; iter < full_album_art.size(); iter++) {
    full_album_art[iter].set_size(album_size, album_size);
  }

  std::cout << "Album num " << album_num << std::endl;
  std::cout << "Curr_items_per row " << curr_items_per_row << std::endl;

  if (album_num != curr_items_per_row && album_num != 0)
    AlbumArtViewer::set_items_per_row(album_num);
  //  }
}

void AlbumArtViewer::init()
{
  if (viewer_width != 0) {
    int album_num = ideal_album_num; //std::round((viewer_width - padding)/(padding + ideal_album_width));
    double album_size = (viewer_width - ((album_num - 1) *
                                         padding))/album_num; // original was -> (viewer_width - ((album_num + 1) * padding))/album_num;

    std::cout << "Album size " << album_size << std::endl;
    std::vector<AlbumSummary> full_album_summary = AudioLibrary::get_album_summary();

    if (!full_album_summary.empty()) {
      double req_row_calc = (double)full_album_summary.size()/album_num;
      int req_rows = util::round_up(req_row_calc);

      int col_iter = 0;
      int row_iter = 0;

      for (size_t iter = 0; iter < full_album_summary.size(); iter++) {

        this->full_album_art.push_back(full_album_summary[iter]);
        this->full_album_art[iter].set_size(album_size, album_size);
        this->album_grid.attach(full_album_art[iter], col_iter, row_iter, 1, 1);

        if (col_iter == (album_num - 1)) {
          row_iter++;
          col_iter = 0;
        }
        else
          col_iter++;
      }

      this->curr_row_amt = req_rows;
      this->curr_items_per_row = album_num;
      std::cout << "Init cur_items_per_row " << curr_items_per_row << std::endl;

    }

    this->initialized = true;
    this->album_grid.set_row_spacing(25);
    this->album_grid.set_column_spacing(25);
    this->add(this->album_grid);
    this->album_grid.override_background_color(Gdk::RGBA("#2D2D2D"));
    this->album_grid.show_all();
    this->show_all();
  }
}

void AlbumArtViewer::set_items_per_row(int item_per_row)
{
  std::cout << "Set items per row -> " << item_per_row << " -> ";
  if (item_per_row != 0 && curr_items_per_row != item_per_row) {
    std::cout << "Executed -> ";
    if (full_album_art.size() > 0) {
      cout << "No of arts " << full_album_art.size() << " -> ";
      int req_rows = util::round_up((double)full_album_art.size()/item_per_row);
      int fully_filled_rows = ((int)(full_album_art.size()/curr_items_per_row)); //  These are the rows that have all of their columns populated with album art.
      int partially_filled_row = req_rows - fully_filled_rows;

      std::cout << "Fully filled calc (items per row = " << curr_items_per_row << "  )-> " <<  full_album_art.size()/curr_items_per_row << std::endl;
      int album_art_in_filled_rows = (curr_items_per_row * fully_filled_rows); // Total number of album art in all of the fully filled rows


      if (item_per_row < curr_items_per_row) {
        std::vector<AlbumArt*> removed_album_art;
        for (size_t col_iter = curr_items_per_row - 1; col_iter > item_per_row -1; col_iter--){  // 1 is minused because item_per_row and grid cols don't incl zero
          int remaining_album_art = full_album_art.size() % (curr_items_per_row); // The number of album art in the partially filled row

          for (size_t row_iter = 0; row_iter < curr_row_amt; row_iter++) {
            std::cout << "Col iter = " << col_iter << " Row iter = " << row_iter << std::endl;
            int removed_art_pos = ((col_iter + 1) * (row_iter + 1)) - 1;

            std::cout << "Removed art pos " << removed_art_pos << std::endl;

            if ((col_iter + 1) > remaining_album_art) {
              if ((row_iter + 1) <= fully_filled_rows) {
                AlbumArt* remv_album_art = (AlbumArt*)album_grid.get_child_at(col_iter,row_iter);
                //                std::cout << "Pushed -> " << full_album_art[removed_art_pos].album_name << std::endl;
                std::cout << "Pushed -> " << remv_album_art->get_album_name() << std::endl;
                removed_album_art.push_back(remv_album_art);
              }
            }
            else {
              AlbumArt* remv_album_art = (AlbumArt*)album_grid.get_child_at(col_iter,row_iter);
              // std::cout << "Pushed2 -> " << full_album_art[removed_art_pos].album_name << std::endl;
              std::cout << "Pushed -> " << remv_album_art->get_album_name() << std::endl;
              removed_album_art.push_back(remv_album_art);
            }
          }
          album_grid.remove_column(col_iter);
        }

        this->curr_items_per_row = item_per_row;
        int remaining_album_art = (full_album_art.size() - removed_album_art.size()) % (curr_row_amt * curr_items_per_row); // The number of album art in the partially filled row
        int add_back_col_iter = remaining_album_art;  //  This variable is the iterator position where the removed album art will be added.
        int row_iter = curr_row_amt - 1;

        if (remaining_album_art == 0)
          row_iter++;

        std::cout << "---------------------------" << std::endl;
        std::cout << "Removed album art " << removed_album_art.size() << std::endl;
        std::cout << "Set items per row -> " << item_per_row << " -> ";
        std::cout << "Curr row amt " << curr_row_amt << std::endl;
        std::cout << "Curr col amt " << curr_items_per_row << std::endl;
        std::cout << "Album art size -> " << full_album_art.size() << std::endl;
        std::cout << "Fully filled rows " << fully_filled_rows << std::endl;
        std::cout << "Rem calc (curr_items_per_row * fully_filled_rows) " << (curr_items_per_row * fully_filled_rows) << std::endl;
        std::cout << "  Row iter " << row_iter << std::endl;
        std::cout << "Add back col iter " << add_back_col_iter << std::endl;
        std::cout << "Curr row amt " << curr_row_amt << std::endl;

        if (curr_row_amt != 0) {
          for (size_t iter = 0; iter < removed_album_art.size(); iter++) {
            this->album_grid.attach(*removed_album_art[iter], add_back_col_iter, row_iter, 1, 1);
            //            std::cout << "Added back pos (" << row_iter << "," << add_back_col_iter << ")-> " << full_album_art[removed_album_art[iter]].album_name << std::endl;

            if (add_back_col_iter == (item_per_row - 1)) {
              row_iter++;
              add_back_col_iter = 0;
            }
            else
              add_back_col_iter++;

          }
        }
        // int removed_columns = curr_items_per_row - item_per_row;
        this->curr_row_amt = row_iter + 1;
        //      this->curr_items_per_row = item_per_row;
      }
    }
  }
}


/*
  enum album_fields
  {
  ID,
  ALBUM_NAME,
  ALBUM_ART_LOCATION,
  SONGS_IN_ALBUM = 2,
  FILE_LOCATION = 3
  };

  int grid_rows;
  int grid_cols=8;
  vector<AlbumArt*> full_album_art;

  AlbumArtViewer::AlbumArtViewer()
  {
  //this->viewer_frame = new Gtk::Box();
  this->album_grid = new Gtk::Grid();
  this->viewer_scrolled_window = new Gtk::ScrolledWindow();
  AlbumArtViewer::init(); // seg fault
  }

  AlbumArtViewer::AlbumArtViewer(Gtk::Widget *parent)
  {
  this->parent = parent;
  this->album_grid = new Gtk::Grid();
  //this->viewer_frame = new Gtk::Box();
  this->viewer_scrolled_window = new Gtk::ScrolledWindow();
  AlbumArtViewer::init();
  }

  AlbumArtViewer::~AlbumArtViewer()
  {}

  void AlbumArtViewer::init(Gtk::Widget *parent)
  {
  this->parent = parent;
  AlbumArtViewer::init();
  }

  void AlbumArtViewer::init()
  {
  //vector<Gtk::Image*> full_album_art = audioinfo::get_all_album_art(200, 200);
  viewer_frame = new Gtk::Box();
  vector<vector<Glib::ustring> > album_info = AudioLibrary::batch_collect_info("album_information");
  vector<vector<Glib::ustring> > album_summ = AudioLibrary::batch_collect_info("album_summary");

  cout << "No. of available album art covers " << album_info.size() << endl;

  for (size_t album_art_iter = 0; album_art_iter < album_info.size(); album_art_iter++){
  AlbumArt *album_art = new AlbumArt();
  album_art->set_album_data(album_info[album_art_iter]);
  Glib::ustring album_name = album_info[album_art_iter][ALBUM_NAME];
  cout << "No. of entries in album summ " << album_summ.size() << endl;
  vector<Glib::ustring> songs_in_album;
  vector<Glib::ustring> song_file_locs;
  for (size_t album_summ_iter = 0; album_summ_iter < album_summ.size(); album_summ_iter++){
  if (album_summ[album_summ_iter][ALBUM_NAME] == album_name)
  {
  songs_in_album.push_back(album_summ[album_summ_iter][SONGS_IN_ALBUM]);
  song_file_locs.push_back(album_summ[album_summ_iter][FILE_LOCATION]);
  }
  }
  album_art->set_songs_in_album(songs_in_album);
  album_art->set_song_file_locs(song_file_locs);
  album_art->set_size(215, 215);
  full_album_art.push_back(album_art);
  }

  double needed_rows = (double)full_album_art.size()/grid_cols; //8 images per row
  cout << "NEEDED ROWS " << util::round_up(needed_rows) << endl;
  grid_rows = util::round_up(needed_rows);
  size_t image_iter=0;
  grid_rows = util::round_up(needed_rows);
  for (int rows = 0; rows < util::round_up(needed_rows); rows++){
  for (int columns = 0; columns < grid_cols; columns++){
  if (image_iter == full_album_art.size()){
  break;
  }
  //util::resize_image(full_album_art[image_iter]->get_art(), 150, 150);
  album_grid->attach(*full_album_art[image_iter]->get_art(), columns, rows, 1, 1);
  full_album_art[image_iter]->get_art()->show();
  image_iter++;
  }
  }

  album_grid->set_row_spacing(25);
  album_grid->set_column_spacing(25);
  viewer_scrolled_window->add(*album_grid);
  album_grid->override_background_color(Gdk::RGBA("#2D2D2D"));
  viewer_frame->pack_start(*viewer_scrolled_window, Gtk::PACK_EXPAND_WIDGET);
  //album_grid->insert_column(0);
  //album_grid->insert_column(9);
  //AlbumArtViewer::set_items_per_row(4);
  cout << "Album art size " << full_album_art.size() << endl;
  AlbumArtViewer::connect_signals();
  viewer_frame->show();
  album_grid->show();
  viewer_scrolled_window->show();
  }

  void AlbumArtViewer::show()
  {
  //album_grid->show();
  //viewer_frame->show();
  //viewer_scrolled_window->show();
  }

  Gtk::Box* AlbumArtViewer::get_frame()
  {
  return viewer_frame;
  }

  void AlbumArtViewer::connect_signals()
  {
  viewer_scrolled_window->signal_size_allocate().connect(sigc::mem_fun(this, &AlbumArtViewer::resize_handler));
  }

  void AlbumArtViewer::resize_children(int size)
  {
  for (size_t iter = 0; iter < full_album_art.size(); iter++){
  util::resize_image(full_album_art[iter]->get_art(), size, size);
  }
  }

  void AlbumArtViewer::set_items_per_row(int item_per_row)
  {
  if (full_album_art.size() > 0){
  cout << "No of arts " << full_album_art.size() << endl;
  double needed_rows = (double)full_album_art.size()/item_per_row; //8 images per row
  needed_rows = util::round_up(needed_rows);
  if (item_per_row < grid_cols){
  for (size_t col_iter = grid_cols - 1; col_iter > item_per_row - 1; col_iter--){ // 1 is minused because item_per_row and grid cols don't incl zero
  cout << "Removed column " << col_iter << endl;
  album_grid->remove_column(col_iter);
  }
  int removed_columns = grid_cols - item_per_row;
  int removed_art;// = 8; //= removed_columns * grid_rows;
  if (full_album_art.size() % grid_cols == 0){
  removed_art = removed_columns * grid_rows;
  }
  else {
  int left_over = full_album_art.size() % grid_cols;
  if (left_over > grid_cols - removed_columns){
  removed_art = removed_columns * (full_album_art.size()/grid_cols);
  cout << "REMOVED ART 1 " << removed_art << endl;
  removed_art += left_over - (grid_cols - removed_columns);
  cout << "REMOVED artssssssssssss " << removed_art << endl;
  }
  else {
  removed_art = removed_columns * (int)(full_album_art.size()/grid_cols);
  }
  }
  int row_iter;// = needed_rows - grid_rows; // 1 is minused because zero isn't taken into account
  if (full_album_art.size() % grid_cols == 0){
  row_iter = grid_rows;
  }
  else {
  row_iter = grid_rows - 1;
  }
  cout << "Row iter " << row_iter << endl;
  cout << "REMOVED COLUMNS " << removed_columns << endl;
  int col_iter = full_album_art.size() % grid_cols;// - 1;
  if (col_iter > item_per_row){
  col_iter = 0;
  }
  cout << "REQ Rows " << needed_rows << endl;
  cout << "INIT COL ITER " << col_iter << endl;
  cout << "Removed cols " << removed_columns << endl;
  int removed_pos = grid_cols - removed_columns;
  cout << "REMOVED POS " << removed_pos << endl;
  int art_pos = removed_pos;
  int art_pos_helper = 0;
  cout << "Art pos " << removed_pos << endl;
  cout << "Removed art " << removed_art << endl;
  for (size_t iter = 0; iter < removed_art; iter++){
  cout << "ITER " << iter << endl;
  //if (art_pos == grid_cols){
  if (art_pos_helper == grid_cols - removed_pos){
  art_pos += removed_pos;
  art_pos_helper = 0;
  cout << "Art pos in loop" << removed_pos << endl;
  }
  if (col_iter == item_per_row){
  col_iter = 0;
  row_iter++;
  }
  //album_grid->attach(*full_album_art[iter+grid_rows]->get_art(), col_iter, row_iter, 1, 1);
  album_grid->attach(*full_album_art[art_pos]->get_art(), col_iter, row_iter, 1, 1);
  cout << "Added at row " << row_iter << " col " << col_iter << " Art pos " << art_pos << endl;
  col_iter++;
  art_pos++;
  art_pos_helper++;
  }
  }
  else {
  for (size_t col_iter = grid_cols - 1; col_iter < item_per_row - 1; col_iter++){ // 1 is minused because item_per_row and grid cols don't incl zero
  cout << "Added column " << col_iter << endl;
  album_grid->insert_column(col_iter);
  }
  }
  grid_cols = item_per_row;
  grid_rows = needed_rows;
  }
  }

  void AlbumArtViewer::resize_handler(Gtk::Allocation &allocation)
  {
  frame_width = allocation.get_width();
  frame_height = allocation.get_height();

  int album_art_min_size = 100;
  int preff_album_art_size = 215;
  int album_art_max_size = 225;

  int min_album_art_per_row = 4;
  int preff_album_art_per_row = 6;

  int spacing = 25;
  int determ_album_art_size;
  int poss_album_art_per_row = frame_width/preff_album_art_size;
  //cout << "Poss album art per row " << poss_album_art_per_row << endl;

  //AlbumArtViewer::set_items_per_row(11);
  //album_grid->remove(*(Gtk::Widget*)full_album_art[0]->get_art());
  //album_grid->remove_row(1);
  //AlbumArtViewer::resize_children(preff_album_art_size);
  //AlbumArtViewer::set_items_per_row(poss_album_art_per_row);

  if (poss_album_art_per_row == preff_album_art_per_row){
  determ_album_art_size = preff_album_art_size;
  AlbumArtViewer::resize_children(determ_album_art_size);
  }
  if (poss_album_art_per_row < preff_album_art_per_row && poss_album_art_per_row > min_album_art_per_row){
  determ_album_art_size = preff_album_art_size;
  AlbumArtViewer::set_items_per_row(poss_album_art_per_row);
  AlbumArtViewer::resize_children(determ_album_art_size);
  }
  if (poss_album_art_per_row < min_album_art_per_row){
  determ_album_art_size = frame_width/preff_album_art_per_row;
  if (determ_album_art_size < album_art_min_size){

  }
  poss_album_art_per_row = determ_album_art_size/preff_album_art_per_row;
  AlbumArtViewer::set_items_per_row(poss_album_art_per_row);
  AlbumArtViewer::resize_children(determ_album_art_size);
  //if (determ_album_art_size )
  }
  //if (poss_album_art_per_row )

  cout << "AlbumArtViewer width changed -> " << frame_width << endl;
  cout << "AlbumArtViewer height changed -> " << frame_height << endl;

  }
*/
