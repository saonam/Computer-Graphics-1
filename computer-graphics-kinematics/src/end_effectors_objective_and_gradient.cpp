#include "end_effectors_objective_and_gradient.h"
#include "transformed_tips.h"
#include "kinematics_jacobian.h"
#include "copy_skeleton_at.h"
#include <iostream>

void end_effectors_objective_and_gradient(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  const Eigen::VectorXd & xb0,
  std::function<double(const Eigen::VectorXd &)> & f,
  std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  std::function<void(Eigen::VectorXd &)> & proj_z)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  // Given a skeleton and a list of end-effector constraints, construct function
// handles that will compute:
//    the least-squares objective value,
//    the least-squares objective gradient, and
//    project a potential solution onto a feasible solution (within joint limit
//    bounds).
//
// Inputs:
//   skeleton  #bones list of bones
//   b  #b list of indices into skeleton of end-effector constraints
//   xb0  3*#b list of end-effector positions, ordered as [x0 y0 z0 x1 y1 z1 …]
// Outputs:
//   f  function handle that computes the least-squares objective value given a
//     #bones list of Euler angles 
//   grad_f  function handle that computes the least-squares objective gradient
//     given a #bones list of Euler angles 
//   proj_z  function handle that projects a given set of Euler angles onto the
//     input skeleton's joint angles
//  

//   f  function handle that computes the least-squares objective value given a
//     #bones list of Euler angles 
  f = [&](const Eigen::VectorXd & A)->double
  {
      double square_dis = 0.0;
      Skeleton new_skeloton = copy_skeleton_at(skeleton, A);
      Eigen::VectorXd posed_tip = transformed_tips(new_skeloton, b);

      for(int i = 0; i<b.size(); i++){

        int idx = 3*i;
        Eigen::VectorXd l_2 = Eigen::Vector3d(posed_tip[idx] - xb0[idx], 
                          posed_tip[idx+1] - xb0[idx+1], 
                          posed_tip[idx+2] - xb0[idx+2]);
        double l_2norm = l_2.squaredNorm();
        square_dis = square_dis + l_2norm;
      }
      
      return square_dis;
  };


//   grad_f  function handle that computes the least-squares objective gradient
//     given a #bones list of Euler angles 

  grad_f = [&](const Eigen::VectorXd & A)->Eigen::VectorXd
  {

      Eigen::MatrixXd jacobian;
      Eigen::VectorXd gradiant = Eigen::VectorXd::Zero(A.size());
      Skeleton new_skeloton = copy_skeleton_at(skeleton, A);
      Eigen::VectorXd posed_tip = transformed_tips(new_skeloton, b);
      
      kinematics_jacobian(new_skeloton, b, jacobian);
      
      for (int i = 0;i<b.size()*3; i++) 
      {
        gradiant = gradiant + (2*(posed_tip(i)-xb0(i))*jacobian.row(i).transpose());
      }
      return gradiant;
  };


//   proj_z  function handle that projects a given set of Euler angles onto the
//     input skeleton's joint angles
  proj_z = [&](Eigen::VectorXd & A)
  {
      for (int i=0; i<skeleton.size(); i++) {
          Eigen::Vector3d xzx_min = skeleton[i].xzx_min;
          Eigen::Vector3d xzx_max = skeleton[i].xzx_max;
          A[3*i] = std::max(skeleton[i].xzx_min[0], 
                    std::min(skeleton[i].xzx_max[0], A[3*i]));
          A[3*i+1] = std::max(skeleton[i].xzx_min[1], 
                    std::min(skeleton[i].xzx_max[1], A[3*i+1]));
          A[3*i+2] = std::max(skeleton[i].xzx_min[2], 
                    std::min(skeleton[i].xzx_max[2], A[3*i+2]));
    }
  };
  /////////////////////////////////////////////////////////////////////////////
}
