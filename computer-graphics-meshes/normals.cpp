#include "per_vertex_normals.h"
#include "per_corner_normals.h"
#include "per_face_normals.h"
#include <igl/read_triangle_mesh.h>
#include <igl/opengl/glfw/Viewer.h>

int main(int argc, char * argv[])
{
  Eigen::MatrixXd V;
  Eigen::MatrixXi F;
  igl::read_triangle_mesh(argc>1?argv[1]:"../data/fandisk.obj",V,F);
  Eigen::MatrixXd VN,FN,CN;
  // Compute different types of normals
  per_face_normals(V,F,FN);
  per_vertex_normals(V,F,VN);
  per_corner_normals(V,F,20,CN);
  // Set up and launch a little mesh viewer
  igl::opengl::glfw::Viewer v;
  v.data().set_mesh(V,F);
  v.data().set_normals(VN);
  // Keyboard interaction handling
  v.callback_key_down = [&VN,&FN,&CN](
    igl::opengl::glfw::Viewer & v,
    unsigned char key,
    int /*modifier*/
    )->bool
  {
    switch(key)
    {
      default:
        return false;
      case '1':
        v.data().set_normals(FN);
        break;
      case '2':
        // viewer is weird and need to convince it out of CN mode
        v.data().set_normals(FN);
        v.data().set_normals(VN);
        break;
      case '3':
        v.data().set_normals(CN);
        break;
    }
    return true;
  };
  std::cout<< R"(
1  Use per-face normals
2  Use per-vertex normals
3  Use per-corner normals
)";
  v.launch();
}

