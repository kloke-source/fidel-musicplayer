#include <Spectrum/spectrum.h>
#include <gtkmm.h>
#include <iostream>
#include <math.h>
#include <Audio/playback.h>
#include <Utilities/util.h>
#define PI 3.14159265

//extern std::vector<double> phase_shifts;

spectrum::spectrum()
{
  for (size_t band = 0; band < spect_bands; band++) {
    shaders.push_back(0);
    previously_painted.push_back(0);
    bar_heights.push_back(0);
  }
  spectrum::init_connections();
}

spectrum::~spectrum() {}

void spectrum::init_connections()
{
  this->bands_updated_connection = audio_playback::Instance()->signal_spect_bands_updated().connect(sigc::mem_fun(this, &spectrum::on_spect_bands_updated));
  this->playback_status_changed_connection = audio_playback::Instance()->signal_status_changed().connect(sigc::mem_fun(this, &spectrum::on_playback_status_changed));
}

void spectrum::set_spect_bands(int bands)
{
  this->spect_bands = bands;
}

double spectrum::to_degree(double radian_val)
{
  return (radian_val * 180/PI);
}

double spectrum::to_radian(double degree_val)
{
  return (degree_val * PI/180);
}

double spectrum::sin_func(double value)
{
  double sin_val =  sin(value);
  sin_val = roundf(sin_val * 100) / 100;

  return sin_val;
}

void spectrum::start_visualization()
{
  this->visualization_connection = Glib::signal_timeout().connect(sigc::mem_fun(*this, &spectrum::on_timeout), 1);
}

void spectrum::stop_visualization()
{
  visualization_connection.disconnect();
}

void spectrum::clear_context(const Cairo::RefPtr<Cairo::Context>& cr)
{
  Gtk::Allocation allocation = get_allocation();
  const double frame_width = (double)allocation.get_width();
  const double frame_height = (double)allocation.get_height();

  if (auto_padding == true)
    spect_padding = (double) (.65 * frame_width) / (spect_bands + 1); // .65 is ideal padding ratio

  util::set_source_rgb(cr, "#dfdfdf");//2d2d2d
  cr->rectangle(0, 0, frame_width, frame_height);
  cr->fill();
  double spec_bar_width = (frame_width - ((spect_bands+1) * spect_padding))/spect_bands;
  util::set_source_rgb(cr, "#2d2d2d"); //dfdfdf
  //#36D7B7
  
  for (int band = 0; band < spect_bands; band++) {
    double bar_x_pos = spect_padding + (band * (spec_bar_width + spect_padding));
    cr->rectangle(bar_x_pos, (frame_height/2 - 1), spec_bar_width, 1);
  }
  cr->fill();
}

void spectrum::on_spect_bands_updated(std::vector<double> band_magnitudes)
{
  spect_band_magnitudes = band_magnitudes;
}

void spectrum::on_playback_status_changed(int playback_status)
{
  std::cout << "Status changed" << std::endl;
  if (playback_status == playback::PAUSED) {
    spectrum::stop_visualization();
    //spectrum::clear_context(paint_cairo);
  }
  if (playback_status == playback::PLAYING)
    spectrum::start_visualization();
}

//motion interpolation
//y=k*sin((1/k)*x - PI/2) + k Delta easing expression
//--> 0<=x<=(k*PI)
//--> y => (current position/target position) & y>=0
//--> k -> y/2 (scale factor)

//--> subdivision position = (n*k*PI)/s
//--> subdivision spacing = (k*PI)/s
//--> s = subdivisions/speed

bool spectrum::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  paint_cairo = this->get_window()->create_cairo_context();
  Gtk::Allocation allocation = get_allocation();

  double frame_width = allocation.get_width();
  double frame_height = allocation.get_height();

  if (auto_padding == true)
    spect_padding = (double) (.65 * frame_width) / (spect_bands + 1); // .65 is ideal padding ratio
  
  double spectrum_vert_scale = max_magnitude/frame_height;
  double spec_bar_width = (frame_width - ((spect_bands+1) * spect_padding))/spect_bands;

  if (paint_iter==0 && paint_decrement==true)
    paint_decrement = false;

  if (paint_iter == subdivisions){
    std::cout << "Decrement called" << std::endl;
    paint_decrement = true;
  }

  double scale_factor=frame_height/2;

  spectrum::clear_context(cr);
  util::set_source_rgb(cr, "#2d2d2d");
  //#pragma omp parallel for
  for (int band = 0; band < spect_band_magnitudes.size(); band++) {
    double magnitude = spect_band_magnitudes[band];
    double bar_x_pos = spect_padding + (band * (spec_bar_width + spect_padding));
    double height_required = frame_height - ( ((-1) * magnitude)/spectrum_vert_scale);
    
    double interp_x_pos = (shaders[band]*scale_factor*PI)/speed; //interpolation variables (the x position on the interpolation curve)
  
    double bar_height;
    if (scale_factor != 0 && audio_playback::Instance()->is_playing() == true)
      bar_height = scale_factor * spectrum::sin_func((1/scale_factor)*interp_x_pos - PI/2) + scale_factor; //interpolation variables
      
    if (audio_playback::Instance()->is_playing() == false)
      bar_height = previously_painted[band];
      
    bar_heights[band] = bar_height;

    if (previously_painted[band] < height_required && shaders[band] <= subdivisions)
      {
	shaders[band]++;
      }
    else if (shaders[band] == 0)
      shaders[band]++;
    else if (shaders[band] > 0)
      shaders[band]--;

    cr->rectangle(bar_x_pos, (frame_height/2 - bar_heights[band]/2), spec_bar_width, bar_heights[band]);
    previously_painted[band]=bar_height;
  }
  cr->fill();
  return true;
}

bool spectrum::on_timeout()
{
  Glib::RefPtr<Gdk::Window> win = get_window();
  if (win)
    {
      Gdk::Rectangle r(0, 0, get_allocation().get_width(),
		       get_allocation().get_height());
      win->invalidate_rect(r, false);
    }
  return true;
}
