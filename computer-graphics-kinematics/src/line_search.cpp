#include "line_search.h"
#include <iostream>

double line_search(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const Eigen::VectorXd & z,
  const Eigen::VectorXd & dz,
  const double max_step)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
	// Given a function handle that computes an objective value to minimize, a
// function handle that projects a guess onto a set of constraints and a
// direction to search along, use exponential search to find a decreasing step
// distance.
//
// Inputs:
//   f  function that computes scalar objective value at a given z
//   z  #z vector of initial z values
//   dz  #z vector of changes to z
//   max_step  maximum step to take in dir
// Returns optimal step distance

	double optimal_step_sigma = max_step;
	double Energy = f(z);
	Eigen::VectorXd next_step = z + optimal_step_sigma*dz; 

	proj_z(next_step); 
	 
	while(f(next_step) > Energy && optimal_step_sigma!=0){
		// we decrease σ by a constant factor
		optimal_step_sigma = optimal_step_sigma / 2.0;

		next_step = z - optimal_step_sigma*dz;
		proj_z(next_step);
	}
	return optimal_step_sigma;

  /////////////////////////////////////////////////////////////////////////////
}
