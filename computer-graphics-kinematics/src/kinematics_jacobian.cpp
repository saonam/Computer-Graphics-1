#include "kinematics_jacobian.h"
#include "transformed_tips.h"
#include <iostream>

void kinematics_jacobian(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  Eigen::MatrixXd & J)
{
	// Given a list of 
//
// Inputs:
//   b  #b list of indices into skeleton of endpoints to consider
//   skeleton  #bones list of bones
// Outputs:
//   J  #b*3 by #bones*3 Jacobian matrix of partial derivatives. So that
//     J(i*3+c,j*3+a) = ∂xi,c/∂θj,a where xi,c is the cth component of the ith
//     endpoint position in b and θj,a is the ath Euler angle in the jth bone.
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
	J = Eigen::MatrixXd::Zero(b.size()*3,skeleton.size()*3);
	Eigen::VectorXd previous_posed_tip = transformed_tips(skeleton, b);

	for (int i = 0; i<skeleton.size(); i++) {
		for (int j=0; j<3; j++) {
			Skeleton temp = skeleton;
			temp[i].xzx[j] = temp[i].xzx[j] + 10e-7;

			Eigen::VectorXd current_posed_tip = transformed_tips(temp, b);
//J  #b*3 by #bones*3 Jacobian matrix of partial derivatives. So that
//     J(i*3+c,j*3+a) = ∂xi,c/∂θj,a where xi,c is the cth component of the ith
//     endpoint position in b and θj,a is the ath Euler angle in the jth bone.
			for (int bone_idx=0; bone_idx<b.size()*3; bone_idx++) {
				
				J(bone_idx, 3*i+j) = (current_posed_tip[bone_idx]-
							previous_posed_tip[bone_idx])/(10e-7);
			}
		}
	}
  /////////////////////////////////////////////////////////////////////////////
}
