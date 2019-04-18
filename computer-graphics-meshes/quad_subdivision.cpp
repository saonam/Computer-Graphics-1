#include "catmull_clark.h"
#include "QuadViewer.h"
#include <igl/readOBJ.h>
//#include <igl/opengl/glfw/Viewer.h>

int main(int argc, char * argv[])
{
  Eigen::MatrixXd V;
  Eigen::MatrixXi F;
  igl::readOBJ(argc>1?argv[1]:"../data/bob.obj",V,F);
  if(F.cols() != 4 || F.minCoeff()<0)
  {
    std::cerr<<"Error: only pure quad meshes supported."<<std::endl;
    return EXIT_FAILURE;
  }
  // Remember original mesh
  Eigen::MatrixXd OV = V;
  Eigen::MatrixXi OF = F;
  bool show_lines = true;

  QuadViewer v;
  std::cout<<R"(Usage:
[space]  apply Catmull-Clark subdivision
3        apply Catmull-Clark subdivision 3 times
R,r      Reset to original mesh

)";
  v.set_mesh(V,F);
  v.callback_key_pressed = [&v,&V,&F,&OV,&OF,&show_lines](
    igl::opengl::glfw::Viewer & /*viewer*/,
    unsigned int key,
    int /*modifier*/
    )->bool
  {
    switch(key)
    {
      default:
        return false;
      case 'R':
      case 'r':
        // reset to input mesh
        V = OV;
        F = OF;
        v.set_mesh(V,F);
        break;
      case '3':
        // carry out three subdivisions
        catmull_clark(Eigen::MatrixXd(V),Eigen::MatrixXi(F),3,V,F);
        v.set_mesh(V,F);
        break;
      case ' ':
        // carry out one subdivision
        catmull_clark(Eigen::MatrixXd(V),Eigen::MatrixXi(F),1,V,F);
        v.set_mesh(V,F);
        break;
    }
    return true;
  };
  v.launch();
}
