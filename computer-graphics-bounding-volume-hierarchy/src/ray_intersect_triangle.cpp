#include "ray_intersect_triangle.h"

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // Intersect a ray with a triangle
  //
  // Inputs:
  //   ray  ray to consider
  //   A  first triangle corner position
  //   B  second triangle corner position
  //   C  third triangle corner position
  //   min_t  minimum parameteric distance along ray to consider for hits
  //   max_t  maximum parameteric distance along ray to consider for hits
  // Outputs:
  //   t  parametric distance along ray to hit
  // Returns true if ray intersects the triangle between min_t and max_t

  Eigen::RowVector3d first_column = A - B;
  Eigen::RowVector3d second_column = A - C;

  double a = first_column[0];
  double b = first_column[1];
  double c = first_column[2];

  double d = second_column[0];
  double e = second_column[1];
  double f = second_column[2];

  double g = ray.direction[0];
  double h = ray.direction[1];
  double i = ray.direction[2];

  double j = A[0]-ray.origin[0];
  double k = A[1]-ray.origin[1];
  double l = A[2]-ray.origin[2];

  double M = a*(e*i - h*f) + b*(g*f - d*i) + c*(d*h - e*g);

  double beta = (j*(e*i - h*f) + k*(g*f - d*i) + l*(d*h - e*g))/M;
  double gamma = (i*(a*k - j*b) + h*(j*c - a*l) + g*(b*l - k*c))/M;
  double temp_t = -(f*(a*k - j*b) + e*(j*c - a*l) + d*(b*l - k*c))/M;

  if(temp_t<min_t || temp_t>=max_t){
    return false;
  } else if(gamma<0 || gamma>1){
    return false;
  } else if(beta<0 || beta>(1-gamma)){
    return false;
  } else {
    t = temp_t;
    
    return true;
  }
  ////////////////////////////////////////////////////////////////////////////
}
