#include "hsv_to_rgb.h"
#include <cmath>

void hsv_to_rgb(
  const double h,
  const double s,
  const double v,
  double & r,
  double & g,
  double & b)
{
    // Reference: https://en.wikipedia.org/wiki/HSL_and_HSV#Converting_to_RGB
    

    double c = v * s;
    double h_i = std::fmod(h / 60.0, 6.0);
    double x = c*(1.0-std::abs(std::fmod(h_i, 2.0)-1.0));
    double temp_r, temp_g, temp_b;

    if (0.0 <= h_i && h_i < 1.0) {
        temp_r = c;
        temp_g = x;
        temp_b = 0.0;
    } 
    else if (1.0 <= h_i && h_i < 2.0) {
        temp_r = x;
        temp_g = c;
        temp_b = 0.0;
    } 
    else if (2.0 <= h_i && h_i < 3.0) {
        temp_r = 0.0;
        temp_g = c;
        temp_b = x;
    } 
    else if (3.0 <= h_i && h_i < 4.0) {
        temp_r = 0.0;
        temp_g = x;
        temp_b = c;
    } 
    else if (4.0 <= h_i && h_i < 5.0) {
        temp_r = x;
        temp_g = 0.0;
        temp_b = c;
    } 
    else if (5.0 <= h_i && h_i < 6.0) {
        temp_r = c;
        temp_g = 0.0;
        temp_b = x;
    } 
    else {
        temp_r = 0.0;
        temp_g = 0.0;
        temp_b = 0.0;
    }
    
    double m = v - c;

    r = temp_r + m;
    g = temp_g + m;
    b = temp_b + m;
}