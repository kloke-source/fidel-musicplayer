#include <Spectrum/spectrum.h>
#include <gtkmm.h>
#include <iostream>

spectrum::spectrum(){}
spectrum::~spectrum() {}

double smoothDef[64] = {0.8, 0.8, 1, 1, 0.8, 0.8, 1, 0.8, 0.8, 1, 1, 0.8,
  1, 1, 0.8, 0.6, 0.6, 0.7, 0.8, 0.8, 0.8, 0.8, 0.8,
  0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8,
  0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8,
  0.7, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6};
  double sum = 48.4;

  extern std::vector<double> band_magnitudes;
  extern std::vector<double> phase_shifts;

  void spectrum::init()
  {

  }

  void spectrum::kill()
  {
    delete this;
  }

  void spectrum::on_size_allocate(Gtk::Allocation allocation)
  {
    spectrum_frame_height = allocation.get_height();
    spectrum_vert_scale   = (double) max_magnitude/(spectrum_frame_height);
  }

Cairo::RefPtr<Cairo::Context> paintCairo;

  void spectrum::setBandMagn()
  {
    if (hault == false){
      spectrum::on_draw(paintCairo);
    }
  }

  void spectrum::pause()
  {
    hault = true;
  }

  void spectrum::play()
  {
    hault = false;
  }

  void spectrum::shrink(double percentage)
  {
    for (int iter=0; iter < 35; iter++){
      double magnitude    = spectrumBandMagn[iter];
      double paint_amount = spectrum_frame_height - (((-1) * magnitude)/spectrum_vert_scale);
      spectrumBand[iter]->set_size_request(0, (paint_amount * percentage));
    }
  }

  void spectrum::reset()
  {
    for (int iter=0; iter < 35; iter++){
      spectrumBand[iter]->set_size_request(0, 0);
    }
  }

  void spectrum::clear(const Cairo::RefPtr<Cairo::Context>& cr)
  {
    Gtk::Allocation allocation = get_allocation();
    const double width = (double)allocation.get_width();
    const double height = (double)allocation.get_height();

      cr->set_source_rgb(0, 0, 0);
      cr->rectangle(0, 0, width, height);
      cr->fill();
  }

  bool spectrum::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
  {
    paintCairo = this->get_window()->create_cairo_context();
    Gtk::Allocation allocation = get_allocation();
    const double width = (double)allocation.get_width();
    const double height = (double)allocation.get_height();

    double spectrum_vert_scale = max_magnitude/height;
    double spec_bar_width = (width - ((spec_bands+1) * padding))/spec_bands;

    spectrum::clear(cr);
    std::this_thread()
    for (size_t iter = 0; iter < band_magnitudes.size(); iter++) {
      double magnitude = band_magnitudes[iter];
      double bar_x_pos = padding + (iter * (spec_bar_width + padding));
      double bar_height = ((-1) * magnitude)/spectrum_vert_scale;
      std::cout << "Bar height " << bar_height << " band -> " << iter << std::endl;
      cr->set_source_rgb(0.21176, 0.8431, 0.7176);
      cr->rectangle(bar_x_pos, bar_height, spec_bar_width, height);
      cr->fill();
    }
    return true;
  }

  void spectrum::paint(guint band)
  {
    double magnitude    = spectrumBandMagn[band];
    double paint_amount = spectrum_frame_height - (((-1) * magnitude)/spectrum_vert_scale);
    spectrumBand[band]->set_size_request(0, paint_amount);
  }
