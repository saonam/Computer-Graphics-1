#include "PointLight.h"

void PointLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  ////////////////////////////////////////////////////////////////////////////
	Eigen::Vector3d dir_vec = p - q;
	Eigen::Vector3d norm_dir_vec = (p - q)/sqrt((p-q).dot(p-q));
	d = norm_dir_vec;
	max_t = sqrt((p-q).dot(p-q));
}
