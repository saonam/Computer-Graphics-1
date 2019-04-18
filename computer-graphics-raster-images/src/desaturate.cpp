#include "desaturate.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void desaturate(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double factor,
  std::vector<unsigned char> & desaturated)
{
  desaturated.resize(rgb.size());
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////

  // Reference : https://en.wikipedia.org/wiki/HSL_and_HSV#Saturation
  for(int hei = 0; hei<height; hei++){
  	for(int w = 0; w<width; w++){
  		double h=0;
  		double s=0;
  		double v=0;
  		double r = rgb.at(3*(hei*width+w))/255.0;
  		double g = rgb.at(3*(hei*width+w)+1)/255.0;
  		double b = rgb.at(3*(hei*width+w)+2)/255.0;
  		rgb_to_hsv(r,g,b,h,s,v);
  		s = s * (1-factor);
  		hsv_to_rgb(h, s, v, r, g, b);
  		desaturated.at(3*(hei*width+w)) = (unsigned char)(int)(r*255.0);
  		desaturated.at(3*(hei*width+w)+1) = (unsigned char)(int)(g*255.0);
  		desaturated.at(3*(hei*width+w)+2) = (unsigned char)(int)(b*255.0);

  	}
  }

}
