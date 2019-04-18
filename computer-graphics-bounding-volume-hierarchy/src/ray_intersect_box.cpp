#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	// Intersect a ray with a **_solid_** box (careful: if the ray or `min_t` lands
	// _inside_ the box this could still hit something stored inside the box, so
	// this counts as a hit).
	//
	// Inputs:
	//   ray  ray to consider
	//   box  Axis-aligned solid box (presumably bounding some thing(s)
	//   min_t  minimum parameteric distance along ray to consider for hits
	//   max_t  maximum parameteric distance along ray to consider for hits
	// Returns true if ray intersects the box between min_t and max_t

	// 	#ifndef BOUNDING_BOX_H
	// #define BOUNDING_BOX_H
	// #include <Eigen/Core>

	// // Should change this name to AABB or AlignedBox
	// struct BoundingBox
	// {
	//   Eigen::RowVector3d min_corner;
	//   Eigen::RowVector3d max_corner;
	//   BoundingBox(
	//     Eigen::RowVector3d a_min_corner = 
	//       Eigen::RowVector3d::Constant(1,3, std::numeric_limits<double>::infinity()),
	//     Eigen::RowVector3d a_max_corner = 
	//       Eigen::RowVector3d::Constant(1,3,-std::numeric_limits<double>::infinity()))
	//     :
	//       min_corner(std::move(a_min_corner)),
	//       max_corner(std::move(a_max_corner))
	//   { }
	//   Eigen::RowVector3d center()
	//   {
	//     return 0.5*(max_corner + min_corner);
	//   }
	// };
	// #endif

	double x_direction = ray.direction(0);
	double y_direction = ray.direction(1);
	double z_direction = ray.direction(2);

	double origin_x_position = ray.origin(0);
	double origin_y_position = ray.origin(1);
	double origin_z_position = ray.origin(2);

	double box_x_max = box.max_corner(0);
	double box_x_min = box.min_corner(0);

	double box_y_max = box.max_corner(1);
	double box_y_min = box.min_corner(1);

	double box_z_max = box.max_corner(2);
	double box_z_min = box.min_corner(2);

	double t_xmax = 0;
	double t_xmin = 0;

	double temp_min_t = 0;
	double temp_max_t = 0;

	if(x_direction> 0 ){
		t_xmin = (box_x_min - origin_x_position)/x_direction;
		t_xmax = (box_x_max - origin_x_position)/x_direction;
	}
	else{
		t_xmax = (box_x_min - origin_x_position)/x_direction;
		t_xmin = (box_x_max - origin_x_position)/x_direction;
	}

	double t_ymax = 0;
	double t_ymin = 0;

	if(y_direction> 0 ){
		t_ymin = (box_y_min - origin_y_position)/y_direction;
		t_ymax = (box_y_max - origin_y_position)/y_direction;
	}
	else{
		t_ymax = (box_y_min - origin_y_position)/y_direction;
		t_ymin = (box_y_max - origin_y_position)/y_direction;
	}

	double t_zmax = 0;
	double t_zmin = 0;

	if(z_direction> 0 ){
		t_zmin = (box_z_min - origin_z_position)/z_direction;
		t_zmax = (box_z_max - origin_z_position)/z_direction;
	}
	else{
		t_zmax = (box_z_min - origin_z_position)/z_direction;
		t_zmin = (box_z_max - origin_z_position)/z_direction;
	}

	temp_min_t = std::max(std::max(t_xmin, t_ymin),t_zmin);
	temp_max_t = std::min(std::min(t_xmax, t_ymax),t_zmax);

	if(temp_max_t<temp_min_t){
		return false;
	}

	// Consider ray intersect box out side min_t to max_t interval
	if(temp_max_t < min_t || temp_min_t > max_t){
		return false;
	}


  return true;
  ////////////////////////////////////////////////////////////////////////////
}
