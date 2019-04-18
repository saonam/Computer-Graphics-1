#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>
#include <iomanip>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  assert(
    (num_channels == 3 || num_channels ==1 ) &&
    ".ppm only supports RGB or grayscale images");
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  std::ofstream ppmfile(filename);

  //ppmfile.open(filename, std::ios::out | std::ios::binary);
  // If open fails, return false.
  if(!ppmfile.is_open()){
   return false;
  }

  // Check number of channels to decide if ppm is RGB or gray
  if(num_channels == 3){
    ppmfile << "P3" <<"\n";
  }
  if(num_channels == 1){
    ppmfile << "P2" <<"\n";
  }
  
  ppmfile << width << " " << height <<"\n";
  ppmfile << "255" <<"\n";

  // write down all color information. 
  int count = 0;
  for (int h=0;h<height;h++){
    for (int w=0;w<width;w++){
      for (int i=0;i<num_channels;i++){
        int a = data.at(count);
        // printf("%d\n", data.at(count));
        ppmfile<<a;
        count++;
        if (i!=num_channels)
          ppmfile<<" ";
      }
      if (w!=width)
        ppmfile<<" ";
    }
    ppmfile<<"\n";
  }
  // if close fails, return false.
  ppmfile.close();
  if(!ppmfile){
    return false;
  }
  return true;
  ////////////////////////////////////////////////////////////////////////////
}
