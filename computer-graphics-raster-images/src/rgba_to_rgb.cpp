#include "rgba_to_rgb.h"

void rgba_to_rgb(
  const std::vector<unsigned char> & rgba,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(height*width*3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
  int size = height*width*3; 
  int rgba_count = 0;
  // for rgba, every four element, delete last one. 
  for(int i=0; i<size; i++){
  	rgb.at(i) = rgba.at(rgba_count);
  	rgba_count++;
  	if((i+1)%3==0) rgba_count++;
  }

}
