#include <GUI/playlist-manager.h>

PlaylistManager::PlaylistManager()
{
  PlaylistManager::init_connections();  
}

PlaylistManager::PlaylistManager(Gtk::Stack &stack)
{
  this->set_stack(stack);
  PlaylistManager::init_connections();
}

PlaylistManager::~PlaylistManager(){}

void PlaylistManager::set_stack(Gtk::Stack &stack)
{
  playlist_stack = &stack;
  Gtk::StackSidebar::set_stack(stack);
}

void PlaylistManager::init_connections()
{
  this->signal_set_focus_child().connect(sigc::mem_fun(this, &PlaylistManager::on_playlist_switched));
}

void PlaylistManager::add_playlist(Playlist& playlist, const Glib::ustring& name, const Glib::ustring& title)
{
  playlists.push_back(&playlist);
  if (playlists.size() > 1) {
    for (size_t iter = 1; iter < playlists.size(); iter++) {
      playlists[iter]->disable();
    }
  }
  this->playlist_stack->add(playlist, name, title);
}

void PlaylistManager::on_playlist_switched(Gtk::Widget *widget)
{
  std::cout << "On playlist switched" << std::endl;
  Playlist *active_playlist = (Playlist*)playlist_stack->get_visible_child();
  for (size_t iter = 0; iter < playlists.size(); iter++)
    playlists[iter]->disable();
  active_playlist->enable();
}
