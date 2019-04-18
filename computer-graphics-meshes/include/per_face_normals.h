#ifndef PER_FACE_NORMALS_H
#define PER_FACE_NORMALS_H
#include <Eigen/Core>
// Compute per-face normals for a triangle mesh
//
// Inputs:
//   V  #V by 3 list of vertex positions
//   F  #F by 3 list of mesh triangle indices into V
// Outputs:
//   N  #F by 3 list of per-face unit normal vectors
void per_face_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N);
#endif

