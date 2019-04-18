#include <Eigen/Core>

Eigen::Vector3d reflect(const Eigen::Vector3d & in, const Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:

	Eigen::Vector3d reflected_direction;
	reflected_direction = in-2*(in.dot(n))*n;
	Eigen::Vector3d norm_reflected_direction = reflected_direction.normalized();

  	return norm_reflected_direction;
  ////////////////////////////////////////////////////////////////////////////
}
