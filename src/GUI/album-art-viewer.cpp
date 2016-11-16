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
  double resized_width = (double)allocation.get_width();

  if (resized_width != this->viewer_width)
    {
      this->viewer_width = resized_width;
      int album_num = std::round((viewer_width - padding)/(padding + ideal_album_width));
      double album_size = (viewer_width - ((album_num - 1) * padding))/album_num; // original was -> (viewer_width - ((album_num + 1) * padding))/album_num;


      for (size_t iter = 0 ; iter < full_album_art.size(); iter++) {
        full_album_art[iter].set_size(album_size, album_size);
        full_album_art[iter].queue_draw();
      }

      if (album_num != curr_items_per_row && album_num != 0)
        AlbumArtViewer::set_items_per_row(album_num);

      this->queue_draw();
      this->album_grid.queue_draw();
    }
}

void AlbumArtViewer::init()
{
  if (viewer_width != 0) {
    int album_num = ideal_album_num; //std::round((viewer_width - padding)/(padding + ideal_album_width));
    double album_size = (viewer_width - ((album_num - 1) *
                                         padding))/album_num; // original was -> (viewer_width - ((album_num + 1) * padding))/album_num;

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

  if (item_per_row != 0 && curr_items_per_row != item_per_row) {
    if (full_album_art.size() > 0) {
      //  These are the rows that have all of their columns populated with album art.
      int fully_filled_rows = ((int)(full_album_art.size()/curr_items_per_row));

      if (item_per_row < curr_items_per_row)
        {
          int req_rows = util::round_up((double)full_album_art.size()/item_per_row);
          int leftover = full_album_art.size() % curr_items_per_row;
          int total_to_be_shifted = 0;

          int to_shift_col_iter = this->curr_items_per_row - 1;

          int shift_col_iter = leftover;
          int shift_row_iter = curr_row_amt - 1;

          if (item_per_row <= leftover) {
            std::cout << "Called " << std::endl;
            total_to_be_shifted = full_album_art.size() - (curr_row_amt * item_per_row);
          }
          else
            total_to_be_shifted = ((curr_items_per_row - item_per_row) * (curr_row_amt - 1));

          if (leftover == 0)
            shift_row_iter++;
          else if (leftover >= item_per_row) {
            shift_col_iter = 0;
            shift_row_iter++;
          }


          int art_shifted = 0;
          std::cout << "Leftover " << leftover << std::endl;
          std::cout << "Curr row amt " << curr_row_amt << std::endl;
          std::cout << "Total to be shifted " << total_to_be_shifted << std::endl;
          std::cout << "Initial to shift col iter " << to_shift_col_iter << std::endl;
          std::cout << "Items per row " << item_per_row << std::endl;
          std::cout << "Curr items per row " << curr_items_per_row << std::endl;
          std::cout << "Full album art size  " << full_album_art.size() << std::endl;

          while (to_shift_col_iter + 1 > item_per_row) {
            int rows_in_curr_col = curr_row_amt - 1;

            if (to_shift_col_iter < leftover || leftover == 0) {
              std::cout << "Within leftover" << std::endl;
              rows_in_curr_col = curr_row_amt;
            }

            std::vector<AlbumArt*> removed_album_art;
            for (size_t to_shift_row_iter = 0; to_shift_row_iter < rows_in_curr_col; to_shift_row_iter++) {

              std::cout << "1st Art to be shifted (col " << to_shift_col_iter <<", row " << to_shift_row_iter << ")" << std::endl;
              AlbumArt* to_be_remv_art = (AlbumArt*)album_grid.get_child_at(to_shift_col_iter,to_shift_row_iter);
              removed_album_art.push_back(to_be_remv_art);
              art_shifted++;
            }
            this->album_grid.remove_column(to_shift_col_iter);
            std::cout << "Removed col " << to_shift_col_iter << std::endl;

            for (size_t iter = 0; iter < removed_album_art.size(); iter++) {
              AlbumArt* art_to_be_added_back = removed_album_art[iter];
              std::cout << "1st Shifted to (col " << shift_col_iter <<", row " << shift_row_iter << ")" << std::endl;
              this->album_grid.attach(*art_to_be_added_back, shift_col_iter, shift_row_iter, 1, 1);

              if (shift_col_iter == (item_per_row - 1)) {
                shift_row_iter++;
                shift_col_iter = 0;
              }
              else
                shift_col_iter++;
            }

            to_shift_col_iter--;
          }
          this->curr_items_per_row = item_per_row;
          this->curr_row_amt = req_rows;

        }
      else if (item_per_row > curr_items_per_row)
        {
          std::cout << "Add back started " << std::endl;
          int req_rows = util::round_up((double)full_album_art.size()/item_per_row);
          int leftover = full_album_art.size() % curr_items_per_row;
          int expected_leftover = full_album_art.size() % item_per_row;

          int to_shift_row_iter = this->curr_row_amt - 1;
          int to_shift_col_iter = this->curr_items_per_row - 1;

          int shift_col_iter = curr_items_per_row;
          int shift_row_iter = 0;

          std::cout << "Add back curr_row_amt " << curr_row_amt << std::endl;
          std::cout << "Add back req_rows " << req_rows << std::endl;
          std::cout << "Add back curr_items_per_row " << curr_items_per_row << std::endl;
          std::cout << "Add back leftover " << leftover << std::endl;

          int total_to_be_shifted = full_album_art.size() - (req_rows * curr_items_per_row);


          if (expected_leftover < curr_items_per_row)
            total_to_be_shifted += (curr_items_per_row - expected_leftover);

          /*
          if (expected_leftover > curr_items_per_row && expected_leftover != 0) {
            if (leftover != 0) {
          total_to_be_shifted = ((curr_row_amt - req_rows + 1) *
                                 curr_items_per_row) + (curr_items_per_row -
                                     leftover) - expected_leftover;
            }
            else {
            total_to_be_shifted = ((curr_row_amt - req_rows + 1) *
                                   curr_items_per_row) - expected_leftover;
            }
          }
          */
          std::cout << "Add back total to be shifted " << total_to_be_shifted << std::endl;

          if (leftover > 0)
            to_shift_col_iter = leftover - 1;

          if (total_to_be_shifted > 0) {
            int art_shifted = 1;
            struct ShiftAlbumArt {
              AlbumArt* album_art;
              int shift_col;
              int shift_row;
            };
            std::vector<ShiftAlbumArt> removed_album_art;
            while (art_shifted <= total_to_be_shifted) {
              std::cout << "Test add back Art to be shifted (col " << to_shift_col_iter <<", row " << to_shift_row_iter << ")" << std::endl;
              std::cout << "Test Art shifted to (col " << shift_col_iter <<", row " << shift_row_iter << ")" << std::endl;

              ShiftAlbumArt art_to_be_shifted;
              art_to_be_shifted.album_art = (AlbumArt*)album_grid.get_child_at(to_shift_col_iter,to_shift_row_iter);
              art_to_be_shifted.shift_col = shift_col_iter;
              art_to_be_shifted.shift_row = shift_row_iter;
              removed_album_art.push_back(art_to_be_shifted);

              this->album_grid.remove(*art_to_be_shifted.album_art);

              if (to_shift_col_iter == 0) {
                to_shift_col_iter = curr_items_per_row - 1;
                this->album_grid.remove_row(to_shift_row_iter);
                to_shift_row_iter--;
              }
              else
                to_shift_col_iter--;

              if (shift_col_iter < item_per_row - 1) {
                shift_col_iter++;
              }
              else {
                shift_row_iter++;
                shift_col_iter = curr_items_per_row;
              }

              art_shifted++;
            }

            for (size_t iter = 0; iter < removed_album_art.size(); iter++) {
              std::cout << "Add back removed album art size " <<
                removed_album_art.size() << std::endl;
              AlbumArt* album_art_to_shift = removed_album_art[iter].album_art;
              int col_to_shift_to = removed_album_art[iter].shift_col;
              int row_to_shift_to = removed_album_art[iter].shift_row;

              this->album_grid.attach(*album_art_to_shift, col_to_shift_to, row_to_shift_to, 1, 1);
            }
          }

          std::cout << "Add back ended" << std::endl;
          this->curr_items_per_row = item_per_row;
          this->curr_row_amt = req_rows;
        }
    }
  }
}
