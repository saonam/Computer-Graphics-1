#include "transformed_tips.h"
#include "forward_kinematics.h"

Eigen::VectorXd transformed_tips(
  const Skeleton & skeleton, 
  const Eigen::VectorXi & b)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  // Compute the positions of specified bone "tips" (e.g., where the bone
  // connects to its children; as opposed to "tails", where the bone connects to
  // its parent) _after_ evaluating the forward kinematics chain in the given
  // skeleton.
  //
  // Inputs:
  //   skeleton  #bones list of bones with relative transformations stored in .xzx
  //   b  #b list of indices into skelton of endpoints to compute
  // Returns  #b*3 vector of transformed tip positions
  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > T;
  // compute forward kinematics
  forward_kinematics(skeleton, T);

  Eigen::VectorXd tips(b.size()*3);

  for (int i=0; i<b.size(); i++) {
  	int tip_idx = b[i];
    Bone canonical_bone = skeleton[tip_idx];
    Eigen::Vector4d transformed_tip = T[tip_idx]*canonical_bone.rest_T* 
    			Eigen::Vector4d(canonical_bone.length, 0, 0, 1);

    tips[i*3] = transformed_tip[0];
    tips[i*3+1] = transformed_tip[1];
    tips[i*3+2] = transformed_tip[2];
  }

  return tips;
  // return Eigen::VectorXd::Zero(3*b.size());
  /////////////////////////////////////////////////////////////////////////////
}
