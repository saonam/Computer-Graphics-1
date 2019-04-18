#ifndef PRINT_OPENGL_INFO_H
#define PRINT_OPENGL_INFO_H
#include "gl.h"
#define __gl_h_
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

// Use glfw to print information about the current opengl context
// Should be called after glfwMakeContextCurrent(...)
void print_opengl_info(GLFWwindow * window);

// Implementation
 #include <cstdio>
void print_opengl_info(GLFWwindow * window)
{
  int major, minor, rev;
  major = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR);
  minor = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR);
  rev = glfwGetWindowAttrib(window, GLFW_CONTEXT_REVISION);
  printf("OpenGL version recieved: %d.%d.%d\n", major, minor, rev);
  printf("Supported OpenGL is %s\n", (const char*)glGetString(GL_VERSION));
  printf("Supported GLSL is %s\n", (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
}

#endif
