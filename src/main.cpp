//#include <gtk/gtk.h>
#include "GUI/gui.h"

//#include <gst/gst.h>
#include <gtkmm.h>
//#include <iostream>
//#include <Audio/playback.h>
#include <Utilities/util.h>
#include <Audio-Library/audio-library.h>

int main(int argc, char *argv[])
{
  //  fidel_ui::Instance()->initialize(argc, argv);
  AudioLibrary::scan_dir("/home/tashrif/Music/");
}
