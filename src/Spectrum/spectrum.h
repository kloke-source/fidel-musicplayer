#ifndef SPECTRUM
#define SPECTRUM
#include <GUI/singleton.h>
#include <gtkmm.h>

class spectrum : public Gtk::DrawingArea{
public:
  spectrum();
  ~spectrum();
  Gtk::Box *spectrumContainer;
  Gtk::Box *spectrumFrame;
  void init();
  void kill();
  void on_size_allocate(Gtk::Allocation allocation);
  void setBandMagn();
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
  int spec_bands = 35;
  //spectrum settings
  bool hault = false;
  int max_magnitude = 80;
  int padding       = 3;
  // end of spectrum settings;
  void clear(const Cairo::RefPtr<Cairo::Context>& cr);
protected:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
};
typedef Singleton<spectrum> spectrum_visualizer;
#endif
