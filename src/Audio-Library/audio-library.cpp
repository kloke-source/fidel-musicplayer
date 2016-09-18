#include <gtkmm.h>
#include <GUI/gui.h>
#include <iostream>
#include <sqlite3.h>
#include <Utilities/util.h>
#include <Audio-Info/audioinfo.h>
#include <Audio-Library/audio-library.h>
#include <mutex>
#include <thread>
//#define library_db ":memory:"
// initialization variables
std::string default_music_folder;
std::string default_db_location;
bool initialized = false;

// database variables
sqlite3 *library_db;
bool db_initialized = false;
bool db_opened = false;
bool db_loaded = false;
bool db_indexed = false;
bool indexed_once = false;

// --> table fields
std::vector<std::string> library_fields;
std::vector<std::string> library_info_fields;
std::vector<std::string> album_summ_fields;
std::vector<std::string> album_info_fields;
std::vector<std::string> artist_summ_fields;
std::vector<std::string> artist_info_fields;

struct AlbumSummary{
  std::string album_name;
  btree<std::string> songs_in_album;
  std::vector<std::string> file_locations;
  int total_songs_in_album;
};

struct AlbumInfo{
  std::string album_name;
  std::tuple<guint8*, gsize, bool> album_art;
};

struct ArtistSummary{
  std::string artist_name;
  btree<std::string> songs_by_artist;
  vector<std::string> file_locations;
  int total_songs_by_artist;
};

std::vector<AlbumSummary> full_album_summary;
std::vector<AlbumInfo> full_album_information;
btree<std::string> full_loaded_album_names;
std::vector<ArtistSummary> full_artist_summary;
btree<std::string> artists;
// validating variables
btree<std::string> valid_file_formats;

// counter variables
int total_files;
int total_artists;
int total_albums;
int subdir_count;

std::vector<std::string> file_locations;
std::vector<std::string> subdir_locations;
std::vector<char*> omitted_locations;

enum {
  LIB_ID,
  LIB_FILE_LOCATION,
  LIB_NAME,
  LIB_ARTIST,
  LIB_ALBUM,
  LIB_TIME,
};

enum {
  INFO_ALBUM_ID,
  INFO_ALBUM_NAME,
  INFO_ALBUM_ART
};

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

    library_info_fields.push_back("total_songs");
    library_info_fields.push_back("total_albums");
    library_info_fields.push_back("total_artists");

    album_summ_fields.push_back("album_name");
    album_summ_fields.push_back("songs_in_album");
    album_summ_fields.push_back("file_location");

    album_info_fields.push_back("album_name");
    album_info_fields.push_back("album_art");

    artist_summ_fields.push_back("artist_name");
    artist_summ_fields.push_back("songs_by_artist");
    artist_summ_fields.push_back("file_location");


    default_music_folder = util::get_home_dir() + "/Music";
    util::create_folder(util::get_home_dir() + "/.fidel/");
    util::create_folder(util::get_home_dir() + "/.fidel/Databases");
    default_db_location = util::get_home_dir() + "/.fidel/Databases/library.db";
  }
  if (db_indexed == true) {
    sqlite3_close_v2(library_db);
    library_db = NULL;
    db_initialized = false;
    db_indexed = false;
    file_locations.clear();
    subdir_locations.clear();
    full_album_summary.clear();
    full_album_information.clear();
    full_artist_summary.clear();
    artists.clear();
    total_files = 0;
    subdir_count = 0;
  }
  AudioLibrary::init_db();
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
  if (db_initialized == false) {
    db_initialized = true;
    char *error_msg = 0;
    int  ret_code;
    std::string sql_stmt;

    /* Open database */
    ret_code = sqlite3_open_v2("", &library_db, SQLITE_OPEN_READWRITE, NULL); /**< By leaving the first parameter sqlite creates a temporary database which has comparable speeds to a full fledged in-memory database */
    if( ret_code ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(library_db));
    }else{
      fprintf(stdout, "Opened database successfully\n");
    }

    /* Create tables */
    sql_stmt = "CREATE TABLE library (" \
      "ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE," \
      "file_location TEXT," \
      "Name TEXT," \
      "Artist TEXT," \
      "Album TEXT," \
      "Time TEXT," \
      "duration_seconds NUMERIC);" \
      "\n" \
      "CREATE TABLE library_information (" \
      "ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE," \
      "total_songs INTEGER," \
      "total_albums INTEGER," \
      "total_artists INTEGER);" \
      "\n" \
      "CREATE TABLE album_information (" \
      "ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE," \
      "album_name INTEGER," \
      "album_art BLOB);" \
      "\n" \
      "CREATE TABLE album_summary (" \
      "ID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE," \
      "album_name TEXT," \
      "songs_in_album TEXT," \
      "file_location TEXT);" \
      "\n" \
      "CREATE TABLE artists (" \
      "ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE," \
      "artist_name TEXT);" \
      "\n" \
      "CREATE TABLE artist_summary (" \
      "ID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE," \
      "artist_name TEXT," \
      "songs_by_artist TEXT," \
      "file_location TEXT);";


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
}

int AudioLibrary::load_db()
{
  AudioLibrary::initialize();
  if (db_loaded == false) {
    int ret_code;
    sqlite3 *in_memory = library_db;
    sqlite3 *source_file;           /* Database connection opened on default_db_location.c_str() */
    sqlite3_backup *backup_obj;  /* Backup object used to copy data */
    sqlite3 *destination;             /* Database to copy to (source_file or in_memory) */
    sqlite3 *source;           /* Database to copy from (source_file or in_memory) */

    /* Open the database file identified by default_db_location.c_str(). Exit early if this fails
    ** for any reason. */
    ret_code = sqlite3_open(default_db_location.c_str(), &source_file);
    if( ret_code==SQLITE_OK ){

      source = source_file;
      destination   = in_memory;

      backup_obj = sqlite3_backup_init(destination, "main", source, "main");
      if( backup_obj ){
	(void)sqlite3_backup_step(backup_obj, -1);
	(void)sqlite3_backup_finish(backup_obj);
      }
      ret_code = sqlite3_errcode(destination);
    }

    /* Close the database connection opened on database file default_db_location.c_str()
    ** and return the result of this function. */
    (void)sqlite3_close(source_file);
    AudioLibrary::load_album_info();
    db_loaded = true;
    return ret_code;
  }
}

void AudioLibrary::load_album_info()
{
  if (db_loaded == false) {
    AudioLibrary::initialize();
    sqlite3_stmt * statement;

    sqlite3_prepare_v2(library_db, "SELECT * FROM album_information;", -1, &statement, 0);

    while(sqlite3_column_text(statement, INFO_ALBUM_ID))
      {
	AlbumInfo album_info;

	album_info.album_name = std::string((char *)sqlite3_column_text(statement, INFO_ALBUM_NAME));
	full_loaded_album_names.insert(album_info.album_name);

	guint8 *raw_image_buffer = (guint8 *)sqlite3_column_blob(statement, INFO_ALBUM_ART);
        gsize raw_image_size = sqlite3_column_bytes(statement, INFO_ALBUM_ART);

	album_info.album_art = std::make_tuple(raw_image_buffer, raw_image_size, true);
	full_album_information.push_back(album_info);
	sqlite3_step(statement);
      }
    sqlite3_finalize(statement);
  }
}

std::tuple<guint8*, gsize, bool> AudioLibrary::get_album_art(std::string album_name)
{
  full_loaded_album_names.search(album_name);
  int album_pos = full_loaded_album_names.get_search_id();
  return full_album_information[album_pos].album_art;
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

void AudioLibrary::db_ins_blob(std::string blob_ins_stmt, guint8 *buffer, gsize buffer_size)
{
  AudioLibrary::initialize();
  sqlite3_stmt *statement;
  int ret_code = sqlite3_prepare_v2(library_db, blob_ins_stmt.c_str(), -1, &statement, NULL);

  if (ret_code != SQLITE_OK)
    cerr << "prepare failed: " << sqlite3_errmsg(library_db) << endl;
  else {
    ret_code = sqlite3_bind_blob(statement, 1, (char*)buffer, buffer_size, SQLITE_STATIC);
    if (ret_code != SQLITE_OK) {
      cerr << "bind failed: " << sqlite3_errmsg(library_db) << endl;
    } else {
      ret_code = sqlite3_step(statement);
      if (ret_code != SQLITE_DONE)
	cerr << "execution failed: " << sqlite3_errmsg(library_db) << endl;
    }
  }
  sqlite3_finalize(statement);
}

void AudioLibrary::write_lib_data(std::string file_location)
{
  audioinfo::init(util::to_char(file_location));

  std::vector<std::string> library_field_values;

  library_field_values.push_back(file_location);
  library_field_values.push_back(audioinfo::get_info(SONG_NAME));
  library_field_values.push_back(audioinfo::get_info(ARTIST));
  library_field_values.push_back(audioinfo::get_info(ALBUM));
  library_field_values.push_back(audioinfo::get_info(TIME));
  library_field_values.push_back(audioinfo::get_info(DURATION_SECONDS));

  std::string ins_stmt = util::gen_ins_stmt("library", library_fields, library_field_values);
  std::cout << "Inserted " << file_location << std::endl;
  AudioLibrary::db_ins_row(ins_stmt);
}

void AudioLibrary::write_lib_info()
{
  std::vector<std::string> library_info_values;
  library_info_values.push_back(util::to_string(total_files));
  library_info_values.push_back(util::to_string(total_albums));
  library_info_values.push_back(util::to_string(total_artists));
  std::string ins_stmt = util::gen_ins_stmt("library_information", library_info_fields, library_info_values);
  AudioLibrary::db_ins_row(ins_stmt);
}

void AudioLibrary::add_album_summ(std::string file_location)
{
  audioinfo::init(util::to_char(file_location));

  string album_name = audioinfo::get_info("album");
  string song_name = audioinfo::get_info("song_name");

  bool album_exists = false;
  if (full_album_summary.size() == 0){
    AlbumSummary album_summ;
    album_summ.album_name = album_name;
    album_summ.songs_in_album.insert(song_name);
    album_summ.file_locations.push_back(file_location);
    album_summ.total_songs_in_album = 1;
    full_album_summary.push_back(album_summ);
  }
  else {
    for (size_t iter = 0; iter < full_album_summary.size(); iter++){
      if (full_album_summary[iter].album_name == album_name)
	{
	  album_exists = true;
	  if (full_album_summary[iter].songs_in_album.check(song_name) == false)
	    {
	      full_album_summary[iter].songs_in_album.insert(song_name);
	      full_album_summary[iter].file_locations.push_back(file_location);
	      full_album_summary[iter].total_songs_in_album++;
	      break;
	    }
	}
    }
    if (album_exists == false) {
      AlbumSummary album_summ;
      album_summ.album_name = album_name;
      album_summ.songs_in_album.insert(song_name);
      album_summ.file_locations.push_back(file_location);
      album_summ.total_songs_in_album = 1;
      full_album_summary.push_back(album_summ);
    }
  }
}

void AudioLibrary::write_album_summ()
{
  std::vector<std::vector<std::string>> full_album_summ_data;

  for (size_t album_iter = 0; album_iter < full_album_summary.size(); album_iter++){
    std::string album_name = full_album_summary[album_iter].album_name;
    std::vector<std::string> songs_in_album = full_album_summary[album_iter].songs_in_album.inorder();

    for (size_t songs_iter = 0; songs_iter < songs_in_album.size(); songs_iter++){
      std::vector<std::string> album_summ_values;
      std::string song_name = songs_in_album[songs_iter];
      full_album_summary[album_iter].songs_in_album.search(song_name);
      int file_loc_pos = full_album_summary[album_iter].songs_in_album.get_search_id();
      std::string file_location = full_album_summary[album_iter].file_locations[file_loc_pos];
      album_summ_values.push_back(album_name);
      album_summ_values.push_back(song_name);
      album_summ_values.push_back(file_location);
      full_album_summ_data.push_back(album_summ_values);
      std::string ins_stmt = util::gen_ins_stmt("album_summary", album_summ_fields, album_summ_values);
      AudioLibrary::db_ins_row(ins_stmt);
    }
  }
}

void AudioLibrary::write_album_info(std::string file_location)
{
  audioinfo::init(util::to_char(file_location));
  std::string album_name = audioinfo::get_info(ALBUM);

  bool album_found = false;
  for (size_t iter = 0; iter < full_album_information.size(); iter++) {
    if (full_album_information[iter].album_name == album_name)
      {
	album_found = true;
	break;
      }
  }
  if (album_found == false)
    {
      total_albums++;
      AlbumInfo album_info;
      std::vector<std::string> album_info_values;

      album_info.album_name = album_name;
      album_info.album_art = audioinfo::extract_album_art(file_location);
      full_album_information.push_back(album_info);

      album_info_values.push_back(album_name);
      if (std::get<2>(album_info.album_art) == true)
	{
	  album_info_values.push_back("?");

	  std::stringstream blob_ins_stmt;
	  blob_ins_stmt << "INSERT INTO album_information (album_name, album_art) VALUES('" << album_name  << "', ?);";
	  AudioLibrary::db_ins_blob(blob_ins_stmt.str(), std::get<0>(album_info.album_art), std::get<1>(album_info.album_art));
	}
      else {
	album_info_values.push_back("No Album Art");
	std::string ins_stmt = util::gen_ins_stmt("album_information", album_info_fields, album_info_values);
	AudioLibrary::db_ins_row(ins_stmt);
      }
    }
}

void AudioLibrary::add_artist_summ(std::string file_location)
{
  audioinfo::init(util::to_char(file_location));

  string artist_name = audioinfo::get_info("album");
  string song_name = audioinfo::get_info("song_name");

  bool artist_exists = false;
  if (full_artist_summary.size() == 0){
    ArtistSummary artist_summ;
    artist_summ.artist_name = artist_name;
    artist_summ.songs_by_artist.insert(song_name);
    artist_summ.file_locations.push_back(file_location);
    artist_summ.total_songs_by_artist = 1;
    full_artist_summary.push_back(artist_summ);
  }
  else {
    for (size_t iter = 0; iter < full_artist_summary.size(); iter++){
      if (full_artist_summary[iter].artist_name == artist_name)
	{
	  artist_exists = true;
	  if (full_artist_summary[iter].songs_by_artist.check(song_name) == false)
	    {
	      full_artist_summary[iter].songs_by_artist.insert(song_name);
	      full_artist_summary[iter].file_locations.push_back(file_location);
	      full_artist_summary[iter].total_songs_by_artist++;
	      break;
	    }
	}
    }
    if (artist_exists == false) {
      ArtistSummary artist_summ;
      artist_summ.artist_name = artist_name;
      artist_summ.songs_by_artist.insert(song_name);
      artist_summ.file_locations.push_back(file_location);
      artist_summ.total_songs_by_artist = 1;
      full_artist_summary.push_back(artist_summ);
    }
  }
}

void AudioLibrary::write_artist_summ()
{
  std::vector<std::vector<std::string>> full_artist_summ_data;

  for (size_t artist_iter = 0; artist_iter < full_artist_summary.size(); artist_iter++){
    std::string artist_name = full_artist_summary[artist_iter].artist_name;
    std::vector<std::string> songs_by_artist = full_artist_summary[artist_iter].songs_by_artist.inorder();

    for (size_t songs_iter = 0; songs_iter < songs_by_artist.size(); songs_iter++){
      std::vector<std::string> artist_summ_values;
      std::string song_name = songs_by_artist[songs_iter];
      full_artist_summary[artist_iter].songs_by_artist.search(song_name);
      int file_loc_pos = full_artist_summary[artist_iter].songs_by_artist.get_search_id();
      std::string file_location = full_artist_summary[artist_iter].file_locations[file_loc_pos];
      artist_summ_values.push_back(artist_name);
      artist_summ_values.push_back(song_name);
      artist_summ_values.push_back(file_location);
      full_artist_summ_data.push_back(artist_summ_values);
      std::string ins_stmt = util::gen_ins_stmt("artist_summary", artist_summ_fields, artist_summ_values);
      AudioLibrary::db_ins_row(ins_stmt);
    }
  }
}

void AudioLibrary::write_artists(std::string file_location)
{

  audioinfo::init(util::to_char(file_location));
  std::string artist_name = audioinfo::get_info(ARTIST);

  if (artists.check(artist_name) == false) {
    total_artists++;
    artists.insert(artist_name);
    std::string ins_stmt = "INSERT INTO artists(artist_name) VALUES('" + artist_name + "');";
    AudioLibrary::db_ins_row(ins_stmt);
  }
}

void AudioLibrary::populate_playlist()
{
  char *err_msg = 0;
  int ret_code;
  const char *sql_stmt = "SELECT * from library";
  const char* data = "";


  AudioLibrary::load_db();

  ret_code = sqlite3_exec(library_db, sql_stmt, populate_playlist_cb, (void*)data, &err_msg);
  if( ret_code != SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", err_msg);
    sqlite3_free(err_msg);
  }else{
    fprintf(stdout, "Operation done successfully\n");
  }
}

int AudioLibrary::populate_playlist_cb(void *data, int total_col_num, char **value, char **fields)
{
  std::vector<std::string> row_data;
  row_data.push_back(value[LIB_NAME]);
  row_data.push_back(value[LIB_ARTIST]);
  row_data.push_back(value[LIB_ALBUM]);
  row_data.push_back(value[LIB_TIME]);
  row_data.push_back(value[LIB_FILE_LOCATION]);
  fidel_ui::Instance()->append_playlist_row(row_data);
  return 0;
}

void AudioLibrary::scan()
{
  db_indexed = true; // will become false after initialize function
  AudioLibrary::initialize();
  AudioLibrary::scan_dir(default_music_folder.c_str());
  db_indexed = true;
  indexed_once = true;
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
	      total_files++;
	      file_locations.push_back(file_location);
	      AudioLibrary::write_lib_data(file_location);
	      AudioLibrary::add_album_summ(file_location);
	      AudioLibrary::write_album_info(file_location);
	      AudioLibrary::add_artist_summ(file_location);
	      AudioLibrary::write_artists(file_location);
	    }
	  file_location = temp;
	}
    }
  }
  std::cout << "No. of Files : " << total_files << std::endl;
  std::cout << "No. of Subdirectories : " << subdir_count << std::endl;
  //sqlite3 *library_db = library_db;
  AudioLibrary::write_album_summ();
  AudioLibrary::write_artist_summ();
  AudioLibrary::write_lib_info();
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
