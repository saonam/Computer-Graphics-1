#include "read_rgba_from_png.h"
#include "rgba_to_rgb.h"
#include "rgb_to_gray.h"
#include "reflect.h"
#include "rotate.h"
#include "write_ppm.h"
#include "over.h"
#include "simulate_bayer_mosaic.h"
#include "desaturate.h"
#include "hue_shift.h"
#include "demosaic.h"

#include <vector>
#include <iostream>

int main(int argc, char *argv[])
{
  char ** input_filenames = argv+1;
  int num_inputs = argc-1;
  if(num_inputs == 0)
  {
    const char * default_input_file_names[] = {
      "../data/dog.png",
      "../data/glasses.png",
      "../data/laser-beams.png",
      "../data/sparkles.png"
    };
    input_filenames = const_cast<char **>(default_input_file_names);
    num_inputs = 4;
  }

  // read a RGBA .png
  int width,height;
  std::vector<unsigned char> rgba;
  read_rgba_from_png(input_filenames[0],rgba,width,height);

  // Convert to RGB
  std::vector<unsigned char> rgb;
  rgba_to_rgb(rgba,width,height,rgb);

  // Write to .ppm file format
  write_ppm("rgb.ppm",rgb,width,height,3);

  // Reflection
  std::vector<unsigned char> reflected;
  reflect(rgb,width,height,3,reflected);
  write_ppm("reflected.ppm",reflected,width,height,3);

  // Rotation
  std::vector<unsigned char> rotated;
  rotate(rgb,width,height,3,rotated);
  write_ppm("rotated.ppm",rotated,height,width,3);

  // Convert to gray
  std::vector<unsigned char> gray;
  rgb_to_gray(rgb,width,height,gray);
  write_ppm("gray.ppm",gray,width,height,1);

  // Create fake bayer mosaic image
  std::vector<unsigned char> bayer;
  simulate_bayer_mosaic(rgb,width,height,bayer);
  write_ppm("bayer.ppm",bayer,width,height,1);

  // Demosaic that output
  std::vector<unsigned char> demosaicked;
  demosaic(bayer,width,height,demosaicked);
  write_ppm("demosaicked.ppm",demosaicked,width,height,3);

  // Shift the hue of the image by 180°
  std::vector<unsigned char> shifted;
  hue_shift(rgb,width,height,180.0,shifted);
  write_ppm("shifted.ppm",shifted,width,height,3);

  // Partially desaturate an image by 25%
  std::vector<unsigned char> desaturated;
  desaturate(rgb,width,height,0.25,desaturated);
  write_ppm("desaturated.ppm",desaturated,width,height,3);

  // Alpha composite multiple images (if present)
  std::vector<unsigned char> composite_rgba;
  read_rgba_from_png(input_filenames[0],composite_rgba,width,height);
  for(int f = 1;f<num_inputs;f++)
  {
    std::vector<unsigned char> next_rgba;
    int next_height,next_width;
    read_rgba_from_png(input_filenames[f],next_rgba,next_width,next_height);
    assert(height == next_height && "height must match");
    assert(width == next_width && "width must match");
    over(next_rgba,composite_rgba,width,height,composite_rgba);
  }
  std::vector<unsigned char> composite;
  rgba_to_rgb(composite_rgba,width,height,composite);
  write_ppm("composite.ppm",composite,width,height,3);
}
