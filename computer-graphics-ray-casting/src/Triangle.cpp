#include "Triangle.h"
#include "Ray.h"
#include <iostream>
#include <Eigen/Geometry>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:


	// Ray-Triangle Intersection algorithm in textbook 4.4.2
	Eigen::Vector3d A = std::get<0>(corners);
	Eigen::Vector3d B = std::get<1>(corners);
	Eigen::Vector3d C = std::get<2>(corners);
	Eigen::Vector3d D = ray.direction;
	Eigen::Vector3d E = ray.origin;

	Eigen::Vector3d first_column = A - B;
	Eigen::Vector3d second_column = A - C;
	Eigen::Vector3d right_side = A - E;

	Eigen::Vector3d dir;

	double a = first_column[0];
	double b = first_column[1];
	double c = first_column[2];

	double d = second_column[0];
	double e = second_column[1];
	double f = second_column[2];

	double g = D[0];
	double h = D[1];
	double i = D[2];

	double j = right_side[0];
	double k = right_side[1];
	double l = right_side[2];

	double M = a*(e*i - h*f) + b*(g*f - d*i) + c*(d*h - e*g);

	double beta = (j*(e*i - h*f) + k*(g*f - d*i) + l*(d*h - e*g))/M;
	double gamma = (i*(a*k - j*b) + h*(j*c - a*l) + g*(b*l - k*c))/M;
	double temp_t = -(f*(a*k - j*b) + e*(j*c - a*l) + d*(b*l - k*c))/M;

	if(temp_t<min_t){
		return false;
	} else if(gamma<0 || gamma>1){
		return false;
	} else if(beta<0 || beta>(1-gamma)){
		return false;
	} else {
		t = temp_t;
		dir = (first_column).cross(second_column);
		n = dir/(sqrt(dir.dot(dir)));
		return true;
	}
  ////////////////////////////////////////////////////////////////////////////
}


