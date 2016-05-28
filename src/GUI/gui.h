#ifndef GUI
#define GUI
#include <vector>
#include <gtkmm.h>
#include <iostream>
#include <GUI/singleton.h>

typedef Glib::RefPtr<Gtk::Builder> Builder;
typedef Glib::RefPtr<Gtk::FileFilter> FileFilter;
typedef Gtk::ApplicationWindow ApplicationWindow;
typedef Gtk::Toolbar Toolbar;
typedef Gtk::ImageMenuItem ImageMenuItem;
typedef Gtk::Image Image;
typedef Gtk::Notebook Notebook;
typedef Gtk::Entry Entry;
typedef Gtk::Label Label;
typedef Gtk::Box Box;
typedef Gtk::Grid Grid;
typedef Gtk::Scale Scale;
typedef Gtk::Button Button;

class gui{
public:
	gui();
	virtual ~gui();
	void initialize(int argc, char **argv);
	void init_builder();
	/*
	void add_list_store_row(vector<Glib::ustring> row_data);
	void initializeCloseEventHandler();
	void set_paused_icon();
	void set_playing_icon();
	void update_pb_slider_pos(double *time);
	void set_pb_slider_endtime(int endtime);
	void set_sidebar_data(Gtk::Image *album_art, vector<Glib::ustring> song_data);
	void delete_sidebar_data();
	class Playlist_Columns : public Gtk::TreeModel::ColumnRecord
  {
  public:

    Playlist_Columns()
    {add(col_name); add(col_artist); add(col_album); add(col_time); add(col_color);  add (col_file_location);}

    Gtk::TreeModelColumn<Glib::ustring> col_name;
    Gtk::TreeModelColumn<Glib::ustring> col_artist;
    Gtk::TreeModelColumn<Glib::ustring> col_album;
    Gtk::TreeModelColumn<Glib::ustring> col_time;
		Gtk::TreeModelColumn<Glib::ustring> col_color;
		Gtk::TreeModelColumn<Glib::ustring> col_file_location;
  };

	*/
private:
	void init_connections();
	void init_widget_vectors();
	void init_icons();
	void init_spectrum();
	void set_styles();
	bool on_window_closed(GdkEventAny* event);
	void get_widgets();
	void on_file_open_triggered();
	void testhandler(guint band, gfloat magnitude, gfloat phase_shift);
	/*
	void init_playlist();
	void init_album_view();
	void populate_playlist();
	virtual bool keyboard_shortcuts(GdkEventKey* event);
	void split_view_resize_handler(Gtk::Allocation &allocation);
	void playlist_resize_handler(Gtk::Allocation &allocation);
	void on_search_entry_kp_event(const Glib::ustring& text,int* character_num);
	void search_playlist(Glib::ustring search_term);
	void on_double_click_handler(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn *column);
	void on_view_switched(Gtk::Widget *page, guint page_number);
	void on_sidebar_hider_clicked();
	void on_play_button_clicked();
	void pb_slider_val_changed();
	void test();
	void kill();
	*/
};

typedef Singleton<gui> fidel_ui;
#endif
