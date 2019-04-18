#include "insert_triangle_into_box.h"

void insert_triangle_into_box(
  const Eigen::RowVector3d & a,
  const Eigen::RowVector3d & b,
  const Eigen::RowVector3d & c,
  BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
	// Grow a box `B` by inserting a triangle with corners `a`,`b`, and `c`.
//
// Inputs:
//   a  first corner position of the triangle
//   b  second corner position of the triangle
//   c  third corner position of the triangle
//   B  bounding box to be grown
// Outputs:
//   B  bounding box grown to include original contents and A
	B.max_corner(0) = std::max(B.max_corner(0), std::max(std::max(a(0), b(0)), c(0)));
	B.max_corner(1) = std::max(B.max_corner(1), std::max(std::max(a(1), b(1)), c(1)));
	B.max_corner(2) = std::max(B.max_corner(2), std::max(std::max(a(2), b(2)), c(2)));
	B.min_corner(0) = std::min(B.min_corner(0), std::min(std::min(a(0), b(0)), c(0)));
	B.min_corner(1) = std::min(B.min_corner(1), std::min(std::min(a(1), b(1)), c(1)));
	B.min_corner(2) = std::min(B.min_corner(2), std::min(std::min(a(2), b(2)), c(2)));
}


