#include "sphere.h"
#include <iostream>
#include <cmath>
#include <math.h>
#define _USE_MATH_DEFINES

void sphere(
  const int num_faces_u,
  const int num_faces_v,
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{

    V.resize((num_faces_u+1)*(num_faces_v+1), 3);
    UV.resize((num_faces_u+1)*(num_faces_v+1), 2);
    NV.resize((num_faces_u+1)*(num_faces_v+1), 3);
    F.resize(num_faces_u*num_faces_v, 4);
    UF.resize(num_faces_u*num_faces_v, 4);
    NF.resize(num_faces_u*num_faces_v, 4);
    
// Construct a quad mesh of a sphere wth num_faces_u × num_faces_v faces
// using a latitude-longitude Mercator parameterization.

// Inputs:
//   num_faces_u  number of faces in the longitudinal direction
//   num_faces_v  number of faces in the latitudinal direction
// Outputs:
//   V  #V by 3 list of 3D corner vertex positions
//   F  #F by 4 list of quad face indices into rows of V
//   UV  #UV by 2 list of corner parameterization positions
//   UF  #F by 4 list of quad face indices into rows of UV
//   NV  #NV  by 3 list of 3D unit normal vectors
//   NF  #F by 4 list of quad face indices into rows of NV
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
    // printf("%f\n", M_PI);
    for(int i = 0; i<=num_faces_u; i++){
        for(int j = 0; j<=num_faces_v; j++){

            int idx = i*(num_faces_v+1) + j;
            double u = ((double)i/num_faces_u - 0.5)*((2*M_PI));  //lon
            double v = ((double)j/num_faces_v - 0.5)*((M_PI));    //lat

            double x = cos(u)*cos(v);
            double y = sin(u)*cos(v);
            double z = sin(v);

            V.row(idx) = Eigen::RowVector3d(x, y, z);
            UV.row(idx) = Eigen::RowVector2d((double)i/num_faces_u, (double)j/num_faces_v);
            NV.row(idx) = Eigen::RowVector3d(x, y, z);
        }
    }

    int index = 0;
    for (int i=0; i<num_faces_u; i++) {
        for (int j=0; j<num_faces_v; j++) {
            const int idx1 = i*(num_faces_v+1)+j;
            const int idx2 = idx1+1;
            const int idx3 = (i+1)*(num_faces_v+1)+j;
            const int idx4 = idx3+1;
            F.row(index) = Eigen::RowVector4i(idx1, idx3, idx4, idx2);
            UF.row(index) = Eigen::RowVector4i(idx1, idx3, idx4, idx2);
            NF.row(index) = Eigen::RowVector4i(idx1, idx3, idx4, idx2);
            index++;
        }
    }
  ////////////////////////////////////////////////////////////////////////////
}