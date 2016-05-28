#ifndef SPECTRUM
#define SPECTRUM
#include <GUI/singleton.h>
#include <gtkmm.h>

class spectrum{
public:
  spectrum();
  ~spectrum();
  Gtk::Box *spectrumContainer;
  Gtk::Box *spectrumFrame;
  void init();
  void kill();
  void on_size_allocate(Gtk::Allocation allocation);
  void setBandMagn(guint band, gfloat magnitude, gfloat phase_shift);
  void shrink(double percentage);
  void reset();
  void pause();
  void play();
private:
  void paint(guint band);


  //spectrum features
  Gtk::Box *spectrum_layout[35];
  Gtk::Box *spectrumBand[35];
  int spectrum_frame_height;
  double spectrum_vert_scale;
  double spectrumBandMagn[35];
  // end of spectrum features

  //spectrum settings
  bool hault = false;
  int max_magnitude = 80;
  int padding       = 3;
  // end of spectrum settings;

};
typedef Singleton<spectrum> spectrum_visualizer;
#endif
