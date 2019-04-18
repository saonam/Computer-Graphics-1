#ifndef VERTEX_TRIANGLE_ADJACENCY_H
#define VERTEX_TRIANGLE_ADJACENCY_H
#include <Eigen/Core>
#include <vector>
// Compute a vertex-triangle adjacency list. For each vertex store a list of all
// incident faces.
//
// Inputs:
//   F  #F by 3 list of mesh triangle indices
//   num_vertices  number of vertices (i.e., V.rows(); usually ==F.maxCoeff()+1)
// Outputs:
//   VF  num_verticess-long list of lists so that f=VF[i][j] means that face f
//     is the jth face among those incident on vertex i. Adjacency faces are
//     listed in no particular order (but no duplicates).
void vertex_triangle_adjacency(
  const Eigen::MatrixXi & F,
  const int num_vertices,
  std::vector<std::vector<int> > & VF);
#endif
