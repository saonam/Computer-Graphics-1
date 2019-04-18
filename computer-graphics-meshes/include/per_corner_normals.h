#ifndef PER_CORNER_NORMALS_H
#define PER_CORNER_NORMALS_H
#include <Eigen/Core>
// Compute per corner normals for a triangle mesh by computing the area-weighted
// average of normals at incident faces whose normals deviate less than the
// provided threshold.
//
// Inputs:
//   V  #V by 3 list of vertex positions
//   F  #F by 3 list of mesh triangle indices into V
//   corner_threshold  threshold in degrees on sharp angles
// Outputs:
//   N  #F*3 by 3 list of mesh vertex 3D normals, where the normal
//     for corner F(i,j) is at N.row(i*3+j)
void per_corner_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double corner_threshold,
  Eigen::MatrixXd & N);
#endif

