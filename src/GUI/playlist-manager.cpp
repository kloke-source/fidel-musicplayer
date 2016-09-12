#include <GUI/playlist-manager.h>

PlaylistManager::PlaylistManager(){}

PlaylistManager::PlaylistManager(Gtk::Stack &stack)
{
  this->set_stack(stack);
}

PlaylistManager::~PlaylistManager(){}

void PlaylistManager::set_stack(Gtk::Stack &stack)
{
  playlist_stack = &stack;
  Gtk::StackSidebar::set_stack(stack);
}

void PlaylistManager::add_playlist(Playlist& playlist, const Glib::ustring& name, const Glib::ustring& title)
{
  playlists.push_back(&playlist);
  for (size_t iter = 0; iter < playlists.size(); iter++) {
    playlists[iter]->signal_playing().connect([this, iter](){
	int active_playlist_pos = iter;
	for (size_t playlist_iter = 0; playlist_iter < playlists.size(); playlist_iter++)
	  playlists[playlist_iter]->disable();
	playlists[active_playlist_pos]->enable();
      });
  }  
  this->playlist_stack->add(playlist, name, title);
}
