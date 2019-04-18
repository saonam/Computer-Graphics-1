#ifndef OVER_H
#define OVER_H
#include <vector>
// Compute C = A Over B, where A and B are semi-transparent rgba images and
// "Over" is the Porter-Duff Over operator
//
//
// Inputs:
//   A  width*height*4 array of 4-channel rgba instensities (i.e., rgb +
//     alpha channel for transparency)
//   B  width*height*4 array of 4-channel rgba instensities (i.e., rgb +
//     alpha channel for transparency)
//   width  image width (i.e., number of columns)
//   height  image height (i.e., number of rows)
// Outputs:
//   C  width*height*4 array of 4-channel rgba instensities (i.e., rgb +
//     alpha channel for transparency)
void over(
  const std::vector<unsigned char> & A,
  const std::vector<unsigned char> & B,
  const int & width,
  const int & height,
  std::vector<unsigned char> & C);
#endif
