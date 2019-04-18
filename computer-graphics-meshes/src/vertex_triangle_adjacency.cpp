#include "vertex_triangle_adjacency.h"

void vertex_triangle_adjacency(
  const Eigen::MatrixXi & F,
  const int num_vertices,
  std::vector<std::vector<int> > & VF)
{
  VF.resize(num_vertices);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  for(int i = 0; i<F.rows(); i++){
  	for(int j = 0; j<F.cols(); j++){
  		VF[F(i, j)].push_back(i);
  	}
  }
  ////////////////////////////////////////////////////////////////////////////
}
