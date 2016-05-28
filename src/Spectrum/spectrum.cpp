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

void spectrum::init()
{
  spectrumFrame = new Gtk::Box(Gtk::ORIENTATION_VERTICAL);
  spectrumContainer = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 3);
  for (int count = 0; count < 35; count++){
    spectrum_layout[count] =  new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0);
    spectrumBand[count] = new Gtk::Box();
    spectrumBand[count]->override_background_color(Gdk::RGBA("#36D7B7"));
    spectrumBand[count]->set_size_request(0, 0);
    spectrum_layout[count]->pack_start(*spectrumBand[count], Gtk::PACK_EXPAND_PADDING);
    spectrumContainer->pack_start(*spectrum_layout[count], Gtk::PACK_EXPAND_WIDGET);
    spectrum_layout[count]->show();
    spectrumBand[count]->show();
  }
  spectrumContainer->override_background_color(Gdk::RGBA("#333333"));
  spectrumFrame->pack_start(*spectrumContainer, Gtk::PACK_EXPAND_WIDGET);
  spectrumContainer->set_resize_mode(Gtk::RESIZE_QUEUE);
  spectrumFrame->set_resize_mode(Gtk::RESIZE_QUEUE);
  spectrumContainer->show();
  spectrum::spectrumContainer->signal_size_allocate().connect(sigc::mem_fun(this, &spectrum::on_size_allocate));
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

void spectrum::setBandMagn(guint band, gfloat magnitude, gfloat phase_shift)
{
  if (hault == false){
    spectrumBandMagn[band]=(double)(magnitude);
    spectrum::paint(band);
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

void spectrum::paint(guint band)
{
  double magnitude    = spectrumBandMagn[band];
  double paint_amount = spectrum_frame_height - (((-1) * magnitude)/spectrum_vert_scale);
  spectrumBand[band]->set_size_request(0, paint_amount);
}
