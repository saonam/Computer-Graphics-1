#ifndef SIMULATE_BAYER_MOSAIC_H
#define SIMULATE_BAYER_MOSAIC_H

#include <vector>

// Simulate an image acquired from the Bayer mosaic by taking a 3-channel rgb
// image and creating a single channel grayscale image composed of interleaved
// red/green/blue channels. The output image should be the same size as the
// input but with a single channel.
//
// Inputs:
//   rgb  width*height*3 array containing rgb image color intensities
//   width  image width (i.e., number of columns)
//   height  image height (i.e., number of rows)
// Outputs:
//   bayer  width*height array containing interleaved color intensities in the
//     BGGR bayer pattern.
void simulate_bayer_mosaic(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<unsigned char> & bayer);

#endif
