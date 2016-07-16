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

vector<vector<Glib::ustring> > batch_collected_info;
vector<btree<Glib::ustring> > batch_collected_btree;

vector<btree<Glib::ustring> > existing_lib_data;
vector<btree<Glib::ustring> > existing_lib_info_data;
vector<btree<Glib::ustring> > existing_album_info_data;
vector<btree<Glib::ustring> > existing_album_summ_data;
btree<Glib::ustring> existing_artist_info_data;
vector<btree<Glib::ustring> > existing_artist_summ_data;

vector<bool> existing_data_pulled;

vector<Glib::ustring> indexed_lib_data;
vector<vector<Glib::ustring> > indexed_lib_info_data;
vector<vector<Glib::ustring> > indexed_album_info_data;
vector<vector<Glib::ustring> > indexed_album_summ_data;
vector<vector<Glib::ustring> > indexed_artist_info_data;
vector<vector<Glib::ustring> > indexed_artist_summ_data;

//vector<Glib::ustring> indexed_ins_stmts;
btree<string> valid_file_formats;
btree<string> valid_fields;
//vector<string> albums;
//vector<string> artists;

int file_count;
int subdir_count;
int artist_num;
int album_num;

bool initialized = false;

string path = Glib::get_home_dir() + "/";

struct AlbumSummary{
  Glib::ustring album_name;
  btree<Glib::ustring> songs_in_album;
  vector<Glib::ustring> file_locations;
  int total_songs_in_album;
};

struct ArtistSummary{
  Glib::ustring artist_name;
  btree<Glib::ustring> songs_by_artist;
  vector<Glib::ustring> file_locations;
  int total_songs_by_artist;
};

vector<AlbumSummary> full_album_summary;
vector<ArtistSummary> full_artist_summary;

enum audio_lib_enums {
  ID,
  FILE_LOCATION,
  NAME,
  ARTIST,
  ALBUM,
  TIME,
  DURATION_SEC,
  FILE_COUNT = 0,
  ARTIST_NUM = 1,
  ALBUM_NUM = 2,
  LIB = 0,
  LIB_INFO = 1,
  ALBUM_INFO = 2,
  ALBUM_SUMM = 3,
  ARTIST_INFO = 4,
  ARTIST_SUMM = 5,
};

vector<Glib::ustring> album_info_fields;
vector<Glib::ustring> album_summ_fields;
vector<Glib::ustring> artist_info_fields;
void AudioLibrary::init()
{
  if (db_opened == false){
    AudioLibrary::open_db();
  }
  if (initialized == false){
    valid_file_formats.insert("mp3");
    valid_file_formats.insert("flac");
    valid_file_formats.insert("wav");
    valid_file_formats.insert("ogg");
    valid_file_formats.insert("m4a");
    valid_file_formats.insert("m4p");

    valid_fields.insert("file_location");
    valid_fields.insert("Name");
    valid_fields.insert("Artist");
    valid_fields.insert("Album");
    valid_fields.insert("Time");
    valid_fields.insert("songs_num");
    valid_fields.insert("artist_num");
    valid_fields.insert("artist_name");
    valid_fields.insert("album_num");
    valid_fields.insert("album_name");

    album_info_fields.push_back("album_name");
    album_info_fields.push_back("album_art_location");

    album_summ_fields.push_back("album_name");
    album_summ_fields.push_back("songs_in_album");
    album_summ_fields.push_back("file_location");

    artist_info_fields.push_back("artist_name");

    for (size_t iter = 0; iter < 6; iter++){ //there are 6 tables in the db
      existing_data_pulled.push_back(false);
    }
    initialized = true;
  }
  file_count = 0;
  file_locations.clear();
  subdir_locations.clear();
}

void AudioLibrary::scan()
{
  if (initialized == false){
    AudioLibrary::init();
  }

  AudioLibrary::scan_dir("/home/tashrif/Music");
  AudioLibrary::flush_to_db();
  cout << "DB write completed" << endl;
  cout << "File Count: " << file_count << endl;

  //string unescaped_space = "Hello is it me";
  //string escaped_space = util::escape_spaces(unescaped_space);
  //cout << "Escaped spaces \n" << escaped_space << endl;
  //cout << "unescaped spaces \n" << util::unescape_spaces(escaped_space) << endl;
  AudioLibrary::close_db();
}

void AudioLibrary::open_db()
{
  string homedir = Glib::get_home_dir();
  string library_db_location = homedir + "/fidel/Resources/Databases/audio-library.db";
  cout << library_db_location << endl;
  if(sqlite3_open(library_db_location.c_str(), &library_db) == SQLITE_OK){
    cout << "successfully connected to database" << endl;
    db_opened = true;
  }
  else {
    db_opened = false;
  }
}

void AudioLibrary::close_db()
{
  sqlite3_close(library_db);
}
bool AudioLibrary::db_field_validate(string field)
{
  return valid_fields.check(field);
}

void AudioLibrary::update_library_db(string table_name, string db_field ,string db_data, string position)
{
  if (db_opened == true && AudioLibrary::db_field_validate(db_field) == true)
  {
    stringstream db_string_stream;
    if (table_name == "library_information"){
      db_string_stream << "UPDATE " << table_name << " SET " << db_field << " = '" << db_data << "' WHERE ID = '" << position << "' ;";
    }
    else {
      db_string_stream << "UPDATE " << table_name << " SET " << db_field << " = '" << db_data << "' WHERE file_location = '" << position << "' ;";
    }
    string db_data_string = db_string_stream.str();
    char *str = &db_data_string[0];

    sqlite3_stmt *statement;

    char *query = str;
    {
      if(sqlite3_prepare(library_db,query,-1,&statement,0)==SQLITE_OK)
      {
        sqlite3_step(statement);
        sqlite3_finalize(statement);
      }
    }
  }
  else if (AudioLibrary::db_field_validate(db_field) == true){
    cout << "Connection to database failed" << endl;
  }
  if (AudioLibrary::db_field_validate(db_field) != true){
    cout << "Invalid database field or invalid row ID" << endl;
  }
}
/*
void AudioLibrary::update_library_db(string table_name, string db_field ,Glib::ustring db_data, string position)
{
if (db_opened == true && AudioLibrary::db_field_validate("library", db_field) == true)
{
cout << "update called" << endl;
stringstream db_string_stream;
db_string_stream << "UPDATE library SET " << db_field << " = '" << db_data << "' WHERE file_location = '" << position << "' ;";
string db_data_string = db_string_stream.str();
cout << db_data_string << endl;
char *str = &db_data_string[0];

sqlite3_stmt *statement;
int result;

char *query = str;
{
if(sqlite3_prepare(library_db,query,-1,&statement,0)==SQLITE_OK)
{
int res = sqlite3_step(statement);
result  = res;
sqlite3_finalize(statement);
}
}
}
else if (AudioLibrary::db_field_validate("library", db_field) == true){
cout << "Connection to database failed" << endl;
}
if (AudioLibrary::db_field_validate("library", db_field) != true){
cout << "Invalid database field or invalid row ID" << endl;
}
}
*/
void AudioLibrary::update_library_db(string table_name, Glib::ustring db_data_string)
{
  if (db_opened == true)
  {
    sqlite3_stmt *statement;

    char *query = util::to_char(db_data_string);
    {
      if(sqlite3_prepare(library_db,query,-1,&statement,0)==SQLITE_OK)
      {
        sqlite3_step(statement);
        sqlite3_finalize(statement);
      }
    }
  }
  else {
    cout << "Connection to database failed" << endl;
  }
}

bool AudioLibrary::overwrite_check(string file_location)
{
  bool existing = false;
  if (AudioLibrary::get_db_field_data("library", "file_location", file_location, false) == file_location){
    existing = true;
    return true;
  }
  if (AudioLibrary::get_db_field_data("library", "file_location", file_location, true) == file_location){
    existing = true;
    return true;
  }
  if (AudioLibrary::get_db_field_data("library", "file_location", "ID", util::to_string(file_count), true) == file_location){
    existing = true;
    return true;
  }
  return existing;
}

bool AudioLibrary::exists_in_lib(Glib::ustring file_location)
{
  audioinfo::init(util::to_char(file_location));

  if (existing_data_pulled[LIB] == false){
    existing_lib_data = AudioLibrary::batch_collect_btree("library");
    existing_data_pulled[LIB] = true;
  }

  bool data_exists = false;
  for (size_t row_iter = 0; row_iter < existing_lib_data.size(); row_iter++){
    if (existing_lib_data[row_iter].check(file_location) == true){
      data_exists = true;
      break;
    }
  }

  return data_exists;
}

int AudioLibrary::get_song_num()
{
  if (db_opened == false){
    AudioLibrary::open_db();
  }
  Glib::ustring song_num = AudioLibrary::get_db_field_data("library_information", "songs_num", "ID", "1", true);
  return util::to_int(song_num);
}

Glib::ustring AudioLibrary::get_db_field_data(string table_name, Glib::ustring field, Glib::ustring where_id, bool definite)
{
  cout << "get db called" << endl;
  sqlite3_stmt *statement;

  field    = util::escape_string(field);
  where_id = util::escape_string(where_id);

  Glib::ustring db_search_string;
  char *query;

  if (definite == false){
    db_search_string = "SELECT " + field + " FROM " + table_name + " WHERE ";
    db_search_string.append(field + " like '%" + where_id + "%';");
    query = util::to_char(db_search_string);
  }
  else {
    db_search_string = "SELECT " + field + " FROM " + table_name + " WHERE ";
    db_search_string.append(field + " = '" + where_id + "';");
    query = util::to_char(db_search_string);
  }

  cout << "search statement: " << db_search_string << endl;
  Glib::ustring search_result;
  if ( sqlite3_prepare(library_db, query, -1, &statement, 0 ) == SQLITE_OK )
  {
    int ctotal = sqlite3_column_count(statement);
    int res = 0;

    while ( 1 )
    {
      res = sqlite3_step(statement);

      if ( res == SQLITE_ROW )
      {
        for ( int i = 0; i < ctotal; i++ )
        {
          string search = (char*)sqlite3_column_text(statement, i);
          search_result = search;
        }
        cout << endl;
      }

      if ( res == SQLITE_DONE || res==SQLITE_ERROR)
      {
        cout << "done " << endl;
        break;
      }
    }
  }
  cout << "Return value (" << search_result << ")" << endl;
  return search_result;
  //cout << "Result -> " << search_result << endl;
}

Glib::ustring AudioLibrary::get_db_field_data(string table_name, Glib::ustring field, Glib::ustring where_field, Glib::ustring where_id, bool definite)
{
  cout << "get db called" << endl;
  sqlite3_stmt *statement;

  field       = util::escape_string(field);
  where_field = util::escape_string(where_field);
  where_id    = util::escape_string(where_id);

  Glib::ustring db_search_string;
  Glib::ustring search_result;
  char *query;

  if (definite == false){
    db_search_string = "SELECT " + field + " FROM " + table_name + " WHERE ";
    db_search_string.append(where_field + " like '%" + where_id + "%';");
    query = util::to_char(db_search_string);
  }
  else {
    db_search_string = "SELECT " + field + " FROM " + table_name + " WHERE ";
    db_search_string.append(where_field + " = '" + where_id + "';");
    query = util::to_char(db_search_string);
  }

  cout << "search statement: " << db_search_string << endl;

  if ( sqlite3_prepare(library_db, query, -1, &statement, 0 ) == SQLITE_OK )
  {
    int ctotal = sqlite3_column_count(statement);
    int res = 0;

    while ( 1 )
    {
      res = sqlite3_step(statement);

      if ( res == SQLITE_ROW )
      {
        for ( int i = 0; i < ctotal; i++ )
        {
          string search = (char*)sqlite3_column_text(statement, i);
          search_result = search;
        }
        cout << endl;
      }

      if ( res == SQLITE_DONE || res==SQLITE_ERROR)
      {
        cout << "done " << endl;
        break;
      }
    }
    cout << "Return value (" << search_result << ")" << endl;

  }
  return search_result;
}

void AudioLibrary::populate_playlist()
{
  char *err_msg = 0;
  int ret_cb;
  const char *sql_stmt = "SELECT * from library";
  const char* data = "";

  if (db_opened == false){
    AudioLibrary::open_db();
  }
  ret_cb = sqlite3_exec(library_db, sql_stmt, populate_playlist_cb, (void*)data, &err_msg);
  if( ret_cb != SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", err_msg);
    sqlite3_free(err_msg);
  }else{
    fprintf(stdout, "Operation done successfully\n");
  }
}

int AudioLibrary::get_table_pos(string table_name)
{
  if (table_name == "ID"){
    return ID;
  }
  if (table_name == "library"){
    return LIB;
  }
  if (table_name == "library_information"){
    return LIB_INFO;
  }
  if (table_name == "album_information"){
    return ALBUM_INFO;
  }
  if (table_name == "album_summary"){
    return ALBUM_SUMM;
  }
  if (table_name == "artist_information"){
    return ARTIST_INFO;
  }
  if (table_name == "artist_summary"){
    return ARTIST_SUMM;
  }
}


int AudioLibrary::populate_playlist_cb(void *data, int total_col_num, char **value, char **fields)
{
  vector<Glib::ustring> row_data;
  row_data.push_back(value[NAME]);
  row_data.push_back(value[ARTIST]);
  row_data.push_back(value[ALBUM]);
  row_data.push_back(value[TIME]);
  row_data.push_back(value[FILE_LOCATION]);
  // --(deprecated)-- fidel_ui::Instance()->add_list_store_row(row_data);
  return 0;
}

vector<vector<Glib::ustring> > AudioLibrary::batch_collect_info(string table_name)
{
  if (db_opened == false){
    AudioLibrary::open_db();
  }
  batch_collected_info.clear();
  AudioLibrary::batch_collect_info_backend(table_name);
  return batch_collected_info;
}

void AudioLibrary::batch_collect_info_backend(string table_name)
{
  char *err_msg = 0;
  int ret_cb;
  string stmt = "SELECT * from " + table_name;
  const char *sql_stmt = stmt.c_str();
  const char* data = "";

  if (db_opened == false){
    AudioLibrary::open_db();
  }
  ret_cb = sqlite3_exec(library_db, sql_stmt, batch_collect_info_cb, (void*)data, &err_msg);
  if( ret_cb != SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", err_msg);
    sqlite3_free(err_msg);
  }else{
    fprintf(stdout, "Operation done successfully\n");
  }
}

int AudioLibrary::batch_collect_info_cb(void *data, int total_col_num, char **value, char **fields)
{
  cout << "IN BATCH TEST " << value[2] << endl;
  vector<Glib::ustring> row_data;
  for (int iter=0; iter < total_col_num; iter++){
    row_data.push_back(value[iter]);
  }
  batch_collected_info.push_back(row_data);
  return 0;
}

vector<btree<Glib::ustring> > AudioLibrary::batch_collect_btree(string table_name)
{
  if (db_opened == false){
    AudioLibrary::open_db();
  }
  batch_collected_btree.clear();
  AudioLibrary::batch_collect_btree_backend(table_name);
  return batch_collected_btree;
}

void AudioLibrary::batch_collect_btree_backend(string table_name)
{
  char *err_msg = 0;
  int ret_cb;
  string stmt = "SELECT * from " + table_name;
  const char *sql_stmt = stmt.c_str();
  const char* data = "";

  if (db_opened == false){
    AudioLibrary::open_db();
  }
  ret_cb = sqlite3_exec(library_db, sql_stmt, batch_collect_btree_cb, (void*)data, &err_msg);
  if( ret_cb != SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", err_msg);
    sqlite3_free(err_msg);
  }else{
    fprintf(stdout, "Operation done successfully\n");
  }
}

int AudioLibrary::batch_collect_btree_cb(void *data, int total_col_num, char **value, char **fields)
{
  cout << "IN BATCH TEST " << value[2] << endl;
  btree<Glib::ustring> row_data;
  for (int iter=0; iter < total_col_num; iter++){
    row_data.insert(value[iter]);
  }
  batch_collected_btree.push_back(row_data);
  return 0;
}

vector<Glib::ustring> AudioLibrary::get_db_row(Glib::ustring field, Glib::ustring where_id)
{
  if (db_opened == false){
    AudioLibrary::open_db();
  }
  vector<Glib::ustring> fields;
  vector<Glib::ustring> row_data;

  fields.push_back("Name");
  fields.push_back("Artist");
  fields.push_back("Album");
  fields.push_back("Time");
  fields.push_back("file_location");

  for(size_t iter=0; iter < fields.size(); iter++){
    row_data.push_back(AudioLibrary::get_db_field_data("library", fields[iter], field, where_id, true));
  }
  cout << "Pushed file location: " << row_data[4] << endl;
  return row_data;
}

void AudioLibrary::write_lib_info()
{
  bool existing = false;
  vector<string> lib_info_fields;
  lib_info_fields.push_back(util::to_string(file_count));
  lib_info_fields.push_back(util::to_string(artist_num));
  lib_info_fields.push_back(util::to_string(album_num));

  if (AudioLibrary::get_db_field_data("library_information", "ID", "1", true) != ""){
    cout << "something exists" << endl;
    Glib::ustring update_stmt = "UPDATE library_information SET ";
    update_stmt.append("songs_num = " + lib_info_fields[FILE_COUNT] + ", ");
    update_stmt.append("artist_num = " + lib_info_fields[ARTIST_NUM] + ", " + "album_num = " + lib_info_fields[ALBUM_NUM] + ";");
    cout << update_stmt << endl;
    AudioLibrary::update_library_db("library_information", update_stmt);
    return;
  }
  if (existing == false){
    cout << "something doesn't exist" << endl;
    Glib::ustring ins_stmt = "INSERT INTO library_information (songs_num, artist_num, album_num) ";
    ins_stmt.append("VALUES('" + lib_info_fields[FILE_COUNT] + "', '" + lib_info_fields[ARTIST_NUM] + "', '");
    ins_stmt.append(lib_info_fields[ALBUM_NUM] + "');");
    AudioLibrary::write("library_information", ins_stmt);
  }
}

void AudioLibrary::write_album_summ()
{
  vector<Glib::ustring> album_summ_fields;
  album_summ_fields.push_back("album_name");
  album_summ_fields.push_back("songs_in_album");
  album_summ_fields.push_back("file_location");

  vector<vector<Glib::ustring> > full_album_data;
  cout << "WRITING ALBUM SUMMARY " << endl;
  for (size_t album_iter = 0; album_iter < full_album_summary.size(); album_iter++){
    Glib::ustring album_name = full_album_summary[album_iter].album_name;
    bool album_name_written = false;
    vector<Glib::ustring> songs_in_album = full_album_summary[album_iter].songs_in_album.inorder();
    for (size_t songs_iter = 0; songs_iter < songs_in_album.size(); songs_iter++){
      vector<Glib::ustring> album_summ_values;
      Glib::ustring song_name = songs_in_album[songs_iter];
      full_album_summary[album_iter].songs_in_album.search(song_name);
      int file_loc_pos = full_album_summary[album_iter].songs_in_album.get_search_id();
      Glib::ustring file_location = full_album_summary[album_iter].file_locations[file_loc_pos];
      bool skip = false;
      if (album_name_written == false)
      {
        album_summ_values.push_back(album_name);
        album_summ_values.push_back(song_name);
        album_summ_values.push_back(file_location);
        full_album_data.push_back(album_summ_values);
        //Glib::ustring ins_stmt = util::gen_ins_stmt("album_summary", album_summ_fields, album_summ_values);
        //AudioLibrary::write("album_summary", ins_stmt);
        album_name_written = true;
        skip = true;
      }
      if (album_name_written == true && skip == false)
      {
        album_summ_values.push_back(album_name); // where ---- was
        album_summ_values.push_back(song_name);
        album_summ_values.push_back(file_location);
        full_album_data.push_back(album_summ_values);
        //Glib::ustring ins_stmt = util::gen_ins_stmt("album_summary", album_summ_fields, album_summ_values);
        //AudioLibrary::write("album_summary", ins_stmt);
      }
    }
  }
  Glib::ustring bulk_ins_stmt = util::gen_bulk_ins_stmt("album_summary", album_summ_fields, full_album_data);
  //cout << "BULK INS STMT -> \n" << bulk_ins_stmt << endl;
  AudioLibrary::bulk_write("album_summary", bulk_ins_stmt);
}

void AudioLibrary::write_album_info(string field, string value, string album_art_location)
{
  string existing_info = AudioLibrary::get_db_field_data("album_information", field, value, true);
  if (existing_info == ""){
    existing_info = AudioLibrary::get_db_field_data("album_information", field, value, false);
  }
  if (existing_info == "") {
    cout << "something doesn't exist" << endl;
    album_num++;

    vector<Glib::ustring> album_info_fields;
    album_info_fields.push_back("album_name");
    album_info_fields.push_back("album_art_location");

    vector<Glib::ustring> album_info_values;
    album_info_values.push_back(audioinfo::get_info("album"));
    album_info_values.push_back(album_art_location);

    string album_ins_stmt = "BEGIN TRANSACTION; ";
    album_ins_stmt += util::gen_ins_stmt("album_information", album_info_fields, album_info_values);
    album_ins_stmt += "END;";
    cout << "Custom Ins stmt " << album_ins_stmt << endl;
    AudioLibrary::write("album_information", album_ins_stmt);
  }
}

void AudioLibrary::write_artist_info(string field, string value)
{
  string existing_info = AudioLibrary::get_db_field_data("artist_information", field, value, true);
  if (existing_info == ""){
    existing_info = AudioLibrary::get_db_field_data("artist_information", field, value, false);
  }
  if (existing_info == "") {
    cout << "something doesn't exist" << endl;
    cout << "Artist write called: " << field << " " << value << endl;
    artist_num++;
    AudioLibrary::write("artist_information", field, value);
  }
}

void AudioLibrary::add_lib_data(Glib::ustring ins_stmt)
{
  indexed_lib_data.push_back(ins_stmt);
}

void AudioLibrary::add_album_info(string file_location)
{
  audioinfo::init(util::to_char(file_location));
  if (existing_data_pulled[ALBUM_INFO] == false){
    existing_album_info_data = AudioLibrary::batch_collect_btree("album_information");
    existing_data_pulled[ALBUM_INFO] = true;
  }

  vector<Glib::ustring> album_info_values;
  Glib::ustring album_name = audioinfo::get_info("album");
  Glib::ustring album_art_location = audioinfo::extract_album_art(util::to_char(file_location));

  album_info_values.push_back(album_name);
  album_info_values.push_back(album_art_location);

  bool data_exists = false;
  for (size_t row_iter = 0; row_iter < existing_album_info_data.size(); row_iter++){
    for (size_t col_iter = 0; col_iter < album_info_values.size(); col_iter++){
      if (existing_album_info_data[row_iter].check(album_info_values[col_iter]) == true){
        data_exists = true;
        break;
      }
    }
  }

  if (data_exists == false){
    indexed_album_info_data.push_back(album_info_values);
    existing_album_info_data.push_back(util::vector_to_btree(album_info_values));
  }
}

void AudioLibrary::add_album_summ(string file_location) //overwrite protection not added
{
  audioinfo::init(util::to_char(file_location));

  string album_name = audioinfo::get_info("album");
  string song_name = audioinfo::get_info("song_name");

  bool album_exists = false;
  if (full_album_summary.size() == 0){
    AlbumSummary album_summ;
    album_summ.album_name = album_name;
    int insert_id = 0; //insert id is zero cause there is currently now songs in the album
    album_summ.songs_in_album.insert(song_name, insert_id);
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
          cout << "inserting new album ----------" << endl;
          int insert_id = full_album_summary[iter].total_songs_in_album;
          full_album_summary[iter].songs_in_album.insert(song_name, insert_id);
          full_album_summary[iter].file_locations.push_back(file_location);
          cout << "finishedd inserting new album ----------" << endl;
          full_album_summary[iter].total_songs_in_album++;
          break;
        }
      }
    }
    if (album_exists == false) {
      AlbumSummary album_summ;
      album_summ.album_name = album_name;
      cout << "Creating new album ----------" << endl;
      int insert_id = 0; //insert id is zero cause there is currently now songs in the album
      album_summ.songs_in_album.insert(song_name, insert_id);
      album_summ.file_locations.push_back(file_location);
      cout << "finishd creating new album ----------" << endl;
      album_summ.total_songs_in_album = 1;
      full_album_summary.push_back(album_summ);
    }
  }
}

void AudioLibrary::add_artist_info(string file_location) //functionality not tested
{
  audioinfo::init(util::to_char(file_location));
  Glib::ustring artist_name = audioinfo::get_info("artist");
  bool data_exists = existing_artist_info_data.check(artist_name);

  if (data_exists == false){
    vector<Glib::ustring> artist_info_values;
    artist_info_values.push_back(artist_name);
    indexed_artist_info_data.push_back(artist_info_values);
    existing_artist_info_data.insert(artist_name);
  }
  /*
  if (existing_data_pulled[ARTIST_INFO] == false){
  existing_artist_info_data = AudioLibrary::batch_collect_btree("artist_information");
  existing_data_pulled[ARTIST_INFO] = true;
}

vector<Glib::ustring> artist_info_values;

artist_info_values.push_back(artist_name);

bool data_exists = false;
for (size_t row_iter = 0; row_iter < existing_artist_info_data.size(); row_iter++){
for (size_t col_iter = 0; col_iter < artist_info_values.size(); col_iter++){
if (existing_artist_info_data[row_iter].check(artist_info_values[col_iter]) == true){
data_exists = true;
break;
}
}
}

if (data_exists == false){
indexed_artist_info_data.push_back(artist_info_values);
existing_artist_info_data.push_back(util::vector_to_btree(artist_info_values));
}
*/
}

void AudioLibrary::add_artist_summ(string file_location) //overwrite protection not added
{
  audioinfo::init(util::to_char(file_location));
  string artist_name = audioinfo::get_info("artist");
  string song_name = audioinfo::get_info("song_name");

  bool album_exists = false;
  if (full_artist_summary.size() == 0){
    ArtistSummary album_summ;
    album_summ.artist_name = artist_name;
    int insert_id = 0; //insert id is zero cause there is currently now songs in the album
    album_summ.songs_by_artist.insert(song_name, insert_id);
    album_summ.file_locations.push_back(file_location);
    album_summ.total_songs_by_artist = 1;
    full_artist_summary.push_back(album_summ);
  }
  else {
    for (size_t iter = 0; iter < full_artist_summary.size(); iter++){
      if (full_artist_summary[iter].artist_name == artist_name)
      {
        album_exists = true;
        if (full_artist_summary[iter].songs_by_artist.check(song_name) == false)
        {
          cout << "inserting new album ----------" << endl;
          int insert_id = full_artist_summary[iter].total_songs_by_artist;
          full_artist_summary[iter].songs_by_artist.insert(song_name, insert_id);
          full_artist_summary[iter].file_locations.push_back(file_location);
          cout << "finishedd inserting new album ----------" << endl;
          full_artist_summary[iter].total_songs_by_artist++;
          break;
        }
      }
    }
    if (album_exists == false) {
      ArtistSummary album_summ;
      album_summ.artist_name = artist_name;
      cout << "Creating new album ----------" << endl;
      int insert_id = 0; //insert id is zero cause there is currently no songs in the album
      album_summ.songs_by_artist.insert(song_name, insert_id);
      album_summ.file_locations.push_back(file_location);
      cout << "finishd creating new album ----------" << endl;
      album_summ.total_songs_by_artist = 1;
      full_artist_summary.push_back(album_summ);
    }
  }
}

void AudioLibrary::flush_to_db()
{
  Glib::ustring bulk_lib_stmt = util::collate_ins_stmts(indexed_lib_data);
  Glib::ustring bulk_album_info_stmt = util::gen_bulk_ins_stmt("album_information", album_info_fields, indexed_album_info_data);
  Glib::ustring bulk_artist_info_stmt = util::gen_bulk_ins_stmt("artist_information", artist_info_fields, indexed_artist_info_data);

  auto flush_job1 = std::async(std::launch::async,	AudioLibrary::bulk_write, "library", bulk_lib_stmt);
  auto flush_job2 = std::async(std::launch::async, AudioLibrary::bulk_write, "album_information", bulk_album_info_stmt);
  auto flush_job3 = std::async(std::launch::async, AudioLibrary::bulk_write, "artist_information", bulk_artist_info_stmt);
  auto flush_job4 = std::async(std::launch::async, AudioLibrary::write_album_summ);
  flush_job1.get();
  flush_job2.get();
  flush_job3.get();
  flush_job4.get();
  //AudioLibrary::write_artist_summ();
  cout << "Successfully flushed to database" << endl;
}

void AudioLibrary::write(string table_name, Glib::ustring db_data_string)
{
  if (db_opened == true)
  {
    sqlite3_stmt *statement;

    cout << db_data_string << endl;
    char *query = util::to_char(db_data_string);
    {
      if(sqlite3_prepare_v2(library_db,query,-1,&statement,0)==SQLITE_OK)
      {
        sqlite3_step(statement);
        sqlite3_finalize(statement);
      }
    }
  }
  else {
    cout << "Connection to database failed" << endl;
  }
}
/*
void AudioLibrary::write(string table_name, string db_field, Glib::ustring db_data)
{
if (db_opened == true && AudioLibrary::db_field_validate("library", db_field) == true)
{
//stringstream db_string_stream;
//db_string_stream << "INSERT INTO library (" << db_field  << ") VALUES('" << db_data << "');";

//string db_data_string = db_string_stream.str();

Glib::ustring db_data_string;
db_data_string = "INSERT INTO library (" + db_field + ") VALUES('" + db_data + "');";
//char *str = &db_data_string[0];

sqlite3_stmt *statement;
int result;

char *query = util::to_char(db_data_string);
{
if(sqlite3_prepare(library_db,query,-1,&statement,0)==SQLITE_OK)
{
int res = sqlite3_step(statement);
result  = res;
sqlite3_finalize(statement);
}
}
}
else if (AudioLibrary::db_field_validate("library", db_field) == true){
cout << "Connection to database failed" << endl;
}
if (AudioLibrary::db_field_validate("library", db_field) != true){
cout << "Invalid database field" << endl;
}
}
*/
void AudioLibrary::write(string table_name, string db_field, string db_data)
{
  if (db_opened == true && AudioLibrary::db_field_validate(db_field) == true)
  {
    stringstream db_string_stream;
    db_string_stream << "INSERT INTO " << table_name << " (" << db_field  << ") VALUES('" << db_data << "');";

    string db_data_string = db_string_stream.str();
    cout << db_data_string << endl;
    char *str = &db_data_string[0];

    sqlite3_stmt *statement;

    char *query = str;
    {
      if(sqlite3_prepare(library_db,query,-1,&statement,0)==SQLITE_OK)
      {
        sqlite3_step(statement);
        sqlite3_finalize(statement);
      }
    }
  }
  else if (AudioLibrary::db_field_validate(db_field) == true){
    cout << "Connection to database failed" << endl;
  }
  if (AudioLibrary::db_field_validate(db_field) != true){
    cout << "Invalid database field" << endl;
  }
}

void AudioLibrary::bulk_write(string table_name, Glib::ustring bulk_ins_stmt)
{
  if (db_opened != true){
    AudioLibrary::open_db();
  }
  char *bulk_stmt = util::to_char(bulk_ins_stmt);
  char *error_msg;
  sqlite3_exec(library_db, bulk_stmt, AudioLibrary::bulk_write_cb, 0, &error_msg);
  //cout << "Error msg " << error_msg << endl;
}

int AudioLibrary::bulk_write_cb(void *data, int total_col_num, char **value, char **fields)
{
  for(int iter=0; iter < total_col_num; iter++){
    printf("%s = %s\n", fields[iter], value[iter] ? value[iter] : "NULL");
  }
  printf("\n");
  return 0;
}

bool AudioLibrary::file_validator(string file_location)
{
  return valid_file_formats.check(file_location.substr(file_location.find_last_of(".") + 1));
}

//AudioLibrary::AudioLibrary::scan_dir recursion variables
int subdir_iter=0;
int subdir_iter_amount=0;
bool subdir_iter_init = false;
//end

void AudioLibrary::scan_dir(const char *dir_location){
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
      string temp = file_location;
      file_location += file;
      if (AudioLibrary::file_validator(file_location) == true){
        auto ins_stmt_job = std::async(std::launch::async,	util::gen_db_ins_stmt, file_location, file);
        file_locations.push_back(util::to_char(file_location));
        file_count++;
        if (AudioLibrary::overwrite_check(file_location) == false){
          AudioLibrary::add_lib_data(ins_stmt_job.get());
          AudioLibrary::add_album_summ(file_location);
          AudioLibrary::add_artist_summ(file_location);
          AudioLibrary::add_album_info(file_location);
          AudioLibrary::add_artist_info(file_location);
        }
        else {
          cout << "Duplicate db entry" << endl;
        }
      }
      file_location = temp;
    }
  }
  cout << "file count: " << file_count << endl;
  cout << "subdirs: " << subdir_count << endl;
  if (subdir_iter_init == true)
  {
    subdir_iter++;
  }
  if (subdir_locations.size() != 0){
    subdir_iter_amount = subdir_locations.size();
  }
  if (subdir_iter < subdir_iter_amount){
    subdir_iter_init = true;
    AudioLibrary::scan_dir(subdir_locations[subdir_iter]);
  }
}
