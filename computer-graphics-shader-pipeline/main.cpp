// clang++ -std=c++11 main.cpp -I include -I $LIBIGL/include -I /usr/local/libigl/external/eigen/ -framework OpenGL -L/usr/local/lib/ -lglfw && ./a.out
//

// make sure the modern opengl headers are included before any others
#include "gl.h"
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include "read_json.h"
#include "icosahedron.h"
#include "mesh_to_vao.h"
#include "print_opengl_info.h"
#include "get_seconds.h"
#include "report_gl_error.h"
#include "create_shader_program_from_files.h"
#include "last_modification_time.h"
#ifdef USE_SOLUTION
#  include "find_and_replace_all.h"
#endif

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <thread>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <vector>

// Default width and height
bool wire_frame = false;
bool mouse_down = false;
bool is_animating = true;
double last_time = get_seconds();
double animation_seconds = 0;
int width =  640;
int height = 360;
// Whether display has high dpi (e.g., Mac retinas)
int highdpi = 1;
GLuint prog_id=0;

Eigen::Affine3f view = 
  Eigen::Affine3f::Identity() * 
  Eigen::Translation3f(Eigen::Vector3f(0,0,-10));
Eigen::Matrix4f proj = Eigen::Matrix4f::Identity();

GLuint VAO;
// Mesh data: RowMajor is important to directly use in OpenGL
Eigen::Matrix< float,Eigen::Dynamic,3,Eigen::RowMajor> V;
Eigen::Matrix<GLuint,Eigen::Dynamic,3,Eigen::RowMajor> F;

int main(int argc, char * argv[])
{

  std::vector<std::string> vertex_shader_paths;
  std::vector<std::string> tess_control_shader_paths;
  std::vector<std::string> tess_evaluation_shader_paths;
  std::vector<std::string> fragment_shader_paths;

  // Initialize glfw window
  if(!glfwInit())
  {
    std::cerr<<"Could not initialize glfw"<<std::endl;
     return EXIT_FAILURE;
  }
  const auto & error = [] (int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  };
  glfwSetErrorCallback(error);
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  GLFWwindow* window = glfwCreateWindow(width, height, "shader-pipeline", NULL, NULL);
  if(!window)
  {
    glfwTerminate();
    std::cerr<<"Could not create glfw window"<<std::endl;
    return EXIT_FAILURE;
  }
  std::cout<<R"(
Usage:
  [Click and drag]  to orbit view
  [Scroll]  to translate view in and out
  A,a  toggle animation
  L,l  toggle wireframe rending
  Z,z  reset view to look along z-axis
)";
  glfwSetWindowPos(window,0,0);
  glfwMakeContextCurrent(window);
  // Load OpenGL and its extensions
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
  {
    std::cerr<<"Failed to load OpenGL and its extensions"<<std::endl;
    return EXIT_FAILURE;
  }
  print_opengl_info(window);
  igl::opengl::report_gl_error("init");


  icosahedron(V,F);
  mesh_to_vao(V,F,VAO);
  igl::opengl::report_gl_error("mesh_to_vao");

  const auto & reshape = [](
    GLFWwindow* window,
    int _width,
    int _height)
  {
    ::width=_width,::height=_height;

    // augh, windows can't handle variables named near and far.
    float nearVal = 0.01;
    float farVal = 100;
    float top = tan(35./360.*M_PI)*nearVal;
    float right = top * (double)::width/(double)::height;
    float left = -right;
    float bottom = -top;
    proj.setConstant(4,4,0.);
    proj(0,0) = (2.0 * nearVal) / (right - left);
    proj(1,1) = (2.0 * nearVal) / (top - bottom);
    proj(0,2) = (right + left) / (right - left);
    proj(1,2) = (top + bottom) / (top - bottom);
    proj(2,2) = -(farVal + nearVal) / (farVal - nearVal);
    proj(3,2) = -1.0;
    proj(2,3) = -(2.0 * farVal * nearVal) / (farVal - nearVal);
  };
  // Set up window resizing
  glfwSetWindowSizeCallback(window,reshape);
  {
    int width_window, height_window;
    glfwGetWindowSize(window, &width_window, &height_window);
    reshape(window,width_window,height_window);
  }

  // Close the window if user presses ESC or CTRL+C
  glfwSetKeyCallback(
    window,
    [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
      if(key == 256 || (key == 67 && (mods & GLFW_MOD_CONTROL)))
      {
        glfwSetWindowShouldClose(window,true);
      }
    });
  glfwSetCharModsCallback(
    window,
    [](GLFWwindow* window, unsigned int codepoint, int modifier)
    {
      switch(codepoint)
      {
        case 'A':
        case 'a':
          is_animating ^= 1;
          if(is_animating)
          {
            last_time = get_seconds();
          }
          break;
        case 'L':
        case 'l':
          wire_frame ^= 1;
          break;
        case 'Z':
        case 'z':
          view.matrix().block(0,0,3,3).setIdentity();
          break;
        default:
          std::cout<<"Unrecognized key: "<<(unsigned char) codepoint<<std::endl;
          break;
      }
    });
  glfwSetMouseButtonCallback(
    window,
    [](GLFWwindow * window, int button, int action, int mods)
    {
      mouse_down = action == GLFW_PRESS;
    });
  glfwSetCursorPosCallback(
    window,
    [](GLFWwindow * window, double x, double y)
    {
      static double mouse_last_x = x;
      static double mouse_last_y = y;
      double dx = x-mouse_last_x;
      double dy = y-mouse_last_y;
      if(mouse_down)
      {
        // Two axis valuator with fixed up
        float factor = std::abs(view.matrix()(2,3));
        view.rotate(
          Eigen::AngleAxisf(
            dx*factor/float(width),
            Eigen::Vector3f(0,1,0)));
        view.rotate(
          Eigen::AngleAxisf(
            dy*factor/float(height),
            view.matrix().topLeftCorner(3,3).inverse()*Eigen::Vector3f(1,0,0)));
      }
      mouse_last_x = x;
      mouse_last_y = y;
    });
  glfwSetScrollCallback(window,
    [](GLFWwindow * window, double xoffset, double yoffset)
    {
      view.matrix()(2,3) =
        std::min(std::max(view.matrix()(2,3)+(float)yoffset,-100.0f),-2.0f);
    });

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  // Force compilation on first iteration through loop
  double time_of_last_shader_compilation = 0;
  double time_of_last_json_load = 0;
  const auto any_changed = 
    [](
        const std::vector<std::string> &paths,
        const double time_of_last_shader_compilation
        )->bool
  {
    for(const auto & path : paths)
    {
      if(last_modification_time(path) > time_of_last_shader_compilation)
      {
        std::cout<<path<<" has changed since last compilation attempt."<<std::endl;
        return true;
      }
    }
    return false;
  };

  float start_time = get_seconds();
  // Main display routine
  while (!glfwWindowShouldClose(window))
  {
    double tic = get_seconds();

    if(any_changed({argv[1]},time_of_last_json_load))
    {
      std::cout<<"-----------------------------------------------"<<std::endl;
      time_of_last_json_load = get_seconds();
      if(!read_json(argv[1],
            vertex_shader_paths,
            tess_control_shader_paths,
            tess_evaluation_shader_paths,
            fragment_shader_paths))
      {
        std::cerr<<"Failed to read "<<argv[1]<<std::endl;
      }
#ifdef USE_SOLUTION
      {
        const auto replace_all = [](std::vector<std::string> & paths)
        {
          for(auto & path : paths)
          {
            find_and_replace_all("/src/","/solution/",path);
          }
        };
        replace_all(vertex_shader_paths);
        replace_all(tess_control_shader_paths);
        replace_all(tess_evaluation_shader_paths);
        replace_all(fragment_shader_paths);
      }
#endif
      // force reload of shaders
      time_of_last_shader_compilation = 0;
    }
    if(
      any_changed(vertex_shader_paths         ,time_of_last_shader_compilation) ||
      any_changed(tess_control_shader_paths   ,time_of_last_shader_compilation) ||
      any_changed(tess_evaluation_shader_paths,time_of_last_shader_compilation) ||
      any_changed(fragment_shader_paths       ,time_of_last_shader_compilation))
    {
      std::cout<<"-----------------------------------------------"<<std::endl;
      // remember the time we tried to compile
      time_of_last_shader_compilation = get_seconds();
      if(
          !create_shader_program_from_files(
            vertex_shader_paths,
            tess_control_shader_paths,
            tess_evaluation_shader_paths,
            fragment_shader_paths,
            prog_id))
      {
        // Force null shader to visually indicate failure
        glDeleteProgram(prog_id);
        prog_id = 0;
        std::cout<<"-----------------------------------------------"<<std::endl;
      }
    }

    // clear screen and set viewport
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwGetFramebufferSize(window, &::width, &::height);
    glViewport(0,0,::width,::height);
    // select program 
    glUseProgram(prog_id);
    // Attach uniforms
    {
      if(is_animating)
      {
        double now = get_seconds();
        animation_seconds += now - last_time;
        last_time = now;
      }
      glUniform1f(glGetUniformLocation(prog_id,"animation_seconds"),animation_seconds);
    }
    glUniformMatrix4fv(
      glGetUniformLocation(prog_id,"proj"),1,false,proj.data());
    glUniformMatrix4fv(
      glGetUniformLocation(prog_id,"view"),1,false,view.matrix().data());
    // Draw mesh as wireframe
    if(wire_frame)
    {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }else
    {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    for(int i = 0;i<2;i++)
    {
      glUniform1i(glGetUniformLocation(prog_id, "is_moon"), i==1);
      glBindVertexArray(VAO);
      glDrawElements(GL_PATCHES, F.size(), GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);
    }


    glfwSwapBuffers(window);

    // 60 fps
    {
      glfwPollEvents();
      // In microseconds
      double duration = 1000000.*(get_seconds()-tic);
      const double min_duration = 1000000./60.;
      if(duration<min_duration)
      {
        std::this_thread::sleep_for(std::chrono::microseconds((int)(min_duration-duration)));
      }
    }
  }

  // Graceful exit
  glfwDestroyWindow(window);
  glfwTerminate();
  return EXIT_SUCCESS;
}
