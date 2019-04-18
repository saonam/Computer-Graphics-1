#ifndef PRINT_PROGRAM_INFO_LOG_H
#define PRINT_PROGRAM_INFO_LOG_H

#include "gl.h"
#include <string>

// Print information about a given glsl shader program.
//
// Inputs:
//   obj  id of object we're querying
// Returns true if printed anything.
bool print_program_info_log(const GLuint obj);

// Implementation
#include "REDRUM.h"
#include "STR.h"
#include "find_and_replace_all.h"

bool print_program_info_log(const GLuint obj)
{
  GLint infologLength = 0;
  GLint charsWritten  = 0;
  
  glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);
  
  if (infologLength > 0)
  {
    char * infoLog = new char[infologLength];
    glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
    std::string log(infoLog);
    find_and_replace_all("ERROR",STR(REDRUM("ERROR")),log);
    find_and_replace_all("WARNING",STR(YELLOWRUM("WARNING")),log);
    std::cerr<<log<<std::endl;
    delete[] infoLog;
    return true;
  }
  return false;
}

#endif
