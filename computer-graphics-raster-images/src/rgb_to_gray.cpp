#include "rgb_to_gray.h"

void rgb_to_gray(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  std::vector<unsigned char> & gray)
{
  gray.resize(height*width);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
  for(int h = 0; h<height; h++){
  	for(int w = 0; w<width; w++){
  		int gray_scale = 0;
  		int r = rgb.at(3*(h*width+w));
  		int g = rgb.at(3*(h*width+w)+1);
  		int b = rgb.at(3*(h*width+w)+2);
  		// reference: Assignment readme.
  		gray_scale = 0.2126*r+0.7152*g+0.0722*b;
  		gray.at(h*width+w) = gray_scale;
  	}
  }
}


