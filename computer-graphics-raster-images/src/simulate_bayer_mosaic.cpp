#include "simulate_bayer_mosaic.h"

void simulate_bayer_mosaic(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<unsigned char> & bayer)
{
  bayer.resize(width*height);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
  // the bayer mosaic pattern used:
    // g b
    // r g
    std::vector<std::vector<char>> bayerPattern = {{'g', 'b'}, {'r', 'g'}};
    int count = 0;
    for (int h=0; h<height; h++) {
        int pattern_row = h % 2;
        for (int w=0; w<width; w++) {
            int pattern_col = w % 2;
            // check current pixel related bayer cell. 
            char color = bayerPattern[pattern_row][pattern_col];
            
            // write down color 
            if (color == 'r') {
                bayer.at(h*width+w) = rgb.at(3*(h*width+w));
            } else if (color == 'g') {
                bayer.at(h*width+w) = rgb.at(3*(h*width+w)+1);
            } else {
                bayer.at(h*width+w) = rgb.at(3*(h*width+w)+2);
            }
    	}
	}
}
