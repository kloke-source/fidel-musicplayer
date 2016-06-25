#include <iostream>
#include <gtkmm.h>
#include <GUI/gui.h>
#include <GUI/themer.h>

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
extern Box *sidebar_albumart;
extern Box *spectrum_view_layout;

extern Grid *sidebar_audioinfo_layout;
extern Scale *playback_slider;

extern Button *previous_button;
extern Button *play_button;
extern Button *next_button;
extern Button *sidebar_hider;

extern std::vector<Button*> all_buttons;

/* stylesheets */
std::stringstream notebook_stylesheet;
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

  //std::cout << notebook_stylesheet.str() << std::endl;
  Glib::RefPtr<Gtk::StyleContext> stylecontext = view_switcher->get_style_context();
  Glib::RefPtr<Gtk::CssProvider> cssprov = Gtk::CssProvider::create();
  cssprov->load_from_data(notebook_stylesheet.str());
  stylecontext->add_provider(cssprov, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  stylecontext->context_save();

    for (size_t button_iter = 0; button_iter < all_buttons.size(); button_iter++) {
      all_buttons[button_iter]->set_relief(Gtk::RELIEF_NONE);
      all_buttons[button_iter]->show();
    }
}
