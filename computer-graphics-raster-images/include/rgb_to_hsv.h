#ifndef RGB_TO_HSV_H
#define RGB_TO_HSV_H

// Convert a color represented by red, green and blue intensities to its
// representation using hue, saturation and value.
//
// Inputs:
//   r  red intensity [0,1]
//   g  green intensity [0,1]
//   b  blue intensity [0,1]
// Outupts:
//   h  hue in degrees [0,360)
//   s  saturation intensity [0,1]
//   v  value intensity [0,1]
void rgb_to_hsv(
  const double r,
  const double g,
  const double b,
  double & h,
  double & s,
  double & v);
#endif
