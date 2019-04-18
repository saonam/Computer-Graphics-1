#include "write_obj.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_obj(
  const std::string & filename,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const Eigen::MatrixXd & UV,
  const Eigen::MatrixXi & UF,
  const Eigen::MatrixXd & NV,
  const Eigen::MatrixXi & NF)
{
  assert((F.size() == 0 || F.cols() == 3 || F.cols() == 4) && "F must have 3 or 4 columns");
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  std::ofstream objfile(filename);

  // If open fails, return false
  if(!objfile.is_open()){
    return false;
  }

// template <typename Scalar, typename Index>
// IGL_INLINE bool igl::readOBJ(
//   FILE * obj_file,

  // ...

//   // variables and constants to assist parsing the .obj file
//   // Constant strings to compare against
//   std::string v("v");
//   std::string vn("vn");
//   std::string vt("vt");
//   std::string f("f");
//   std::string tic_tac_toe("#");

    int number_vertices = V.rows();
    for (int i=0; i<number_vertices; i++) {
        objfile<<"v "<<V(i, 0)<<" "<<V(i, 1)<<" "<<V(i, 2)<<"\n";
    }
    
    int number_3d_norm_vector = NV.rows();
    for (int i=0; i<number_3d_norm_vector; i++) {
        objfile<<"vn "<<NV(i, 0)<<" "<<NV(i, 1)<<" "<<NV(i, 2)<<"\n";
    }

    int number_2d_param = UV.rows();
    for (int i=0; i<number_2d_param; i++) {
        objfile<<"vt "<<UV(i, 0)<<" "<<UV(i, 1)<<"\n";
    }
    
    // F  #F by poly=(3 or 4) list of mesh face indices into V
    // # Polygonal face element (see below)
    // f 1 2 3
    // f 3/1 4/2 5/3
    // f 6/4/1 3/5/3 7/6/5
    // f 7//1 8//2 9//3
    // f ...
    // ...
    // Faces are defined using lists of vertex, texture and normal indices. 
    // Polygons such as quadrilaterals can be defined by using more than 
    // three vertex/texture/normal indices.
    // Since F contain V indices, UF contain texture(2D param) indices, and 
    // NF contain normal indices, we define f as following 
    // Note: In C++ indices “start” at 0, but in a .obj file the first element 
    // in a list has index 1
    for (int i=0; i<F.rows(); i++) {
        objfile<<"f ";
        for (int j=0; j<F.cols(); j++) {
            objfile<<F(i, j)+1<<"/"<<UF(i, j)+1<<"/"<<NF(i, j)+1<<" ";
        }
        objfile<<"\n";
    }

    // if close fails, return false.
    objfile.close();
    if (!objfile) {
        return false;
    }
    return true;
  ////////////////////////////////////////////////////////////////////////////
  return false;
}