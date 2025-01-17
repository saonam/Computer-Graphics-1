#include "hue_shift.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"


void hue_shift(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double shift,
  std::vector<unsigned char> & shifted)
{
  shifted.resize(rgb.size());
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////

  // Reference: https://en.wikipedia.org/wiki/Hue#Computing_hue
  for(int hei = 0; hei<height; hei++){
  	for(int w = 0; w<width; w++){
  		double h=0;
  		double s=0;
  		double v=0;
  		double r = rgb.at(3*(hei*width+w))/255.0;
  		double g = rgb.at(3*(hei*width+w)+1)/255.0;
  		double b = rgb.at(3*(hei*width+w)+2)/255.0;
  		rgb_to_hsv(r,g,b,h,s,v);
  		h = h - shift;
  		while(h>=360){
			h = h-360;
		}
		while(h<0){
			h = h+360;
		}
  		hsv_to_rgb(h, s, v, r, g, b);
  		shifted.at(3*(hei*width+w)) = (unsigned char)(int)(r*255.0);
  		shifted.at(3*(hei*width+w)+1) = (unsigned char)(int)(g*255.0);
  		shifted.at(3*(hei*width+w)+2) = (unsigned char)(int)(b*255.0);

  	}
  }
}
