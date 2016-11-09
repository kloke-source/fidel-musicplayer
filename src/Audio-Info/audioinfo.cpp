#include "audioinfo.h"
#include <iostream>
#include <gtkmm.h>
#include <taglib/taglib.h>
#include <taglib/fileref.h>
#include <taglib/mp4file.h>
#include <taglib/oggfile.h>
#include <taglib/vorbisfile.h>

#include <Utilities/util.h>
#include <Audio-Library/audio-library.h>
#include <mutex>

audioinfo::audioinfo(){}
audioinfo::~audioinfo()
{
  std::cout << "AudioInfo destructor" << std::endl;
}

namespace {
  TagLib::FileRef audio_file;
  std::mutex audioinfo_mutex;
  char *audio_file_location;

  struct AudioFileInfo {
    std::string song_name;
    //TagLib::String song_name;
    std::string artist;
    std::string album;
    double duration_seconds;
  };

  struct ExtractedAlbumArtSuppData {
    btree<std::string> file_locs;
    btree<std::string> albums;
  };
  
  AudioFileInfo info;
  ExtractedAlbumArtSuppData extracted_album_art_supp_data;  
  std::vector<Gtk::Image*> extracted_album_art;
  int total_extracted_album_art = 0;
}

bool audioinfo::init_checker(char *filesrc)
{
  if (audio_file_location == filesrc){
    return true;
  }
  else return false;
}

void audioinfo::init(char *filesrc)
{
  if (audioinfo::init_checker(filesrc) == false){
    TagLib::FileRef file(filesrc);
    audio_file_location = filesrc;
    audio_file = file;
    audioinfo::set_data();
  }
}

void audioinfo::set_data()
{
  if (audio_file.tag()) {
    info.song_name = (audio_file.tag()->title()).to8Bit(true);
    info.artist = (audio_file.tag()->artist()).to8Bit(true);
    info.album = (audio_file.tag()->album()).to8Bit(true);
    info.duration_seconds = (audio_file.audioProperties()->length());
  }

  if (info.song_name == "" || info.song_name == " "){
    info.song_name = util::file_to_song_name(audio_file_location);
    info.song_name = util::escape_slashes(info.song_name);
  }
  if (info.artist == "" || info.artist == " "){
    info.artist = "Unknown Artist";
  }
  if (info.album == "" || info.album == " "){
    info.album = "Unknown Album";
  }
}

void audioinfo::set_duration(double duration)
{
  info.duration_seconds = duration;
}

void audioinfo::set_duration_from_tag()
{
  info.duration_seconds = audio_file.audioProperties()->length();
}

double audioinfo::tag_duration()
{
  double duration_seconds = audio_file.audioProperties()->length();
  return duration_seconds;
}

double audioinfo::duration()
{
  return info.duration_seconds;
}

std::string audioinfo::get_info(int enum_field)
{
  switch (enum_field) {
  case SONG_NAME:
    return info.song_name;
  case ARTIST:
    return info.artist;
  case ALBUM:
    return info.album;
    break;
  case DURATION_SECONDS:
    return util::to_string(info.duration_seconds);
    break;
  case TIME:
    return util::time_format(info.duration_seconds);
  }
}

std::string audioinfo::get_info(std::string field)
{
  std::string song_info;
  if (field == "song_name"){
    song_info = info.song_name;
  }
  if (field == "artist"){
    song_info = info.artist;
  }
  if (field == "album"){
    song_info = info.album;
  }
  if (field == "duration_seconds"){
    song_info = util::to_string(info.duration_seconds);
  }
  if (field == "time"){
    song_info = util::time_format(info.duration_seconds);
  }
  return song_info;
}

void audioinfo::add_album_art_to_index(Gtk::Image* album_art, std::string album_name)
{
  /** @brief Adds album art to an index, to make later retrieval much faster,
   * rather than extracting album art from a file. The index utilizes a binary
   * search tree, to make checking through the index faster.
   * 
   *
   * @param album_art The album art to be indexed
   *
   * @param album_name The name of the album to be added for reference to the index
   *
   */
  extracted_album_art.push_back(album_art);
  extracted_album_art_supp_data.albums.insert(album_name, total_extracted_album_art);
  total_extracted_album_art++;
}

Gtk::Image* audioinfo::get_album_art_by_name(std::string album_name, std::string file_location)
{
  /** @brief Returns album art, by searching through already
   * extracted album art by album name, if it doesn't find it in album art that
   * has already been extracted, it will use the file location of the song (second
   * parameter) to extract its album art.
   * 
   *
   * @param album_name The name of the album, that the function will use to
   * search through pre-indexed album art 
   * @param file_location This parameter is only used, if the function couldn't
   * find the album in pre-indexed album art
   *
   * @return Returns a Gtk::Image* of the album art
   */

  std::tuple<guint8*, gsize, bool> raw_album_art;

  auto raw_album_art_extract_job = std::async(std::launch::async, &audioinfo::extract_album_art, file_location);
  
  bool album_art_found = extracted_album_art_supp_data.albums.check(album_name);
  int found_pos = extracted_album_art_supp_data.albums.get_search_id();

  Gtk::Image *album_art;
  if (album_art_found == true)
    return extracted_album_art[found_pos];
  else {  
    album_art = new Gtk::Image();
    raw_album_art = raw_album_art_extract_job.get();
    if (std::get<2>(raw_album_art) == true) {
      Glib::RefPtr<Gdk::PixbufLoader> loader = Gdk::PixbufLoader::create();      
      loader->write(std::get<0>(raw_album_art), std::get<1>(raw_album_art));
      loader->close();
      Glib::RefPtr<Gdk::Pixbuf> pixbuf = loader->get_pixbuf();
      album_art->set(pixbuf);
    }
    else
      album_art->set_from_resource("/fidel/Resources/icons/blank-albumart.svg");
  }

    extracted_album_art.push_back(album_art);
    extracted_album_art_supp_data.file_locs.insert(file_location, total_extracted_album_art);
    extracted_album_art_supp_data.albums.insert(album_name, total_extracted_album_art);
    total_extracted_album_art++;
    return album_art;  
}

Gtk::Image* audioinfo::get_album_art(std::string file_location)
{
  std::string current_file_album;
  std::string current_file_artist;
  std::tuple<guint8*, gsize, bool> raw_album_art;

  auto raw_album_art_extract_job = std::async(std::launch::async, &audioinfo::extract_album_art, file_location);
  
  bool album_art_found = extracted_album_art_supp_data.file_locs.check(file_location);
  int found_pos = extracted_album_art_supp_data.file_locs.get_search_id();
  if (album_art_found == false) {
    audioinfo::init(util::to_char(file_location));
    current_file_album = audioinfo::get_info(ALBUM);
    current_file_artist = audioinfo::get_info(ARTIST);
      
    album_art_found = extracted_album_art_supp_data.albums.check(current_file_album);
    found_pos = extracted_album_art_supp_data.albums.get_search_id();
  }
    
  if (album_art_found == true)
    return extracted_album_art[found_pos];

  if (album_art_found == false) {  
    Gtk::Image *album_art = new Gtk::Image();
    raw_album_art = raw_album_art_extract_job.get();
    if (std::get<2>(raw_album_art) == true) {
      Glib::RefPtr<Gdk::PixbufLoader> loader = Gdk::PixbufLoader::create();      
      loader->write(std::get<0>(raw_album_art), std::get<1>(raw_album_art));
      loader->close();
      Glib::RefPtr<Gdk::Pixbuf> pixbuf = loader->get_pixbuf();
      album_art->set(pixbuf);
    }
    else
      album_art->set_from_resource("/fidel/Resources/icons/blank-albumart.svg");
      
    extracted_album_art.push_back(album_art);
    extracted_album_art_supp_data.file_locs.insert(file_location, total_extracted_album_art);
    extracted_album_art_supp_data.albums.insert(current_file_album, total_extracted_album_art);
    total_extracted_album_art++;
    return album_art;
  }
}

std::tuple<guint8*, gsize, bool> audioinfo::extract_album_art(std::string file_location)
{
  guint8* extracted_image;
  gsize image_size;
  bool albumart_found = false;
  
  if (util::check_file_format(file_location, "flac") == true) {
    TagLib::FLAC::File flac_file(util::to_char(file_location));
    const TagLib::List<TagLib::FLAC::Picture*>& picList = flac_file.pictureList();
    TagLib::FLAC::Picture* flac_cover_pic = new TagLib::FLAC::Picture();

    if (!picList.isEmpty()){
      flac_cover_pic = picList[0];
      albumart_found = true;
    }

    image_size = flac_cover_pic->data().size() ;
    extracted_image = (guint8*)malloc ( image_size ) ;
    if ( extracted_image )
      memcpy ( extracted_image, flac_cover_pic->data().data(), image_size );
  }
  
  else if (util::check_file_format(file_location, "mp3") == true) {
    static const char *IdPicture = "APIC" ;
    TagLib::MPEG::File mp3_file(util::to_char(file_location));
    TagLib::ID3v2::Tag *id3v2tag = mp3_file.ID3v2Tag();
    TagLib::ID3v2::FrameList Frame;
    TagLib::ID3v2::AttachedPictureFrame *picture_frame ;


    if ( id3v2tag ) {
      Frame = id3v2tag->frameListMap()[IdPicture];
      if (!Frame.isEmpty() )
        {
          for(TagLib::ID3v2::FrameList::ConstIterator iter = Frame.begin(); iter != Frame.end(); ++iter)
            {
              picture_frame = (TagLib::ID3v2::AttachedPictureFrame *)(*iter) ;
              {
                image_size = picture_frame->picture().size() ;
                extracted_image = (guint8*)malloc ( image_size ) ;
                if ( extracted_image )
                  {
                    memcpy ( extracted_image, picture_frame->picture().data(), image_size ) ;
                    albumart_found = true;
                  }
              }
            }
        }
    }
  }

  else if (util::check_file_format(file_location, "m4a") == true) {
    TagLib::MP4::File m4a_file(util::to_char(file_location));
    TagLib::MP4::Tag* m4a_tag = m4a_file.tag();
    TagLib::MP4::ItemListMap itemsListMap = m4a_tag->itemListMap();
    TagLib::MP4::Item coverItem;
    TagLib::MP4::CoverArtList coverArtList;
    if (!itemsListMap.isEmpty()){
      albumart_found = true;
      coverItem = itemsListMap["covr"];
      coverArtList = coverItem.toCoverArtList();
    }
    if (albumart_found == true){
      TagLib::MP4::CoverArt coverArt = coverArtList.front();
      image_size = coverArt.data().size() ;
      extracted_image = (guint8*)malloc (image_size) ;
      if (extracted_image)
        memcpy ( extracted_image, coverArt.data().data(), image_size ) ;
    }
  }

  if (albumart_found == true)
    return std::make_tuple(extracted_image, image_size, true);
  else
    return std::make_tuple((guint8*)"No Album Art", NULL, false);
}
