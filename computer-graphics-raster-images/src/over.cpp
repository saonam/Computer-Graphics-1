
#include "over.h"

void over(
  const std::vector<unsigned char> & A,
  const std::vector<unsigned char> & B,
  const int & width,
  const int & height,
  std::vector<unsigned char> & C)
{
    C.resize(A.size());
    
    int read1 = 0, read2 = 0, write = 0;
    // Reference: Chapter 3 of Fundamentals of Computer Graphics (4th Edition) 
    for (int h=0; h<height; h++) {
        for (int w=0; w<width; w++) {
            double A_r = A.at(4*(h*width+w)) / 255.0;
            double A_g = A.at(4*(h*width+w)+1) / 255.0;
            double A_b = A.at(4*(h*width+w)+2) / 255.0;
            double A_a = A.at(4*(h*width+w)+3) / 255.0;
            
            double B_r = B.at(4*(h*width+w)) / 255.0;
            double B_g = B.at(4*(h*width+w)+1) / 255.0;
            double B_b = B.at(4*(h*width+w)+2) / 255.0;
            double B_a = B.at(4*(h*width+w)+3) / 255.0;
            
            double Porter_Duff_a = 1.0 - (1.0 - A_a) * (1.0 - B_a);
            double Porter_Duff_r = ((A_a * A_r) + (1.0 - A_a) * B_a * B_r) / Porter_Duff_a;
            double Porter_Duff_g = ((A_a * A_g) + (1.0 - A_a) * B_a * B_g) / Porter_Duff_a;
            double Porter_Duff_b = ((A_a * A_b) + (1.0 - A_a) * B_a * B_b) / Porter_Duff_a;
	    // Poter/Duff composing.
    	    // This is Poter/Duff over operator
    	    // Reference: http://ssp.impulsetrain.com/porterduff.html
            C.at(4*(h*width+w)) = (unsigned char)((int)(Porter_Duff_r * 255.0));
            C.at(4*(h*width+w)+1) = (unsigned char)((int)(Porter_Duff_g * 255.0));
            C.at(4*(h*width+w)+2) = (unsigned char)((int)(Porter_Duff_b * 255.0));
            C.at(4*(h*width+w)+3) = (unsigned char)((int)(Porter_Duff_a * 255.0));
        }
    }
}
