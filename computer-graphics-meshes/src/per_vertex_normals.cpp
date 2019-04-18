#include "per_vertex_normals.h"
#include "triangle_area_normal.h"
#include "vertex_triangle_adjacency.h"


void per_vertex_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(V.rows(),3);
  std::vector<std::vector<int> >  VF;
  int num_vertices = V.rows();
  vertex_triangle_adjacency(F, num_vertices, VF);

  for(int i = 0; i<V.rows(); i++){
    for(int j = 0; j<VF[i].size(); j++){
        N.row(i) += triangle_area_normal(V.row(F(VF[i][j], 0)), V.row(F(VF[i][j], 1)), V.row(F(VF[i][j], 2)));
        N.row(i).normalized();
    }
  }
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  ////////////////////////////////////////////////////////////////////////////
}