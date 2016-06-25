#ifndef SPECTRUM
#define SPECTRUM
#include <gtkmm.h>
#include <GUI/singleton.h>
#include <Utilities/util.h>

class spectrum : public Gtk::DrawingArea{
public:
  spectrum();
  ~spectrum();
  void start_visualization();
  void stop_visualization();
private:
  void clear_context(const Cairo::RefPtr<Cairo::Context>& cr);
  //Utility functions
  double to_degree(double radian_val);
  double to_radian(double degree_val);
  double sin_func(double value);
protected:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
  bool on_timeout();
};
typedef Singleton<spectrum> spectrum_visualizer;
#endif
