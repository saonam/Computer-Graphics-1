#include "demosaic.h"
#include <string>


// unsigned char compute(std::string corners_char, char c, std::vector<unsigned char> corners){
//   int count = 0;
//   double sum = 0;
//   for (int i=0;i<8;i++){
//     if (corners_char[i]==c){
//       sum += corners[i];
//       count ++;
//     }
//   }
//   return (unsigned char) ((int)(sum/count));
// }

void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(width*height*3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
  std::vector<std::vector<char>> bayerPattern = {{'g', 'b'}, {'r', 'g'}};
  // std::vector<std::string> full_bayerPattern = {"grgbbgrg", "rgrggrgr", "bgbggbgb", "gbgrrgbg"};

    for (int h=0; h<height; h++) {
        int pattern_row = h % 2;
        for (int w=0; w<width; w++) {
            double rtotal=0, gtotal=0, btotal=0;
            int rcount=0, gcount=0, bcount = 0;
            int pattern_col = w % 2;
            char color = bayerPattern[pattern_row][pattern_col];
            int pi = h,pj = w;

            // Loop for each pixel. 
            // Read all neighbors Bayer info.
            for (int i=pi-1;i<=pi+1;i++){
              for (int j= pj-1;j<=pj+1;j++){
                if (!(i==pi && j==pj)){
                  if (!(i<0 || j<0 || i>= height|| j>= width)){
                  // corners.push_back(bayer.at(i*width+j));
                    int y = i%2, x = j%2;
                    char neighcolor = bayerPattern[y][x];
                    if (neighcolor=='r'){
                      rtotal += bayer.at(j+i*width);
                      rcount++;
                    }
                    if (neighcolor == 'g'){
                      gtotal += bayer.at(j+i*width);
                      gcount++;
                    }
                    if (neighcolor == 'b'){
                      btotal += bayer.at(j+i*width);
                      bcount++;
                    }
                  }

                }
              }
            }
            // Take average 
            unsigned char r = (unsigned char) ((int)(rtotal/rcount));
            unsigned char g = (unsigned char) ((int)(gtotal/gcount));
            unsigned char b = (unsigned char) ((int)(btotal/bcount));

            // Convert bayer.ppm to RGB
            if (color == 'r') {
                rgb.at(3*(h*width+w)) = bayer.at(h*width+w);
                rgb.at(3*(h*width+w)+1) = g;
                rgb.at(3*(h*width+w)+2) = b;
            } else if (color == 'g') {
                rgb.at(3*(h*width+w)) = r;
                rgb.at(3*(h*width+w)+1) = bayer.at(h*width+w);
                rgb.at(3*(h*width+w)+2) = b;
            } else {
                rgb.at(3*(h*width+w)) = r;
                rgb.at(3*(h*width+w)+1) = g;
                rgb.at(3*(h*width+w)+2) = bayer.at(h*width+w);
            }
      }
  }
}

