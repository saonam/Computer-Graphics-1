#ifndef QUADVIEWER_H
#define QUADVIEWER_H
#include <igl/opengl/glfw/Viewer.h>
#include <Eigen/Core>
#include <cassert>
#include <string>
class QuadViewer
{
  public:
    igl::opengl::glfw::Viewer viewer;
    std::function<bool(igl::opengl::glfw::Viewer& viewer, unsigned int key, int modifiers)> callback_key_pressed;
    bool show_lines;
  public:
    QuadViewer():show_lines(true),
      // Important to initialize function
      callback_key_pressed([](igl::opengl::glfw::Viewer& viewer, unsigned int key, int modifiers)->bool{return false;})
    {
      std::cout<<R"(QuadViewer usage:
  F,f      [disabled]
  L,l      Show/hide quad eges
  U,u      Show/hide texture

)";
      viewer.data().show_lines = false;
      viewer.callback_key_pressed = [this](
        igl::opengl::glfw::Viewer & /*viewer*/,
        unsigned int key,
        int modifier)->bool
      {
        if(!callback_key_pressed(viewer,key,modifier))
        {
          switch(key)
          {
            default:
              return false;
            case 'F':
            case 'f':
              // Disable Toggling "face based" since we want control of quad-mesh
              // appearance
              break;
            case 'L':
            case 'l':
              // Usurp the Toggling "show lines" and map to showing overlay instead
              show_lines = !show_lines;
              viewer.data().show_overlay = show_lines;
              break;
            case 'U':
            case 'u':
              viewer.data().show_texture = !viewer.data().show_texture;
              break;
          }
        }
        return true;
      };
    }
    // Set the mesh of .data() to be an exploded version of the given quad mesh
    // 
    // Inputs:
    //   V  #V by 3 mesh vertex positions
    //   F  #F by 4 quad indices into V
    void set_mesh(
      const Eigen::MatrixXd & V,
      const Eigen::MatrixXd & UV,
      const Eigen::MatrixXd & NV,
      const Eigen::MatrixXi & F)
    {
      assert((UV.rows() == 0 || V.rows() == UV.rows()) && "V and UV should have same #rows");
      assert((NV.rows() == 0 || V.rows() == NV.rows()) && "V and NV should have same #rows");
      // libigl Viewer does not handle quad meshes well by default
      // Explode the quad mesh into quad soup. Then each quad can have smooth
      // normals: faceted-quad appearance
      Eigen::MatrixXd FV(F.rows()*4,V.cols());
      Eigen::MatrixXd FUV,FNV;
      if(UV.rows() != 0) FUV.resize(F.rows()*4,UV.cols());
      if(NV.rows() != 0) FNV.resize(F.rows()*4,NV.cols());
      Eigen::MatrixXi FF(F.rows(),4);
      for(int f = 0;f<F.rows();f++)
      {
        for(int c = 0;c<4;c++)
        {
          FF(f,c) = c+f*4;
          FV.row(FF(f,c)) = V.row(F(f,c));
          if(UV.rows() != 0) FUV.row(FF(f,c)) = UV.row(F(f,c));
          if(NV.rows() != 0) FNV.row(FF(f,c)) = NV.row(F(f,c));
        }
      }
      Eigen::MatrixXi T(FF.rows()*2,3);
      T<<
        FF.col(0), FF.col(1), FF.col(2),
        FF.col(0), FF.col(2), FF.col(3);
      viewer.data().clear();
      viewer.data().set_mesh(FV,T);
      if(NV.rows() != 0) viewer.data().set_normals(FNV);
      if(UV.rows() != 0) viewer.data().set_uv(FUV);
      viewer.data().set_face_based(false);
      Eigen::MatrixXi E(FF.rows()*4,2);
      E<<
        FF.col(0), FF.col(1),
        FF.col(1), FF.col(2),
        FF.col(2), FF.col(3),
        FF.col(3), FF.col(0);
      viewer.data().set_edges(FV,E,Eigen::RowVector3d(0,0,0));
    }
    // Wrapper without UV and NV
    void set_mesh(
      const Eigen::MatrixXd & V,
      const Eigen::MatrixXi & F)
    {
      return set_mesh(V,Eigen::MatrixXd(),Eigen::MatrixXd(),F);
    }
    // Explode all data to be per-corner so libigl viewer can handle it.
    void set_mesh(
      const Eigen::MatrixXd & V,
      const Eigen::MatrixXi & F,
      const Eigen::MatrixXd & UV,
      const Eigen::MatrixXi & UF,
      const Eigen::MatrixXd & NV,
      const Eigen::MatrixXi & NF)
    {
      Eigen::MatrixXd vV(F.rows()*F.cols(),V.cols());
      Eigen::MatrixXd vUV(F.rows()*F.cols(),UV.cols());
      Eigen::MatrixXd vNV(F.rows()*F.cols(),NV.cols());
      Eigen::MatrixXi vF(F.rows(),F.cols());
      for(int f = 0;f<F.rows();f++)
      {
        for(int c = 0;c<F.cols();c++)
        {
          const int vi = f*F.cols()+c;
           vV.row(vi) = V.row(F(f,c));
          vUV.row(vi) = UV.row(UF(f,c));
          vNV.row(vi) = NV.row(NF(f,c));
          vF(f,c) = vi;
        }
      }
      set_mesh(vV,vUV,vNV,vF);
    }
    // Pass through to igl::opengl::glfw::Viewer::launch
    int launch(bool resizable = true,bool fullscreen = false)
    { return viewer.launch(resizable,fullscreen); }
};
#endif
