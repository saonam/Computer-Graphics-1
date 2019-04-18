#ifndef READ_RGBA_FROM_PNG_H
#define READ_RGBA_FROM_PNG_H

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <string>
#include <vector>
inline bool read_rgba_from_png(
  const std::string & filename,
  std::vector<unsigned char> & rgba,
  int & width,
  int & height)
{
  // read a RGBA .png
  int n;
  unsigned char * rgba_raw = stbi_load(filename.c_str(),&width,&height,&n,4);
  if(rgba_raw == NULL)
  {
    return false;
  }
  // copy into vector
  rgba.reserve(height*width*4);
  std::copy(rgba_raw,rgba_raw+height*width*4,std::back_inserter(rgba) );
  return true;
}

#endif
