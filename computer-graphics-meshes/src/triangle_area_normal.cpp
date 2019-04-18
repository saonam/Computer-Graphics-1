#include "triangle_area_normal.h"
#include <Eigen/Geometry>

Eigen::RowVector3d triangle_area_normal(
  const Eigen::RowVector3d & a, 
  const Eigen::RowVector3d & b, 
  const Eigen::RowVector3d & c)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code:
	Eigen::RowVector3d l_1 = b - a;
	Eigen::RowVector3d l_2 = c - a;

	Eigen::RowVector3d norm = l_1.cross(l_2);

  ////////////////////////////////////////////////////////////////////////////
  return norm/2.0;
}