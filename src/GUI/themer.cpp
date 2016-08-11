#include <iostream>
#include <gtkmm.h>
#include <GUI/gui.h>
#include <GUI/themer.h>
#include <Utilities/util.h>

bool themer_initialized = false;

themer::themer(){}

themer::~themer(){}

extern GResource *fidel_resources;
extern Builder builder;
extern ApplicationWindow *window;

extern Toolbar *toolbar;
extern ImageMenuItem *open_action;
extern Notebook *view_switcher;
extern Entry *playlist_search_entry;

extern Image *previous_icon, *play_icon, *pause_icon, *next_icon;

extern Label *split_view_label;
extern Label *playlist_view_label;
extern Label *library_view_label;
extern Label *spectrum_view_label;
extern Label *idle_status_label;
extern Label *playback_timer;
extern Label *playback_endtime;
extern Label *sidebar_name_label;
extern Label *sidebar_artist_label;
extern Label *sidebar_album_label;
extern Label *sidebar_song_name;
extern Label *sidebar_song_artist;
extern Label *sidebar_song_album;

extern Box *split_view_layout;
extern Box *split_view_spectrum;
extern Box *split_view_playlist;
extern Box *library_view_frame;
extern Box *playback_frame;
extern Box *playlist_view;
extern Box *playback_slider_frame;
extern Box *sidebar_layout;
extern Box *sidebar_album_art_container;
extern Box *spectrum_view_layout;
extern Box *mini_spectrum_container;

extern Grid *sidebar_audioinfo_layout;
extern Scale *playback_slider;

extern Button *previous_button;
extern Button *play_button;
extern Button *next_button;
extern Button *sidebar_hider;

/* widget vector enums */

enum{
  NOTEBOOKS,
  ENTRIES,
  IMAGES,
  LABELS,
  BOXES,
  GRIDS,
  SCALES,
  BUTTONS
};

/* type definitions */
typedef Glib::RefPtr<Gtk::StyleContext> StyleContext;

/* style context vector */
std::vector<std::vector<StyleContext> > all_style_ctx_vect;
std::vector<StyleContext> notebook_style_ctx_vect;
std::vector<StyleContext> entry_style_ctx_vect;
std::vector<StyleContext> image_style_ctx_vect;
std::vector<StyleContext> label_style_ctx_vect;
std::vector<StyleContext> box_style_ctx_vect;
std::vector<StyleContext> grid_style_ctx_vect;
std::vector<StyleContext> scale_style_ctx_vect;
std::vector<StyleContext> button_style_ctx_vect;

/* widget vectors */
std::vector<Notebook*> notebook_vect;
std::vector<Entry*> entry_vect;
std::vector<Image*> image_vect;
std::vector<Label*> label_vect;
std::vector<Box*> box_vect;
std::vector<Grid*> grid_vect;
std::vector<Scale*> scale_vect;
std::vector<Button*> button_vect;

/* stylesheet enums */
enum{
  NOTEBOOK_STYLESHEET,
  SLIDER_STYLESHEET
};

/* stylesheets */
std::stringstream notebook_stylesheet;
std::stringstream slider_stylesheet;

std::vector<std::string> stylesheet_vect; // stylesheet vector
/* notebook colors */
std::string selected_tab_bg_color = "#e8e8e8";
std::string selected_tab_font_bg_color = "#2d2d2d";
std::string selected_tab_top_border_bg_color = "#cccccc";
std::string selected_tab_bottom_border_bg_color = "transparent";
std::string notebook_unselected_bottom_border_bg_color = "transparent";
std::string notebook_tab_bg_color = "#e0e0e0";
std::string notebook_tab_hover_bg_color = "#f0f0f0";
std::string notebook_tab_hover_bottom_border_bg_color = "#a1a1a1";
std::string notebook_bottom_border_color = "#cccccc";

/* notebook settings */
int notebook_bottom_border_width = 1; //px

void themer::set_styles()
{
  if (themer_initialized == false)
  themer::init_stylesheets();
  themer::init_vectors();

  themer_initialized = true;

  for (size_t iter = 0; iter < stylesheet_vect.size(); iter++) {
    Glib::RefPtr<Gtk::CssProvider> cssprov = Gtk::CssProvider::create();
    cssprov->load_from_data(stylesheet_vect[iter]);
    switch (iter) {
      case NOTEBOOK_STYLESHEET:
      for (size_t notebook_iter = 0; notebook_iter < all_style_ctx_vect[NOTEBOOKS].size(); notebook_iter++) {
        all_style_ctx_vect[NOTEBOOKS][notebook_iter]->add_provider(cssprov, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        all_style_ctx_vect[NOTEBOOKS][notebook_iter]->context_save();
      }
      break;
      case SLIDER_STYLESHEET:
      for (size_t slider_iter = 0; slider_iter < all_style_ctx_vect[SCALES].size(); slider_iter++) {
        all_style_ctx_vect[SCALES][slider_iter]->add_provider(cssprov, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        all_style_ctx_vect[SCALES][slider_iter]->context_save();
      }
      break;
    }
  }

  /* Set button reliefs (Makes them flat) */
  for (size_t button_iter = 0; button_iter < button_vect.size(); button_iter++) {
    button_vect[button_iter]->set_relief(Gtk::RELIEF_NONE);
    button_vect[button_iter]->show();
  }
}

void themer::init_vectors()
{
  if (themer_initialized == true)
  {
    notebook_vect.clear();
    label_vect.clear();
    box_vect.clear();
    grid_vect.clear();
    scale_vect.clear();
    button_vect.clear();

    all_style_ctx_vect.clear();
  }
  notebook_vect.push_back(view_switcher);

  label_vect.push_back(split_view_label);
  label_vect.push_back(playlist_view_label);
  label_vect.push_back(library_view_label);
  label_vect.push_back(spectrum_view_label);
  label_vect.push_back(idle_status_label);
  label_vect.push_back(playback_timer);
  label_vect.push_back(playback_endtime);
  label_vect.push_back(sidebar_name_label);
  label_vect.push_back(sidebar_artist_label);
  label_vect.push_back(sidebar_album_label);
  label_vect.push_back(sidebar_song_name);
  label_vect.push_back(sidebar_song_artist);
  label_vect.push_back(sidebar_song_album);

  box_vect.push_back(split_view_layout);
  box_vect.push_back(split_view_spectrum);
  box_vect.push_back(split_view_playlist);
  box_vect.push_back(library_view_frame);
  box_vect.push_back(playback_frame);
  box_vect.push_back(playlist_view);
  box_vect.push_back(playback_slider_frame);
  box_vect.push_back(sidebar_layout);
  box_vect.push_back(sidebar_album_art_container);
  box_vect.push_back(spectrum_view_layout);
  box_vect.push_back(mini_spectrum_container);
  
  grid_vect.push_back(sidebar_audioinfo_layout);

  scale_vect.push_back(playback_slider);

  button_vect.push_back(previous_button);
  button_vect.push_back(play_button);
  button_vect.push_back(next_button);
  button_vect.push_back(sidebar_hider);

  /* Initialize style sheet vect */
  if (themer_initialized == false){
    stylesheet_vect.push_back(notebook_stylesheet.str());
    stylesheet_vect.push_back(slider_stylesheet.str());
  }

  /* Initialize style context vectors */
  for (size_t iter = 0; iter < notebook_vect.size(); iter++) {
    notebook_style_ctx_vect.push_back(notebook_vect[iter]->get_style_context());
  }
  for (size_t iter = 0; iter < entry_vect.size(); iter++) {
    entry_style_ctx_vect.push_back(entry_vect[iter]->get_style_context());
  }
  for (size_t iter = 0; iter < image_vect.size(); iter++) {
    image_style_ctx_vect.push_back(image_vect[iter]->get_style_context());
  }
  for (size_t iter = 0; iter < label_vect.size(); iter++) {
    label_style_ctx_vect.push_back(label_vect[iter]->get_style_context());
  }
  for (size_t iter = 0; iter < box_vect.size(); iter++) {
    box_style_ctx_vect.push_back(box_vect[iter]->get_style_context());
  }
  for (size_t iter = 0; iter < grid_vect.size(); iter++) {
    grid_style_ctx_vect.push_back(grid_vect[iter]->get_style_context());
  }
  for (size_t iter = 0; iter < scale_vect.size(); iter++) {
    scale_style_ctx_vect.push_back(scale_vect[iter]->get_style_context());
  }
  for (size_t iter = 0; iter < button_vect.size(); iter++) {
    button_style_ctx_vect.push_back(button_vect[iter]->get_style_context());
  }

  /* Initialize full style context vector */
  all_style_ctx_vect.push_back(notebook_style_ctx_vect);
  all_style_ctx_vect.push_back(entry_style_ctx_vect);
  all_style_ctx_vect.push_back(image_style_ctx_vect);
  all_style_ctx_vect.push_back(label_style_ctx_vect);
  all_style_ctx_vect.push_back(box_style_ctx_vect);
  all_style_ctx_vect.push_back(grid_style_ctx_vect);
  all_style_ctx_vect.push_back(scale_style_ctx_vect);
  all_style_ctx_vect.push_back(button_style_ctx_vect);
}

void themer::init_stylesheets()
{
  notebook_stylesheet << "\
  @define-color selected_tab_bg_color " << selected_tab_bg_color << ";\n\
  @define-color selected_tab_font_bg_color " << selected_tab_font_bg_color << ";\n\
  @define-color selected_tab_top_border_bg_color " << selected_tab_top_border_bg_color << ";\n\
  @define-color selected_tab_bottom_border_bg_color " << selected_tab_bottom_border_bg_color << ";\n\
  \n\
  @define-color notebook_unselected_bottom_border_bg_color " << notebook_unselected_bottom_border_bg_color << ";\n\
  \n\
  @define-color notebook_tab_bg_color " << notebook_tab_bg_color << ";\n\
  @define-color notebook_tab_hover_bg_color " << notebook_tab_hover_bg_color << ";\n\
  @define-color notebook_tab_hover_bottom_border_bg_color " << notebook_tab_hover_bottom_border_bg_color << ";\n\
  \n\
  @define-color notebook_bottom_border_color " << notebook_bottom_border_color << ";\n\
  \n\
  * { border-top-width: 0; } /* Removes top border from notebook */\n\
  \n\
  /* Applies  to the notebook as a whole but not the current selected tab*/\n\
  notebook > header {\n\
    padding: 0;\n\
    margin: 0;\n\
    border-bottom-width: " << notebook_bottom_border_width << "px; /*notebook bottom border width */\n\
    border-bottom-color: @notebook_bottom_border_color;\n\
    background-image: none;\n\
    background-color: @notebook_tab_bg_color;\n\
  }\n\
  \n\
  /*Applies to non-selected notebook tabs */\n\
  notebook > header tab {\n\
    padding: 0;\n\
    margin: 0;\n\
    border-color: @notebook_unselected_bottom_border_bg_color;\n\
    background-image: none;\n\
    box-shadow: none;}\n\
  \n\
  notebook > header.top tab {\n\
    padding: 6px 0 0;\n\
    border-style: solid;\n\
    border-width: 0;\n\
    border-bottom-width: 2px;\n\
    transition: border-bottom-color .3s ease-out; }\n\
  \n\
  /* Applies to selected notebook tab */\n\
  notebook > header tab:checked {\n\
    background-color: @selected_tab_bg_color;\n\
    border-top-width: 0px; /*Sets the width of the selected notebook tab's top border */\n\
    border-bottom-width: 1px; /*Sets the width of the selected notebook tab's bottom border */\n\
    border-top-color: @selected_tab_top_border_bg_color;\n\
    border-bottom-color: @selected_tab_bottom_border_bg_color;\n\
    outline: none; }\n\
  \n\
  notebook > header tab:checked label {\n\
    color: @selected_tab_font_bg_color; }\n\
  \n\
  notebook > header tab > box, notebook > header tab > label {\n\
    border-width: 2px;\n\
    border-style: solid;\n\
    border-color: transparent;\n\
    transition: border-color .3s ease-out; }\n\
  \n\
  /* gets rid of blue tab bottom border color that you typically see in the Adwaita theme */\n\
  notebook > header tab:checked:not(:first-child):not(:only-child) {\n\
    box-shadow: -1px 0 1px 0 rgba(0, 0, 0, 0.1); }\n\
  notebook > header tab:checked:not(:last-child):not(:only-child) {\n\
    box-shadow: 1px 0 1px 0 rgba(0, 0, 0, 0.1); }\n\
  \n\
  notebook > header.top tab > box, notebook > header.top tab > label {\n\
    padding: 0 15px 6px; }\n\
  notebook > header.top tab:hover {\n\
    outline: none; }\n\
  \n\
  /*Applies when hovering over non-selected notebook tabs */\n\
  notebook > header tab:hover {\n\
    border-width: .5px;\n\
    background-color: @notebook_tab_hover_bg_color;\n\
    border-bottom-color: @notebook_tab_hover_bottom_border_bg_color;\n\
    outline: none; }\n\
  ";

  slider_stylesheet << "\
  @define-color slider_trough_bg_color #a1a1a1;\n\
  @define-color slider_trough_border_color transparent;\n\
  @define-color slider_highlight_color #4d4d4d;\n\
  @define-color slider_handle_bg_color #cccccc;\n\
\n\
  scale{\n\
  min-height: 5px;\n\
}\n\
\n\
  scale trough{\n\
  background-color: @slider_trough_bg_color;\n\
  border-color: @slider_trough_border_color;\n\
  border-width: 0px;\n\
}\n\
\n\
    scale highlight {\n\
      border-width: 0px;\n\
      background-color: @slider_highlight_color;\n\
  }\n\
\n\
  scale slider {\n\
  border-radius: 100%;\n\
  border-width: 1px;\n\
  border-color: @slider_handle_bg_color;\n\
  box-shadow: none;\n\
}\n\
  ";
}
