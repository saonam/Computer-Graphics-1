cmake_minimum_required(VERSION 2.6)
project(raytracing)

# Prepare the build environment
set(SHARED_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/shared/")
include_directories(${LIBIGL_INCLUDE_DIRS})
add_definitions(${LIBIGL_DEFINITIONS})
option(USE_SOLUTION "Use solution"  OFF)
option(BUILD_TEST "Build test"  OFF)
# Add your project files
include_directories("include/")
if(USE_SOLUTION)
  set(SRC_DIR "solution/")
else()
  set(SRC_DIR "src/")
endif()
file(GLOB SRCFILES "${SRC_DIR}/*.cpp")
set(HW2FILES 
  "${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/Plane.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/Sphere.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/Triangle.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/TriangleSoup.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/first_hit.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/viewing_ray.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/write_ppm.cpp")
list(REMOVE_ITEM SRCFILES ${HW2FILES})

if(BUILD_TEST)
  list(APPEND SRCFILES test/main.cpp)
else()
  list(APPEND SRCFILES main.cpp)
endif()
# create executable
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

if(HW2LIB_DIR)
  link_directories(${HW2LIB_DIR})
endif()

add_executable(${PROJECT_NAME} ${SRCFILES} ${LIBIGL_EXTRA_SOURCES})
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${SHARED_ROOT}/eigen ${SHARED_ROOT}/json)
target_link_libraries(${PROJECT_NAME} ${LIBIGL_LIBRARIES} ${LIBIGL_EXTRA_LIBRARIES})

if(HW2LIB_DIR)
else()
  add_library(hw2 ${HW2FILES})
  target_include_directories(hw2 SYSTEM PUBLIC ${SHARED_ROOT}/eigen ${SHARED_ROOT}/json)
endif()
target_link_libraries(${PROJECT_NAME} hw2)
