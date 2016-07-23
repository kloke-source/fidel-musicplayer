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

audioinfo::audioinfo(){}
audioinfo::~audioinfo(){}

TagLib::FileRef audio_file;

char *audio_file_location;

struct AudioFileInfo{
  std::string song_name;
  //TagLib::String song_name;
  std::string artist;
  std::string album;
  double duration_seconds;
};

AudioFileInfo info;

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
  info.song_name = (audio_file.tag()->title()).to8Bit(true);
  info.artist = (audio_file.tag()->artist()).to8Bit(true);
  info.album = (audio_file.tag()->album()).to8Bit(true);
  info.duration_seconds = (audio_file.audioProperties()->length());

  //info.song_name = util::escape_slashes(info.song_name);
  //info.artist = util::escape_slashes(info.artist);
  //info.album = util::escape_slashes(info.album);

  if (info.song_name == "" || info.song_name == " "){
    //info.song_name = util::file_to_song_name(audio_file_location);
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

std::pair<guint8*, gsize> audioinfo::extract_album_art(std::string file_location)
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
  if (util::check_file_format(file_location, "mp3") == true) {
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
  
  if (util::check_file_format(file_location, "m4a") == true) {
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
    return std::make_pair(extracted_image, image_size);
  else
    return std::make_pair((guint8*)"No Album Art", NULL);
}
