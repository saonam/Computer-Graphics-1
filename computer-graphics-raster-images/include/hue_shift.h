#ifndef HUE_SHIFT_H
#define HUE_SHIFT_H
#include <vector>
// Shift the hue of a color rgb image.
//
// Inputs:
//   rgb  width*height*3 array containing rgb image color intensities
//   width  image width (i.e., number of columns)
//   height  image height (i.e., number of rows)
//   shift  hue shift given in degrees [-180,180)
// Outputs
//   shifted  width*height*3 array containing rgb image color intensities
void hue_shift(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double shift,
  std::vector<unsigned char> & shifted);
#endif
