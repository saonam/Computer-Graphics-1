#include "linear_blend_skinning.h"

void linear_blend_skinning(
  const Eigen::MatrixXd & V,
  const Skeleton & skeleton,
  const std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T,
  const Eigen::MatrixXd & W,
  Eigen::MatrixXd & U)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
// Given a mesh with vertices in their rest positions, a skeleton, bone
// transformations, and per-vertex weights, compute the linear blend skinning
// deformation.
//
// Inputs:
//   V  #V by 3 list of rest pose mesh vertex positions
//   skeleton  #T list of skeleton bones 
//   T  #T list of affine transformations
//   W  #V by #W list of weights (so that W(v,skeleton[i].weight_index) is the
//     weight at vertex v corresponding to transformation T[i] (Recall:
//     weight_index=-1 indicates no associated weights).
// Outputs:
//   U  #V by 3 list of deformed mesh vertex positions
    U.resize(V.size(), 3);

      for(int i = 0; i<V.rows(); i++){
        	Eigen::Vector4d v = Eigen::Vector4d::Zero();

        	for(int j = 0; j<skeleton.size(); j++){
          		if(skeleton[j].weight_index == -1)
              {
            			continue;
          		}
              
          		Eigen::Vector4d vertices = Eigen::Vector4d(V(i, 0), V(i, 1), V(i, 2), 1);
          		v = v + W(i, skeleton[j].weight_index)*((T[j])*vertices);
        	}
      	U.row(i) = v.head<3>();
    }

  /////////////////////////////////////////////////////////////////////////////
}
