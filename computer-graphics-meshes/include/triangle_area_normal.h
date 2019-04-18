#ifndef TRIANGLE_AREA_NORMAL_H
#define TRIANGLE_AREA_NORMAL_H
#include <Eigen/Core>
#include <vector>
// Compute the normal vector of a 3D triangle given its corner locations. The
// output vector should have length equal to the area of the triangle.
//
// Inputs:
//   a  3D position of the first corner as a **row vector**
//   b  3D position of the second corner as a **row vector**
//   c  3D position of the third corner as a **row vector**
// Returns the area normal of the triangle as a 3D row vector
Eigen::RowVector3d triangle_area_normal(
  const Eigen::RowVector3d & a, 
  const Eigen::RowVector3d & b, 
  const Eigen::RowVector3d & c);
#endif

