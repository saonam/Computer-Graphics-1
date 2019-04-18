#ifndef RGB_TO_GRAY_H
#define RGB_TO_GRAY_H

#include <vector>

// Convert a 3-channel RGB image to a 1-channel grayscale image
//
// Inputs:
//   rgb  width*height*3 array containing rgb image color intensities
//   width  image width (i.e., number of columns)
//   height  image height (i.e., number of rows)
// Outputs:
//   gray  width*height array containing grayscale intensities
void rgb_to_gray(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  std::vector<unsigned char> & gray);

#endif
