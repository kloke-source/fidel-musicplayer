#ifndef SPECTRUM_HH
#define SPECTRUM_HH
#include <gtkmm.h>
#include <vector>
#include <GUI/singleton.h>
#include <Utilities/util.h>

class spectrum : public Gtk::DrawingArea{
 public:
  spectrum();
  ~spectrum();
  
  void init_connections();
  void start_visualization();
  void stop_visualization();
  void set_spect_bands(int bands);
 private:
  // variables
  int spect_bands = 250;
  
  double spect_padding;
  double spect_padding_top = .02; // 2% this padding is only applied if a spectrum bar reaches the height of the spectrum frame
  double max_magnitude = 80;  

  bool auto_padding = true;

  // interpolation variables

  int paint_iter=0;
  bool paint_decrement=false;
  int speed = 100;
  int subdivisions=speed;

  Cairo::RefPtr<Cairo::Context> paint_cairo;

  std::vector<int> shaders;
  std::vector<double> spect_band_magnitudes;
  std::vector<double> previously_painted;
  std::vector<double> bar_heights;

  // functions
  void clear_context(const Cairo::RefPtr<Cairo::Context>& cr);
  
  //Utility functions
  double to_degree(double radian_val);
  double to_radian(double degree_val);
  double sin_func(double value);

  // sigc connections
  sigc::connection visualization_connection;  
  sigc::connection bands_updated_connection;
  sigc::connection playback_status_changed_connection;
  
 protected:
  // signal handlers
  void on_spect_bands_updated(std::vector<double> band_magnitudes);
  void on_playback_status_changed(int playback_status);
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
  bool on_timeout();
};
#endif
