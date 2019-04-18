#ifndef PER_VERTEX_NORMALS_H
#define PER_VERTEX_NORMALS_H
#include <Eigen/Core>
// Compute per vertex normals for a triangle mesh by computing the area-weighted
// average of normals at incident faces.
//
// Inputs:
//   V  #V by 3 list of vertex positions
//   F  #F by 3 list of mesh triangle indices into V
// Outputs:
//   N  #V by 3 list of per-face unit normal vectors
void per_vertex_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N);
#endif
