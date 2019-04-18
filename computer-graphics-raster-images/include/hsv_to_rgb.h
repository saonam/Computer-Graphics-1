#ifndef HSV_TO_RGB_H
#define HSV_TO_RGB_H

// Convert a color represented by hue, saturation and value to its
// representation using red, green and blue intensities.
//
// Inputs:
//   h  hue in degrees [0,360)
//   s  saturation intensity [0,1]
//   v  value intensity [0,1]
// Outupts:
//   r  red intensity [0,1]
//   g  green intensity [0,1]
//   b  blue intensity [0,1]
void hsv_to_rgb(
  const double h,
  const double s,
  const double v,
  double & r,
  double & g,
  double & b);
#endif
