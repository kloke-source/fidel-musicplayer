#include <gtkmm.h>
#include <GUI/gui.h>
#include <iostream>
#include <sqlite3.h>
#include <Utilities/util.h>
#include <Audio-Info/audioinfo.h>
#include <Audio-Library/audio-library.h>
#include <Utilities/threadpool.h>
#include <mutex>
#include <thread>
//#define library_db ":memory:"
// initialization variables
std::string default_music_folder;
std::string default_db_location;
bool initialized = false;

// database variables
sqlite3 *library_db;
bool db_opened = false;

// --> table fields
std::vector<std::string> library_fields;

// validating variables
btree<std::string> valid_file_formats;

// directory indexing variables
int file_count;
int subdir_count;

std::vector<std::string> file_locations;
std::vector<std::string> subdir_locations;
std::vector<char*> omitted_locations;

ThreadPool threadpool;
void AudioLibrary::initialize()
{
  if (initialized == false) {
    initialized = true;

    valid_file_formats.insert("mp3");
    valid_file_formats.insert("flac");
    valid_file_formats.insert("wav");
    valid_file_formats.insert("ogg");
    valid_file_formats.insert("m4a");
    valid_file_formats.insert("m4p");

    library_fields.push_back("file_location");    
    library_fields.push_back("Name");
    library_fields.push_back("Artist");
    library_fields.push_back("Album");
    library_fields.push_back("Time");
    library_fields.push_back("duration_seconds");
    
    default_music_folder = util::get_home_dir() + "/Music";
    util::create_folder(util::get_home_dir() + "/.fidel/Databases");
    default_db_location = util::get_home_dir() + "/.fidel/Databases/library.db";
    AudioLibrary::init_db();
  }  
}

int AudioLibrary::generic_db_callback(void *data, int total_col_num, char **value, char **fields)
{
  for(int iter = 0; iter < total_col_num; iter++){
    printf("%s = %s\n", fields[iter], value[iter] ? value[iter] : "NULL");
  }
  printf("\n");
  return 0;
}

/** 
 * \brief Essentially initializes the sqlite database so that it can be written to
 * \details This function initializes the database as an in-memory database so that 
 * database related operations take place much quicker
 */
void AudioLibrary::init_db()
{
  char *error_msg = 0;
  int  ret_code;
  std::string sql_stmt;

  /* Open database */
  ret_code = sqlite3_open("", &library_db); /**< By leaving the first parameter sqlite creates a temporary database which has comparable speeds to a full fledged in-memory database */
  if( ret_code ){
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(library_db));
  }else{
    fprintf(stdout, "Opened database successfully\n");
  }

  /* Create SQL statement */
  sql_stmt = "CREATE TABLE library (" \
    "ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE," \
    "file_location TEXT," \
    "Name TEXT," \
    "Artist TEXT," \
    "Album TEXT," \
    "Time TEXT," \
    "duration_seconds NUMERIC);";				     

  /* Execute SQL statement */
  ret_code = sqlite3_exec(library_db, util::to_char(sql_stmt), generic_db_callback, 0, &error_msg);
  if( ret_code != SQLITE_OK ){
    if (util::has_text(error_msg, "already exists") == false) // omits the already exists error msg
      fprintf(stderr, "SQL error: %s\n", error_msg);
    sqlite3_free(error_msg);
  }else{
    fprintf(stdout, "Table created successfully\n");
  }
}

bool AudioLibrary::check_file_format(std::string input_file)
{
  return valid_file_formats.check(input_file.substr(input_file.find_last_of(".") + 1));
}

void AudioLibrary::db_ins_row(std::string ins_stmt)
{
  sqlite3_stmt *sql_stmt;

  char *query = util::to_char(ins_stmt);
  {
    if(sqlite3_prepare(library_db, query, -1, &sql_stmt, 0) == SQLITE_OK)
      {
        sqlite3_step(sql_stmt);
        sqlite3_finalize(sql_stmt);
      }
  }
}

void AudioLibrary::scan()
{
  AudioLibrary::initialize();
  AudioLibrary::scan_dir(default_music_folder.c_str());
}

std::mutex indexing_mutex;
void AudioLibrary::scan_dir(const char *dir_location){

  subdir_locations.push_back(dir_location);

  for (size_t subdir_iter = 0; subdir_iter < subdir_locations.size(); subdir_iter++){
    std::string file_location = subdir_locations[subdir_iter];
    if (file_location.substr(file_location.length() - 1) != "/")
      file_location += "/";

    GError *error = NULL;
    GError *subdir_error = NULL;

    std::stringstream test;
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
	  std::string temp = file_location;
	  file_location += file;
	  if (AudioLibrary::check_file_format(file_location) == true)
	    {
	      file_count++;
	      file_locations.push_back(file_location);

	      audioinfo::init(util::to_char(file_location));
	      std::vector<std::string> library_field_values;
	      library_field_values.push_back(file_location);
	      library_field_values.push_back(audioinfo::get_info("song_name"));
	      library_field_values.push_back(audioinfo::get_info("artist"));
	      library_field_values.push_back(audioinfo::get_info("album"));
	      library_field_values.push_back(audioinfo::get_info("time"));
	      library_field_values.push_back(audioinfo::get_info("duration_seconds"));
	      std::string ins_stmt = util::gen_ins_stmt("library", library_fields, library_field_values);
	      std::cout << "Inserted " << file_location << std::endl;	     
	      //threadpool.enqueue([ins_stmt] {
	      //std::unique_lock<std::mutex> locker(indexing_mutex);
	      AudioLibrary::db_ins_row(ins_stmt);
	      //locker.unlock();
	      //});
	    }
	  file_location = temp;
	}
    }
  }
  std::cout << "No. of Files : " << file_count << std::endl;
  std::cout << "No. of Subdirectories : " << subdir_count << std::endl;
  //sqlite3 *library_db = library_db;
  AudioLibrary::flush_to_db(library_db, default_db_location.c_str());
}

int AudioLibrary::flush_to_db(sqlite3 *in_memory, const char *file_name) {
  int ret_code;
  sqlite3 *destination_file;           // Database connection opened on file_name
  sqlite3_backup *backup_obj;  // Backup object used to copy data
  sqlite3 *destination;             // Database to copy to (destination_file or in_memory)
  sqlite3 *source;           // Database to copy from (destination_file or in_memory)

  ret_code = sqlite3_open(file_name, &destination_file);
  if( ret_code==SQLITE_OK ){

    source = in_memory;
    destination   = destination_file;

    backup_obj = sqlite3_backup_init(destination, "main", source, "main");
    if( backup_obj ){
      (void)sqlite3_backup_step(backup_obj, -1);
      (void)sqlite3_backup_finish(backup_obj);
    }
    ret_code = sqlite3_errcode(destination);
  }

  /* Close the database connection opened on database file file_name
  ** and return the result of this function. */
  db_opened = true;
  (void)sqlite3_close(destination_file);
  return ret_code;
}
