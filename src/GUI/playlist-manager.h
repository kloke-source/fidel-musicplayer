#ifndef PLAYLIST_MANAGER_HH
#define PLAYLIST_MANAGER_HH

#include <vector>
#include <gtkmm.h>
#include <iostream>
#include <GUI/playlist.h>

class Playlist;

class PlaylistManager : public Gtk::StackSidebar {
 public:
  PlaylistManager();
  PlaylistManager(Gtk::Stack &stack);
  ~PlaylistManager();

  void set_stack(Gtk::Stack &stack);
  void add_playlist(Playlist& playlist, const Glib::ustring& name, const Glib::ustring& title);
 private:
  // variables
  std::vector<Playlist*> playlists;
  Gtk::Stack *playlist_stack;
};
#endif
