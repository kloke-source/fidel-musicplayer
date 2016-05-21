#include "audioinfo.h"
#include <Utilities/util.h>
#include <taglib/taglib.h>
#include <Audio-Library/audio-library.h>
#include <taglib/fileref.h>
#include <taglib/mp4file.h>
#include <taglib/oggfile.h>
#include <taglib/vorbisfile.h>
#include <iostream>
#include <gtkmm.h>

#include <unicode/ustream.h>
#include <unicode/uchar.h>
#include <unicode/unistr.h>
#include <unicode/brkiter.h>

audioinfo::audioinfo(){}
audioinfo::~audioinfo(){}

using namespace std;

TagLib::FileRef audio_file;

//string home_dir = util::get_home_dir();
char *audio_file_location;

struct AudioFileInfo{
  Glib::ustring song_name;
  //TagLib::String song_name;
  Glib::ustring artist;
  Glib::ustring album;
  double duration_seconds;
};

AudioFileInfo info;

enum album_info
{
  ID,
  ALBUM_NAME,
  ALBUM_ART_LOCATION
};
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
    audioinfo::setData();
  }
}

void audioinfo::setData()
{
  info.song_name = (audio_file.tag()->title()).to8Bit(true);
  cout << "Song name: " << info.song_name << endl;
  info.artist = (audio_file.tag()->artist()).to8Bit(true);
  info.album = (audio_file.tag()->album()).to8Bit(true);
  info.duration_seconds = (audio_file.audioProperties()->length());

  info.song_name = util::escape_slashes(info.song_name);
  info.artist = util::escape_slashes(info.artist);
  info.album = util::escape_slashes(info.album);

  if (info.song_name == "" || info.song_name == " "){
    info.song_name = util::file_to_song_name(audio_file_location);
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
  cout << "Tag duration  " << info.duration_seconds << endl;
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

Glib::ustring audioinfo::get_info(std::string field)
{
  Glib::ustring song_info;
  if (field == "song_name"){
    song_info = info.song_name;
  }
  if (field == "artist"){
    song_info = info.artist;
  }
  if (field == "album"){
    song_info = info.album;
  }
  if (field == "duration_formatted"){
    song_info = util::time_format(info.duration_seconds);
  }
  return song_info;
}

Gtk::Image* audioinfo::get_album_art(char *file_location, int width, int height)
{
  string album_art_location = Glib::get_home_dir() + "/fidel/temp/album-art.jpg";
  Gtk::Image *album_art = new Gtk::Image();
  Gtk::Image null_tester;
  FILE *image_file;

  bool albumart_found = false;
  void *source_image;
  unsigned long SIZE;

  if(((string)file_location).substr(((string)file_location).find_last_of(".") + 1) == "flac"){
    TagLib::FLAC::File flac_file(file_location);
    const TagLib::List<TagLib::FLAC::Picture*>& picList = flac_file.pictureList();
    TagLib::FLAC::Picture* flac_cover_pic = new TagLib::FLAC::Picture();

    if (!picList.isEmpty()){
      flac_cover_pic = picList[0];
      albumart_found = true;
    }

    image_file = fopen(album_art_location.c_str(),"wb");

    SIZE = flac_cover_pic->data().size() ;
    source_image = malloc ( SIZE ) ;
    if ( source_image )
    {
      memcpy ( source_image, flac_cover_pic->data().data(), SIZE ) ;
      fwrite(source_image,SIZE,1, image_file);
      fclose(image_file);
      free( source_image ) ;
    }
  }
  if(((string)file_location).substr(((string)file_location).find_last_of(".") + 1) == "mp3"){
    static const char *IdPicture = "APIC" ;
    TagLib::MPEG::File mp3_file(file_location);
    TagLib::ID3v2::Tag *id3v2tag = mp3_file.ID3v2Tag();
    TagLib::ID3v2::FrameList Frame;
    TagLib::ID3v2::AttachedPictureFrame *picture_frame ;

    image_file = fopen(album_art_location.c_str(),"wb");

    if ( id3v2tag )
    {
      Frame = id3v2tag->frameListMap()[IdPicture];
      if (!Frame.isEmpty() )
      {
        albumart_found = true;
        for(TagLib::ID3v2::FrameList::ConstIterator iter = Frame.begin(); iter != Frame.end(); ++iter)
        {
          picture_frame = (TagLib::ID3v2::AttachedPictureFrame *)(*iter) ;
          {
            SIZE = picture_frame->picture().size() ;
            source_image = malloc ( SIZE ) ;
            if ( source_image )
            {
              memcpy ( source_image, picture_frame->picture().data(), SIZE ) ;
              fwrite(source_image,SIZE,1, image_file);
              fclose(image_file);
              free( source_image ) ;
            }

          }
        }
      }
    }
    else
    {
      cout<< "id3v2 not present";
    }
  }
  if(((string)file_location).substr(((string)file_location).find_last_of(".") + 1) == "m4a"){
    TagLib::MP4::File m4a_file(file_location);
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


      image_file = fopen(album_art_location.c_str(),"wb");

      SIZE = coverArt.data().size() ;
      source_image = malloc (SIZE) ;
      if (source_image)
      {
        memcpy ( source_image, coverArt.data().data(), SIZE ) ;
        fwrite(source_image,SIZE,1, image_file);
        fclose(image_file);
        free(source_image) ;
      }
    }
  }
  /*
  if(((string)file_location).substr(((string)file_location).find_last_of(".") + 1) == "ogg"){
  TagLib::Ogg::Vorbis::File ogg_file(file_location);
  TagLib::Ogg::XiphComment *ogg_tag = ogg_file.tag();
  TagLib::ByteVector ogg_byte = ogg_tag->render();
}
*/
//cout << "image data " << image_file << endl;
if (albumart_found == true){
  album_art->set(album_art_location.c_str());
  util::resize_image(album_art, width, height);
}
else {
  album_art->set(Glib::get_home_dir() + "/fidel/Resources/Icons/library-icons/blank-albumart-icon.svg");
  util::resize_image(album_art, width, height);
}
string clean_command = "rm -rf " + album_art_location;
system(clean_command.c_str());
return album_art;
}

string audioinfo::extract_album_art(char *file_location)
{
  audioinfo::init(file_location);
  //string album_art_location = "/home/tashrif/fidel/Album-Info/Album-Art/Hello,world!/コロニー.jpg";
  if (audioinfo::get_info("album") != "Unknown Album"){
    string album_art_location = Glib::get_home_dir() + "/fidel/Album-Info/Album-Art/" + audioinfo::get_info("album") + ".jpg";
    cout << "Album art location " << album_art_location << endl;
    //album_art_location = util::escape_spaces(album_art_location);

    cout << "Album art location " << album_art_location << endl;

    Gtk::Image null_tester;
    FILE *image_file;

    bool albumart_found = false;
    void *source_image;
    unsigned long SIZE;

    if(((string)file_location).substr(((string)file_location).find_last_of(".") + 1) == "flac"){
      TagLib::FLAC::File flac_file(file_location);
      const TagLib::List<TagLib::FLAC::Picture*>& picList = flac_file.pictureList();
      TagLib::FLAC::Picture* flac_cover_pic = new TagLib::FLAC::Picture();

      if (!picList.isEmpty()){
        flac_cover_pic = picList[0];
        albumart_found = true;
      }

      image_file = fopen(album_art_location.c_str(),"wb");

      SIZE = flac_cover_pic->data().size() ;
      source_image = malloc ( SIZE ) ;
      if ( source_image )
      {
        memcpy ( source_image, flac_cover_pic->data().data(), SIZE ) ;
        fwrite(source_image,SIZE,1, image_file);
        fclose(image_file);
        free( source_image ) ;
      }
    }
    if(((string)file_location).substr(((string)file_location).find_last_of(".") + 1) == "mp3"){
      static const char *IdPicture = "APIC" ;
      TagLib::MPEG::File mp3_file(file_location);
      TagLib::ID3v2::Tag *id3v2tag = mp3_file.ID3v2Tag();
      TagLib::ID3v2::FrameList Frame;
      TagLib::ID3v2::AttachedPictureFrame *picture_frame ;

      image_file = fopen(album_art_location.c_str(),"wb");

      if ( id3v2tag )
      {
        Frame = id3v2tag->frameListMap()[IdPicture];
        if (!Frame.isEmpty() )
        {
          albumart_found = true;
          for(TagLib::ID3v2::FrameList::ConstIterator iter = Frame.begin(); iter != Frame.end(); ++iter)
          {
            picture_frame = (TagLib::ID3v2::AttachedPictureFrame *)(*iter) ;
            {
              SIZE = picture_frame->picture().size() ;
              source_image = malloc ( SIZE ) ;
              if ( source_image )
              {
                memcpy ( source_image, picture_frame->picture().data(), SIZE ) ;
                fwrite(source_image,SIZE,1, image_file);
                fclose(image_file);
                free( source_image ) ;
              }

            }
          }
        }
      }
      else
      {
        cout<< "id3v2 not present";
      }
    }
    if(((string)file_location).substr(((string)file_location).find_last_of(".") + 1) == "m4a"){
      TagLib::MP4::File m4a_file(file_location);
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


        image_file = fopen(album_art_location.c_str(),"wb");

        SIZE = coverArt.data().size() ;
        source_image = malloc (SIZE) ;
        if (source_image)
        {
          memcpy ( source_image, coverArt.data().data(), SIZE ) ;
          fwrite(source_image,SIZE,1, image_file);
          fclose(image_file);
          free(source_image) ;
        }
      }
    }
    /*
    if(((string)file_location).substr(((string)file_location).find_last_of(".") + 1) == "ogg"){
    TagLib::Ogg::Vorbis::File ogg_file(file_location);
    TagLib::Ogg::XiphComment *ogg_tag = ogg_file.tag();
    TagLib::ByteVector ogg_byte = ogg_tag->render();
  }
  */
  //cout << "image data " << image_file << endl;
  if (albumart_found == true){
    cout << "Album art found -> " << album_art_location << endl;
    return album_art_location;
  }
  else {
    string clean_command = "rm -rf \"" + album_art_location + "\"";
    cout << "clean command " << clean_command << endl;
    system(clean_command.c_str());
    return "No Album Art";
  }
}
else {
  return "No Album Art";
}
}

Gtk::Image* audioinfo::get_extracted_album_art(char *file_location, int width, int height)
{
  return NULL;
}

vector<Gtk::Image*> audioinfo::get_all_album_art(int width, int height)
{
  vector<Gtk::Image*> all_album_art;
  vector<vector<Glib::ustring>> album_information = AudioLibrary::batch_collect_info("album_information");

  for (size_t iter = 0; iter < album_information.size(); iter++){
    Gtk::Image *album_art = new Gtk::Image();
    if (album_information[iter][ALBUM_ART_LOCATION] != "No Album Art"){
      album_art->set(album_information[iter][ALBUM_ART_LOCATION]);
      cout << "ALBUM ART LOCATIONS -> " << (album_information[iter])[ALBUM_ART_LOCATION] << endl;
      util::resize_image(album_art, width, height);
      all_album_art.push_back(album_art);
    }
  }
  return all_album_art;
}
