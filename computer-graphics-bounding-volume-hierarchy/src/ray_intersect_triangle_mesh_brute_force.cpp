#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"
#include <iostream>

bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // Shoot a ray at a triangle mesh with $n$ faces and record the closest hit. Use
  // a brute force loop over all triangles, aim for O(n) complexity but focus on
  // correctness. This will be your reference solution.

  // Inputs:
  //   ray  ray being shot
  //   V  #V by 3 list of mesh vertex positions
  //   F  #F by 3 list of triangle indices into rows of V
  //   min_t  minimum parametric distance along ray to consider 
  //   max_t  maximum parametric distance along ray to consider 
  // Outputs:
  //   hit_t  parameteric distance of hit along ray
  //   hit_f  index into F of triangle that was hit
  // Returns true iff a valid hit was recorded
  int num_triangles = F.rows();
  bool if_find = false;
  int temp_f = 0;
  double temp_t = std::numeric_limits<double>::infinity();
  
  // Loop all triangles
  for(int i = 0; i<num_triangles; i++){

    Eigen::RowVector3d A = V.row(F(i, 0));
    Eigen::RowVector3d B = V.row(F(i, 1));
    Eigen::RowVector3d C = V.row(F(i, 2));
    double current_t = 0;
    
    bool if_intersect = ray_intersect_triangle(ray, A, B, C, min_t, max_t, current_t);

    if(if_intersect){
      // Get closest triangle
      if(current_t < temp_t){
        if_find = true;
        temp_t = current_t;
        temp_f = i;
      }
    }
  }

  if(if_find){
    hit_t = temp_t;
    hit_f = temp_f;
    return true;
  }
  
  return false;
  ////////////////////////////////////////////////////////////////////////////
}
