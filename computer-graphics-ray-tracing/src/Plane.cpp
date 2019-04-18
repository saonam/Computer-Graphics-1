#include "Plane.h"
#include "Ray.h"

bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////

  // Replace with your code here:

	Eigen::Vector3d d;
	Eigen::Vector3d e;
	Eigen::Vector3d a;

	d = ray.direction;
	e = ray.origin;
	n = normal;
	a = point;
	if (d.dot(n) == 0) {
        return false;
    }
	double t_1 = (-(e-a).dot(n))/(d.dot(n));
	if(t_1<0){
		return false;
	} 
	else if(t_1>=0&&t_1<min_t){
		return false;
	} else{
		t = t_1;
	} 

	return true;

  ////////////////////////////////////////////////////////////////////////////
}

