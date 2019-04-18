#include "rotate.h"

void rotate(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & rotated)
{
  rotated.resize(height*width*num_channels);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
  for (int w=0; w<width; w++){
  	for(int h=0; h<height; h++){

  		// Rotate here just make columns starts from right as row starts from top. 
      if(num_channels == 1){
        rotated.at(h*width+w) = input.at(width*h+width-w-1);
      }
      else if(num_channels == 3){
  		  rotated.at(3*(w*height+h)) = input.at(3*(width*h+width-w-1));
  		  rotated.at(3*(w*height+h)+1) = input.at(3*(width*h+width-w-1)+1);
  		  rotated.at(3*(w*height+h)+2) = input.at(3*(width*h+width-w-1)+2);
  	   }
    }
  }
}
