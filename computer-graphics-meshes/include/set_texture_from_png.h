#ifndef SET_TEXTURE_FROM_PNG_H
#define SET_TEXTURE_FROM_PNG_H
#include <igl/opengl/ViewerData.h>
#include <igl/png/texture_from_png.h>
#include <Eigen/Core>
#include <string>
// Read and set texture from a file (basically wrap up
// igl::png::texture_from_png because it's behaving very strangely
//
// Inputs:
//   path  path to .png file
//   data  ViewerData (e.g., returned from viewer.data())
// Returns true if file read succeeds
// Side effects: 
//   sets data uniform colors to white, show_texture to true, and texture colors
//   to contents of file (ignoring alpha)
bool set_texture_from_png(const std::string & path,
    igl::opengl::ViewerData & data)
{
  Eigen::Matrix<unsigned char,Eigen::Dynamic,Eigen::Dynamic> R,G,B,A;
  // what in the world is going on with igl::png::texture_from_png
  if(!igl::png::texture_from_png(path,R,G,B,A))
  {
    return false;
  }
  R = R.colwise().reverse().eval();
  G = G.colwise().reverse().eval();
  B = B.colwise().reverse().eval();
  // No alpha igl::png::texture_from_png seems confused...
  A.setConstant(255);
  data.set_texture(R,G,B,A);
  const Eigen::Vector3d w(1,1,1);
  data.uniform_colors( w*0.1,w,w);
  data.show_texture = true;
  return true;
}
#endif
