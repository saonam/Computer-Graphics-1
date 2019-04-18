#ifndef SPHERE_H
#define SPHERE_H
#include <Eigen/Core>

// Construct a quad mesh of a sphere wth num_faces_u × num_faces_v faces
// using a latitude-longitude Mercator parameterization.
//
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
void sphere(
  const int num_faces_u,
  const int num_faces_v,
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF);

#endif

