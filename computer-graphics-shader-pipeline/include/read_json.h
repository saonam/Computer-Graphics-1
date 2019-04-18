#ifndef READ_JSON_H
#define READ_JSON_H

#include <string>
#include <vector>

// Read a shader specification from a .json file
//
// Input:
//   filename  path to .json file
// Outputs:
//   vertex_shader_path           paths to files containing source of vertex
//                                shader
//   tess_control_shader_path     paths to files containing source of tessellation
//                                control shader
//   tess_evaluation_shader_path  paths to files containing source of tessellation
//                                evaluation shader
//   fragment_shader_path         paths to files containing source of fragment
//                                shader
bool read_json(
  const std::string & filename,
  std::vector<std::string> & vertex_shader_paths,
  std::vector<std::string> & tess_control_shader_paths,
  std::vector<std::string> & tess_evaluation_shader_paths,
  std::vector<std::string> & fragment_shader_paths);

// Implementation 

#include <json.hpp>
#include <fstream>

bool read_json(
  const std::string & filename,
  std::vector<std::string> & vertex_shader_paths,
  std::vector<std::string> & tess_control_shader_paths,
  std::vector<std::string> & tess_evaluation_shader_paths,
  std::vector<std::string> & fragment_shader_paths)
{
  // Heavily borrowing from
  // https://github.com/yig/graphics101-raycasting/blob/master/parser.cpp
  using json = nlohmann::json;

  std::ifstream infile( filename );
  if( !infile ) return false;
  json j;
  infile >> j;

  vertex_shader_paths.clear();
  tess_control_shader_paths.clear();
  tess_evaluation_shader_paths.clear();
  fragment_shader_paths.clear();
  for(const auto & jstr : j["vertex"]) { vertex_shader_paths.push_back(jstr); }
  for(const auto & jstr : j["tess_control"]) { tess_control_shader_paths.push_back(jstr); }
  for(const auto & jstr : j["tess_evaluation"]) { tess_evaluation_shader_paths.push_back(jstr); }
  for(const auto & jstr : j["fragment"]) { fragment_shader_paths.push_back(jstr); }

  return true;
}

#endif
