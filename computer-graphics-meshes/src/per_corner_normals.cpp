#include "per_corner_normals.h"
#include "triangle_area_normal.h"
// Hint:
#include "vertex_triangle_adjacency.h"
#include <iostream>
#include <cmath>

void per_corner_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double corner_threshold,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(F.rows()*3,3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  std::vector<std::vector<int>> VF;
  int num_vertices = V.rows();
  vertex_triangle_adjacency(F, num_vertices, VF);

  for(int i = 0; i<F.rows(); i++){
    Eigen::RowVector3d N_f = triangle_area_normal(V.row(F(i, 0)), 
                V.row(F(i, 1)), 
                V.row(F(i, 2)));
    for(int j = 0; j<F.cols(); j++){

        int vertex_id = F(i, j);
        std::vector<int> adjacent_faces = VF[vertex_id];
        int num_adjacent_faces = adjacent_faces.size();

        for(int k = 0; k<num_adjacent_faces; k++){
            Eigen::RowVector3d N_g = triangle_area_normal(V.row(F(adjacent_faces[k], 0)), 
                V.row(F(adjacent_faces[k], 1)), 
                V.row(F(adjacent_faces[k], 2)));

            // corner_threshold  threshold in degrees on sharp angles
            // since two normalized vector dot product gives cos(theta), and cos
            // is decreasing function, and we convert corner_threshold to cos, 
            // relationship is greater then. 
            double compare_thre = (N_g.normalized()).dot(N_f.normalized());
            if(compare_thre > cos(corner_threshold*3.1415/180.0)){
                N.row(i*3+j) += N_g;
            }
        }

        // N.row(i) += triangle_area_normal(V.row(F(VF[i][j], 0)), V.row(F(VF[i][j], 1)), V.row(F(VF[i][j], 2)));
        N.row(i*3+j) = N.row(i*3+j).normalized();
    }
    
  }
  ////////////////////////////////////////////////////////////////////////////
}