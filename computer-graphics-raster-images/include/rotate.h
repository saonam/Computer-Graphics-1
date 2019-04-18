#ifndef ROTATE_H
#define ROTATE_H

#include <vector>
// Rotate an image 90°  counter-clockwise
//
// Inputs:
//   input width*height*num_channels array containing image color intensities
//   width  image width (i.e., number of columns)
//   height  image height (i.e., number of rows)
//   num_channels  number of channels (e.g., for rgb 3, for grayscale 1)
// Outputs:
//   rotated height*width*num_channels array containing rotated image
void rotate(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & rotated);

#endif
