#ifndef DEMOSAIC_H
#define DEMOSAIC_H
#include <vector>

// Given a mosaiced image (interleaved BGGR colors in a single channel), created
// a 3-channel rgb image.
//
// Inputs:
//   bayer  width*height array containing interleaved color intensities in
//     the GBRG bayer pattern.
//   width  image width (i.e., number of columns)
//   height  image height (i.e., number of rows)
// Outputs:
//   rgb  width*height*3 array containing rgb image color intensities


void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb);
#endif 
