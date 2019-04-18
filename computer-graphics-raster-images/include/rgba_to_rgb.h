#ifndef RGBA_TO_RGB_H
#define RGBA_TO_RGB_H

#include <vector>

// Extract the 3-channel rgb data from a 4-channel rgba image
//
// Inputs:
//   rgba  width*height*4 array of 4-channel rgba instensities (i.e., rgb +
//     alpha channel for transparency)
//   width  image width (i.e., number of columns)
//   height  image height (i.e., number of rows)
// Outputs:
//   rgb  width*height*3 array containing rgb image color intensities
//    
void rgba_to_rgb(
  const std::vector<unsigned char> & rgba,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb);

#endif
