#include "insert_box_into_box.h"
#include <iostream>

void insert_box_into_box(
  const BoundingBox & A,
  BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
	// Grow a box `B` by inserting a box `A`.
	//
	// Inputs:
	//   A  bounding box to be inserted
	//   B  bounding box to be grown
	// Outputs:
	//   B  bounding box grown to include original contents and A
	B.max_corner(0) = std::max(B.max_corner(0), A.max_corner(0));
	B.max_corner(1) = std::max(B.max_corner(1), A.max_corner(1));
	B.max_corner(2) = std::max(B.max_corner(2), A.max_corner(2));
	B.min_corner(0) = std::min(B.min_corner(0), A.min_corner(0));
	B.min_corner(1) = std::min(B.min_corner(1), A.min_corner(1));
	B.min_corner(2) = std::min(B.min_corner(2), A.min_corner(2));
}

