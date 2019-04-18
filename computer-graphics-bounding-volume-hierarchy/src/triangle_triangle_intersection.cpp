#include "triangle_triangle_intersection.h"
#include "Ray.h"
#include "ray_intersect_triangle.h"


bool triangle_triangle_intersection(
  const Eigen::RowVector3d & A0,
  const Eigen::RowVector3d & A1,
  const Eigen::RowVector3d & A2,
  const Eigen::RowVector3d & B0,
  const Eigen::RowVector3d & B1,
  const Eigen::RowVector3d & B2)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  ////////////////////////////////////////////////////////////////////////////

  // For triangle intersection, thinking of one edge of triangle is intersect with another triangle. 

    double dummy_t;
    // Ray first_triangle_a;
    // first_triangle_a.origin = A0;
    // first_triangle_a.direction = A1-A0;
    // Ray first_triangle_b;
    // first_triangle_b.origin = A1;
    // first_triangle_b.direction = A2-A1;
    // Ray first_triangle_c;
    // first_triangle_c.origin = A2;
    // first_triangle_c.direction = A0-A2;

    // Ray second_triangle_a;
    // second_triangle_a.origin = B0;
    // second_triangle_a.direction = B1-B0;
    // Ray second_triangle_b;
    // second_triangle_b.origin = B1;
    // second_triangle_b.direction = B2-B1;
    // Ray second_triangle_c;
    // second_triangle_c.origin = B2;
    // second_triangle_c.direction = B0-B2;

    if (ray_intersect_triangle(Ray(A0, A1-A0), B0, B1, B2, 0, 1, dummy_t)||
        ray_intersect_triangle(Ray(A1, A2-A1), B0, B1, B2, 0, 1, dummy_t)||
        ray_intersect_triangle(Ray(A2, A0-A2), B0, B1, B2, 0, 1, dummy_t)||
        ray_intersect_triangle(Ray(B0, B1-B0), A0, A1, A2, 0, 1, dummy_t)||
        ray_intersect_triangle(Ray(B1, B2-B1), A0, A1, A2, 0, 1, dummy_t)||
        ray_intersect_triangle(Ray(B2, B0-B2), A0, A1, A2, 0, 1, dummy_t)) 
    {
        return true;
    }
    return false;
}
