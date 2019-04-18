#include "rgb_to_hsv.h"
#include <algorithm>
#include <functional>

void rgb_to_hsv(
  const double r,
  const double g,
  const double b,
  double & h,
  double & s,
  double & v)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  h = 0;
  s = 0;
  v = 0;
  double rgb_value[3] = {r, g, b};
  std::sort(rgb_value, rgb_value + 3, std::greater<double>());

  // reference: https://en.wikipedia.org/wiki/HSL_and_HSV#Conversion_RGB_to_HSL/HSV_used_commonly_in_software_programming
  double max = rgb_value[0];
  double min = rgb_value[2];
  double sub = max-min;
  if(max == min) h = 0;
  if(max == r && g>=b) h = 60*((g-b)/sub);
  if(max == r && g<b) h = 60*((g-b)/sub)+360;
  if(max == g) h = 60*((b-r)/sub) + 120;
  if(max == b) h = 60*((r-g)/sub) + 240;
  if(max == 0){
    s = 0;
  }else{
    s = sub/max;
  }
  v = max;
  ////////////////////////////////////////////////////////////////////////////
}
