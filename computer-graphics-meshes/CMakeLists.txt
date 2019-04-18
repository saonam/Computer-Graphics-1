cmake_minimum_required(VERSION 2.6)
project(meshesh)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

### libIGL options: choose between header only and compiled static library
option(LIBIGL_USE_STATIC_LIBRARY     "Use libigl as static library" OFF)
option(LIBIGL_WITH_OPENGL            "Use OpenGL"         ON)
option(LIBIGL_WITH_PNG               "Use PNG"            ON)
option(LIBIGL_WITH_OPENGL_GLFW       "Use GLFW"           ON)

find_package(LIBIGL REQUIRED)

# Add your project files
include_directories("include/")
if(USE_SOLUTION)
  file(GLOB SRCFILES solution/*.cpp)
else()
  file(GLOB SRCFILES src/*.cpp)
endif()

add_library(core ${SRCFILES})
target_link_libraries(core igl::core igl::opengl igl::opengl_glfw )

add_executable(normals "normals.cpp")
target_link_libraries(normals core igl::core igl::opengl igl::opengl_glfw )

add_executable(quad_subdivision "quad_subdivision.cpp")
target_link_libraries(quad_subdivision core igl::core igl::opengl igl::opengl_glfw )


add_executable(obj "obj.cpp")
target_link_libraries(obj core igl::png igl::core igl::opengl igl::opengl_glfw )
