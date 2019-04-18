#ifndef MESH_TO_VAO_H
#define MESH_TO_VAO_H
#include "gl.h"
#include <Eigen/Core>

// Send a triangle mesh to the GPU using a vertex array object.
//
// Inputs:
//   V  #V by 3 list of 3D mesh vertex positions
//   F  #F by 3 list of triangle indices into V
// Outputs:
//   VAO  identifier of compiled vertex array object.
inline void mesh_to_vao(
  const Eigen::Matrix< float,Eigen::Dynamic,3,Eigen::RowMajor> & V,
  const Eigen::Matrix<GLuint,Eigen::Dynamic,3,Eigen::RowMajor> & F,
  GLuint & VAO);

// Implementation

inline void mesh_to_vao(
  const Eigen::Matrix< float,Eigen::Dynamic,3,Eigen::RowMajor> & V,
  const Eigen::Matrix<GLuint,Eigen::Dynamic,3,Eigen::RowMajor> & F,
  GLuint & VAO)
{
  // Generate and attach buffers to vertex array
  glGenVertexArrays(1, &VAO);
  GLuint VBO, EBO;
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*V.size(), V.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*F.size(), F.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0); 
  glBindVertexArray(0);
}

#endif
