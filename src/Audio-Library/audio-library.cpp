#include <gtkmm.h>
#include <GUI/gui.h>
#include <iostream>
#include <sqlite3.h>
#include <Utilities/util.h>
#include <Audio-Info/audioinfo.h>
#include <Audio-Library/audio-library.h>

AudioLibrary::AudioLibrary(){}
AudioLibrary::~AudioLibrary(){}

sqlite3 *library_db;
bool db_opened;

std::vector<char*> file_locations;
std::vector<std::string> subdir_locations;
std::vector<char*> omitted_locations;

  
int file_count;
int subdir_count;

void AudioLibrary::scan_dir(const char *dir_location){

  subdir_locations.push_back(dir_location);

  for (size_t subdir_iter = 0; subdir_iter < subdir_locations.size(); subdir_iter++){
    std::string file_location = subdir_locations[subdir_iter];
    if (file_location.substr(file_location.length() - 1) != "/")
      file_location += "/";

    GError *error = NULL;
    GError *subdir_error = NULL;

    const char *file;
    GDir *dir = g_dir_open(subdir_locations[subdir_iter].c_str(), 0, &error);

    while ((file = g_dir_read_name(dir))){
      try {
	GError *subdir_error = NULL;

	string subdir_location = file_location + file;
	g_dir_open(util::to_char(subdir_location), 0, &subdir_error);
	if (subdir_error == NULL) {
	  subdir_count++;
	  subdir_locations.push_back(util::to_char(subdir_location));
	}
	if (subdir_error != NULL){
	  throw 0;
	}
      }
      catch (int exception)
	{
	  file_count++;
	  file_location += file;
	}
    }
  }
  std::cout << "No. of Files : " << file_count << std::endl;
  std::cout << "No. of Subdirectories : " << subdir_count << std::endl;
}
