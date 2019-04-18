#ifndef REFLECT_H
#define REFLECT_H

#include <vector>
// Horizontally reflect an image (like a mirror)
//
// Inputs:
//   input width*height*num_channels array containing image color intensities
//   width  image width (i.e., number of columns)
//   height  image height (i.e., number of rows)
//   num_channels  number of channels (e.g., for rgb 3, for grayscale 1)
// Outputs:
//   reflected  width*height*num_channels array containing reflected image
void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected);

#endif
