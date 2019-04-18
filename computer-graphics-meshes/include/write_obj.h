#ifndef WRITE_OBJ_H
#define WRITE_OBJ_H
#include <Eigen/Core>
#include <string>
// Write a triangle or quad mesh to a .obj file
//
// Inputs:
//   filename  path to .obj file
//   V  #V by 3 list of vertex positions
//   F  #F by poly=(3 or 4) list of mesh face indices into V
//   UV  #UV by 2 list of UV positions
//   UF  #F by poly list of mesh face indices into UV
//   NV  #NV by 3 list of normal vectors
//   NF  #F by poly list of mesh face indices into NV
// Returns true if write was successful
bool write_obj(
  const std::string & filename,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const Eigen::MatrixXd & UV,
  const Eigen::MatrixXi & UF,
  const Eigen::MatrixXd & NV,
  const Eigen::MatrixXi & NF);
#endif 
