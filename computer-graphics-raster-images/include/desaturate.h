#ifndef DESATURATE_H
#define DESATURATE_H
#include <vector>
// Desaturate a given rgb color image by a given factor.
//
// Inputs:
//   rgb  width*height*3 array containing rgb image color intensities
//   width  image width (i.e., number of columns)
//   height  image height (i.e., number of rows)
//   factor  fractional amount of saturation to remove [0,1]
// Outputs:
//   desaturated  width*height*3 array containing rgb image color intensities
void desaturate(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double factor,
  std::vector<unsigned char> & desaturated);
#endif
