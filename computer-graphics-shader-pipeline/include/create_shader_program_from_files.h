#ifndef CREATE_SHADER_PROGRAM_FROM_FILES_H
#define CREATE_SHADER_PROGRAM_FROM_FILES_H
#include "gl.h"
#include <string>
#include <vector>

// Create a GLSL shader program given a list of paths containing shader code for
// each shader in the vertex-tessellation-fragment shader pipeline. Prints error
// messages on failure.
//
// Inputs:
//   vertex_shader_paths  ordered list of paths to files containing glsl vertex
//     shader code.
//   tess_control_shader_paths  ordered list of paths to files containing glsl
//     tessellation control shader code.
//   tess_evaluation_shader_paths  ordered list of paths to files containing glsl
//     tessellation evaluation shader code.
//   fragment_shader_paths  ordered list of paths to files containing glsl fragment
//     shader code.
//  Outputs:
//    id  identifier of compiled shader program
//  Returns true iff success
inline bool create_shader_program_from_files(
  const std::vector<std::string> & vertex_shader_paths,
  const std::vector<std::string> & tess_control_shader_paths,
  const std::vector<std::string> & tess_evaluation_shader_paths,
  const std::vector<std::string> & fragment_shader_paths,
  GLuint & id);

// Implementation

#include <iostream>
#include "REDRUM.h"
#include "STR.h"
#include "print_shader_info_log.h"
#include "print_program_info_log.h"

inline bool create_shader_program_from_files(
  const std::vector<std::string> & vertex_shader_paths,
  const std::vector<std::string> & tess_control_shader_paths,
  const std::vector<std::string> & tess_evaluation_shader_paths,
  const std::vector<std::string> & fragment_shader_paths,
  GLuint & id)
{
  const auto create_compile_attach = [](
    const std::vector<std::string> & paths, 
    const GLenum type, 
    const GLuint prog_id, 
    GLuint & s) -> bool
  {
    const std::string type_str = 
      (type == GL_VERTEX_SHADER ?                STR(BOLD("vertex shader")) :
        (type == GL_FRAGMENT_SHADER ?            STR(BOLD("fragment shader")) :
          (type == GL_TESS_CONTROL_SHADER ?      STR(BOLD("tessellation control shader")) :
            (type == GL_TESS_EVALUATION_SHADER ? STR(BOLD("tessellation evaluation shader")) : 
               "unknown shader"))));
    int total_length = 0;
    std::vector<std::string> strs;
    {
      for(int p = 0;p<paths.size();p++)
      {
        const auto & path = paths[p];
        std::ifstream t(path);
        if(t.fail())
        {
          std::cerr<<REDRUM("ERROR")<<": failed to open "<<path<<std::endl;
          return false;
        }
        std::stringstream buffer;
        buffer << t.rdbuf();
        if(p!=0)
        {
          strs.push_back(STR(std::endl<<"#line 1 "<<p<<std::endl));
        }
        strs.push_back(buffer.str());
        total_length += buffer.str().length();
      }
    }
    std::vector<const char *> cstrs;
    for(const auto & str : strs)
    {
      cstrs.emplace_back(str.c_str());
    }
    if(total_length == 0)
    {
      std::cerr<<YELLOWRUM("WARNING")<<": "<<type_str<<" is empty..."<<std::endl;;
      s = 0;
      return false;
    }
    s = glCreateShader(type);
    if(s == 0)
    {
      std::cerr<<"failed to create "<<type_str<<std::endl;
      return false;
    }
    {
      glShaderSource(s,cstrs.size(),&cstrs[0],NULL);
    }
    glCompileShader(s);
    print_shader_info_log(type_str,s,paths);
    if(!glIsShader(s))
    {
      std::cerr<<type_str<<" failed to compile."<<std::endl;
      return false;
    }
    glAttachShader(prog_id,s);
    return true;
  };

  // create program
  id = glCreateProgram();
  if(id == 0)
  {
    std::cerr<<REDRUM("ERROR")<<": could not create shader program."<<std::endl;
    return false;
  }

  // create shaders
  GLuint v=0,tc=0,te=0,f=0;

  create_compile_attach(vertex_shader_paths,GL_VERTEX_SHADER,id,v);
  create_compile_attach(tess_control_shader_paths,GL_TESS_CONTROL_SHADER,id,tc);
  create_compile_attach(tess_evaluation_shader_paths,GL_TESS_EVALUATION_SHADER,id,te);
  create_compile_attach(fragment_shader_paths,GL_FRAGMENT_SHADER,id,f);

  // Link program
  glLinkProgram(id);
  const auto & detach = [&id](const GLuint shader)
  {
    if(shader)
    {
      glDetachShader(id,shader);
      glDeleteShader(shader);
    }
  };
  detach(f);
  detach(v);

  // print log if any
  print_program_info_log(id);
  GLint status;
  glGetProgramiv(id,GL_LINK_STATUS,&status);
  if(status != GL_TRUE)
  {
    std::cerr<<REDRUM("ERROR")<<": Failed to link shader program"<<std::endl;
    return false;
  }

  std::cout<<GREENRUM("shader compilation successful.")<<std::endl;
  return true;
}

#endif
