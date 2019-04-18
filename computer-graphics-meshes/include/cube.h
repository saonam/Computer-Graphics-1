#ifndef CUBE_H
#define CUBE_H
#include <Eigen/Core>

// Construct the quad mesh of a cube.
//
// Outputs:
//   V  8 by 3 list of 3D corner vertex positions
//   F  6 by 4 list of quad face indices into rows of V
//   UV  14 by 2 list of corner parameterization positions
//   UF  6 by 4 list of quad face indices into rows of UV
//   NV  6 by 4 list of 3D unit normal vectors
//   NF  6 by 4 list of quad face indices into rows of NV
void cube(
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF);

#endif
