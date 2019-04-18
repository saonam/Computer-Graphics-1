#include "catmull_clark.h"
#include <unordered_map>
#include <utility>
#include <functional>
#include <vector>
#include <Eigen/Core>

void catmull_clark(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const int num_iters,
  Eigen::MatrixXd & SV,
  Eigen::MatrixXi & SF)
{

////////////////////////////////////////////////////////////////////////////
// Replace with your code here:
// Conduct num_iters iterations of Catmull-Clark subdivision on a **pure quad**
// mesh (V,F).
//
// Inputs:
//   V  #V by 3 list of vertex positions
//   F  #F by 4 list of quad mesh indices into V
//   num_iters  number of iterations
// Outputs:
//   SV  #SV by 3 list of vertex positions
//   SF  #SF by 4 list of quad mesh indices into SV
// 

  if(num_iters<1){
    return;
  }

  SV.resize(V.rows(), 3);

  int face_size = F.rows();
  printf("%d\n", face_size);

  SF.resize(F.rows()*4, 4);

  int num_vertices = SV.rows();
  printf("%d\n", num_vertices);
  std::vector<std::vector<int> > VF;
  VF.resize(num_vertices);

  for(int i = 0; i<face_size; i++){
    for(int j = 0; j<F.cols(); j++){
      VF[F(i, j)].push_back(i);
    }
  }
  // MatrixXd & face_mid_point;
  

  for(int i = 0; i<num_vertices; i++){
    SV.row(i) = V.row(i);
  }


  for(int i = 0; i<face_size; i++){
    SV.conservativeResize((SV.rows())+1, 3);
    SV.row(SV.rows()-1) = (SV.row(F(i, 0))+SV.row(F(i, 1))+SV.row(F(i, 2))+SV.row(F(i, 3)))/4.0;
  }

  std::unordered_map<int, Eigen::RowVector3d> r_sum;
  for (int v = 0; v<V.rows();v++){
    r_sum[v] = Eigen::RowVector3d(0,0,0);
  }

  for(int i = 0; i<face_size; i++){
    int idx_1 = -1;
    int idx_2 = -1;
    int idx_3 = -1;
    int idx_4 = -1;
    int f1 = 0, f2=0, f3=0, f4=0;
    std::vector<int> v1 = VF[F(i, 0)];
    std::vector<int> v2 = VF[F(i, 1)];
    std::vector<int> v3 = VF[F(i, 2)];
    std::vector<int> v4 = VF[F(i, 3)];
    for(int j = 0; j<v1.size(); j++){
      for(int k = 0; k<v2.size(); k++){
        if(!f1 && (v1[j] == v2[k]) && (v1[j] != i) && (v2[k] !=i)){
          f1 = v1[j];
          // printf("ffdlfkldfkl\n");
        }
      }
    }
    for(int j = 0; j<v2.size(); j++){
      for(int k = 0; k<v3.size(); k++){
        if(!f2 && (v2[j] == v3[k]) && (v2[j] != i) && (v3[k] !=i)){
          f2= v2[j];
        }
      }
    }
    for(int j = 0; j<v3.size(); j++){
      for(int k = 0; k<v4.size(); k++){
        if(!f3 && (v3[j] == v4[k]) && (v3[j] != i) && (v4[k] !=i)){
          f3 = v3[j];
        }
      }
    }
    for(int j = 0; j<v4.size(); j++){
      for(int k = 0; k<v1.size(); k++){
        if(!f4 && (v4[j] == v1[k]) && (v4[j] != i) && (v1[k] !=i)){
          f4 = v4[j];
        }
      }
    }

    Eigen::RowVector3d mid_edge_1 = (SV.row(F(i, 0))+SV.row(F(i, 1))
                      +SV.row(num_vertices+f1)+SV.row(num_vertices+i))/4.0;

    // printf("%f   %f    %f\n", mid_edge_1[0], mid_edge_1[1], mid_edge_1[2]);


    for(int k=(num_vertices+face_size)-1; k<SV.rows(); k++){
      double temp = ((SV.row(k))-(mid_edge_1)).norm();
      if (temp < 0.00000001){
        idx_1 = k;
        break;
      }
    }
    if(idx_1 == -1){
      SV.conservativeResize(SV.rows()+1, 3);
      SV.row(SV.rows()-1) = mid_edge_1;
      idx_1 = SV.rows()-1;
    }

    Eigen::RowVector3d mid_edge_2 = (SV.row(F(i, 1))+SV.row(F(i, 2))
                      +SV.row(num_vertices+f2)+SV.row(num_vertices+i))/4.0;


    for(int k=(num_vertices+face_size)-1; k<SV.rows(); k++){
      double temp = ((SV.row(k))-(mid_edge_2)).norm();
      if (temp < 0.00000001){
        idx_2 = k;
        break;
      }
    }
    if(idx_2 == -1){
      SV.conservativeResize(SV.rows()+1, 3);
      SV.row(SV.rows()-1) = mid_edge_2;
      idx_2 = SV.rows()-1;
    }

    Eigen::RowVector3d mid_edge_3 = (SV.row(F(i, 2))+SV.row(F(i, 3))
                      +SV.row(num_vertices+f3)+SV.row(num_vertices+i))/4.0;


    for(int k=(num_vertices+face_size)-1; k<SV.rows(); k++){
      double temp = ((SV.row(k))-(mid_edge_3)).norm();
      if (temp < 0.00000001){
        idx_3 = k;
        break;
      }
    }
    if(idx_3 == -1){
      SV.conservativeResize(SV.rows()+1, 3);
      SV.row(SV.rows()-1) = mid_edge_3;
      idx_3 = SV.rows()-1;
    }

    Eigen::RowVector3d mid_edge_4 = (SV.row(F(i, 3))+SV.row(F(i, 0))
                      +SV.row(num_vertices+f4)+SV.row(num_vertices+i))/4.0;


    for(int k=(num_vertices+face_size)-1; k<SV.rows(); k++){
      double temp = ((SV.row(k))-(mid_edge_4)).norm();
      if (temp < 0.00000001){
        idx_4 = k;
        break;
      }
    }
    if(idx_4 == -1){
      SV.conservativeResize(SV.rows()+1, 3);
      SV.row(SV.rows()-1) = mid_edge_4;
      idx_4 = SV.rows()-1;
    }


    // SV.row(F(i, 0)) = (SV.row(F(i, 0))+SV.row(F(i, 1))+SV.row(F(i, 2))+SV.row(F(i, 3)))/4.0;

    SF.row(i*4) = Eigen::RowVector4i(F(i, 0), idx_1, num_vertices+i, idx_4);
    SF.row(i*4+1) = Eigen::RowVector4i(F(i, 1), idx_2, num_vertices+i, idx_1);
    SF.row(i*4+2) = Eigen::RowVector4i(F(i, 2), idx_3, num_vertices+i, idx_2);
    SF.row(i*4+3) = Eigen::RowVector4i(F(i, 3), idx_4, num_vertices+i, idx_3);

    r_sum[F(i, 0)]+= (V.row(F(i,0)) +  V.row(F(i,1)) + V.row(F(i,3)) +  V.row(F(i,0)))/2.0;
    r_sum[F(i, 1)]+= (V.row(F(i,1)) +  V.row(F(i,2)) + V.row(F(i,2)) +  V.row(F(i,3)))/2.0;
    r_sum[F(i, 2)]+= (V.row(F(i,2)) +  V.row(F(i,3)) + V.row(F(i,1)) +  V.row(F(i,2)))/2.0;
    r_sum[F(i, 3)]+= (V.row(F(i,3)) +  V.row(F(i,0)) + V.row(F(i,2)) +  V.row(F(i,3)))/2.0;
    // printf("%d\n", idx_1);


  }



  for(int i = 0; i<V.rows(); i++){

    std::vector<int> v1 = VF[i];

    Eigen::RowVector3d F_value_1(0.0,0.0,0.0);

    Eigen::RowVector3d r_value;
    for(int j = 0; j<v1.size(); j++){
      F_value_1 = F_value_1 + (SV.row(num_vertices+v1[j]));
    }
    F_value_1 = F_value_1 / (double)v1.size();
    r_value = r_sum[i]/2.0 / (double)v1.size();
    SV.row(i) = (F_value_1+2*r_value + (v1.size()-3)*V.row(i)) / (double)v1.size();
  }
  
  catmull_clark(Eigen::MatrixXd(SV), Eigen::MatrixXi(SF), num_iters-1, SV, SF);
}



  // for(int i = 0; )
  ////////////////////////////////////////////////////////////////////////////

