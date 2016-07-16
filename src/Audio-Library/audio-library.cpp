#include <algorithm>
#include <gtkmm.h>
#include <GUI/gui.h>
#include <iostream>
#include <dirent.h>
#include <fstream>
#include <Utilities/btree.h>
#include <string>
#include <sqlite3.h>
#include <Utilities/util.h>
#include <taglib/taglib.h>
#include <Audio-Info/audioinfo.h>
#include <Audio-Library/audio-library.h>
#include <ctime>
#include <future>
#include <thread>
using namespace std;

AudioLibrary::AudioLibrary(){}
AudioLibrary::~AudioLibrary(){}

sqlite3 *library_db;
bool db_opened;

GDir *dir=NULL;
GError *error=NULL;

vector<char*> file_locations;
vector<char*> subdir_locations;
vector<char*> omitted_locations;

int file_count;
int subdir_count;

void AudioLibrary::scan_dir(const char *dir_location)
{
  AudioLibrary::scan_dir_backend(dir_location);
  std::cout << "No. of Files : " << file_count << std::endl;
  std::cout << "No. of Subdirectories : " << subdir_count << std::endl;
}

//AudioLibrary::AudioLibrary::scan_dir recursion variables
int subdir_iter=0;
int subdir_iter_amount=0;
bool subdir_iter_init = false;
//end

void AudioLibrary::scan_dir_backend(const char *dir_location){
  string file_location = dir_location;
  if (file_location.substr(file_location.length() - 1) != "/"){
    file_location += "/";
  }
  const char *file;
  dir = g_dir_open(dir_location, 0, &error);
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
  if (subdir_iter_init == true)
  {
    subdir_iter++;
  }
  if (subdir_locations.size() != 0){
    subdir_iter_amount = subdir_locations.size();
  }
  if (subdir_iter < subdir_iter_amount){
    subdir_iter_init = true;
    AudioLibrary::scan_dir_backend(subdir_locations[subdir_iter]);
  }
}
