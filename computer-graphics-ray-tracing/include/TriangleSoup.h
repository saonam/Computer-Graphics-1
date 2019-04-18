#ifndef TRIANGLE_SOUP_H
#define TRIANGLE_SOUP_H

#include "Object.h"
#include <Eigen/Core>
#include <memory>
#include <vector>

// Forward declaration
class Triangle;
class TriangleSoup : public Object
{
  public:
    // A soup is just a set (list) of triangles
    std::vector<std::shared_ptr<Object> > triangles;

    // Intersect a triangle soup with ray.
    //
    // Inputs:
    //   Ray  ray to intersect with
    //   min_t  minimum parametric distance to consider
    // Outputs:
    //   t  first intersection at ray.origin + t * ray.direction
    //   n  surface normal at point of intersection
    // Returns iff there a first intersection is found.
    bool intersect(
      const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const;
};

#endif

