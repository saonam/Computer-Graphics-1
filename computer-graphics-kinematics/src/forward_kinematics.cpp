#include "forward_kinematics.h"
#include "euler_angles_to_transform.h"
#include <functional> // std::function

void forward_kinematics(
  const Skeleton & skeleton,
  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
	// Compute the deformations (tranformations from rest pose) for each node in a
	// forward kinematics hiearchy (reading each node's relative transformation from
	// rest).
	//
	// Inputs:
	//   skeleton  transformation hierarchy of #T bones
	// Outputs:
	//   T  #T list of affine transformations
  T.resize(skeleton.size(),Eigen::Affine3d::Identity());
   // Transformation mapping from "canonical bone" to "rest bone"
   // Eigen::Affine3d rest_T;
   // c++ lambda functions and capturing #include <functional>
   // lambda function syntax:
  		// store a lambda
    	// std::function<void()> f_display_42 = []() { print_num(42); };
    	// f_display_42();
  std:: function<Eigen::Affine3d(int)> f_kinematics = [&skeleton, &f_kinematics](int i)
  			// Index into skeleton bone-list  of parent (-1 indicates root)
			-> Eigen::Affine3d  {if (skeleton[i].parent_index == -1) 
			  	{
			  		Eigen::Affine3d root =  Eigen::Affine3d::Identity();
            return root*
               (skeleton[i].rest_T)*
                euler_angles_to_transform(skeleton[i].xzx)*
               ((skeleton[i].rest_T).inverse());
			  	}
			  	Eigen::Affine3d parent = f_kinematics(skeleton[i].parent_index);
			  	return parent*
			  		   (skeleton[i].rest_T)*
			  		    euler_angles_to_transform(skeleton[i].xzx)*
			  		   ((skeleton[i].rest_T).inverse());};
  
  for(int i = 0; i<skeleton.size(); i++){
  	T[i] = f_kinematics(i);
  }
  /////////////////////////////////////////////////////////////////////////////
}
