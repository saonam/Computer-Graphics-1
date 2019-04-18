#include "reflect.h"

void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
  reflected.resize(width*height*num_channels);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
  for (int h = 0; h<height; h++){
  	for(int w = 0; w<width; w++){
      if(num_channels == 1){
        reflected.at(h*width+w) = input.at(h*width+width-w-1);
      } else if(num_channels == 3){
  		  reflected.at(3*(h*width+w)) = input.at(3*(h*width+width-w-1));
  		  reflected.at(3*(h*width+w)+1) = input.at(3*(h*width+width-w-1)+1);
  		  reflected.at(3*(h*width+w)+2) = input.at(3*(h*width+width-w-1)+2);
      }
  	
    }
  }
}
