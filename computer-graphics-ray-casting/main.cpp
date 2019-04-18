#include "Object.h"
#include "Ray.h"
#include "Camera.h"
#include "Sphere.h"
#include "Plane.h"
#include "read_json.h"
#include "write_ppm.h"
#include "viewing_ray.h"
#include "first_hit.h"
#include <Eigen/Core>
#include <vector>
#include <iostream>
#include <memory>
#include <limits>
#include <functional>


int main(int argc, char * argv[])
{
  // list of colors used for per-object id coloring
  const std::vector<unsigned char> color_map = {
    228,26,28,
    55,126,184,
    77,175,74,
    152,78,163,
    255,127,0,
    255,255,51,
    166,86,40,
    247,129,191,
    153,153,153
  };

  Camera camera;
  std::vector< std::shared_ptr<Object> > objects;
  // Read a camera and scene description from given .json file
  read_json(argc<=1?"../data/sphere-packing.json":argv[1],camera,objects);

  int width = 640;
  int height = 360;
  std::vector<unsigned char> id_image(3*width*height);
  std::vector<unsigned char> normal_image(3*width*height);
  std::vector<unsigned char> depth_image(1*width*height);
  // For each pixel (i,j)
  for(unsigned i=0; i<height; ++i) 
  {
    for(unsigned j=0; j<width; ++j)
    {
      // Set background color
      normal_image[0+3*(j+width*i)] = 0;
      normal_image[1+3*(j+width*i)] = 0;
      normal_image[2+3*(j+width*i)] = 0;
      depth_image[j+width*i] = 0;
      id_image[0+3*(j+width*i)] = 0;
      id_image[1+3*(j+width*i)] = 0;
      id_image[2+3*(j+width*i)] = 0;

      // Compute viewing ray
      Ray ray;
      viewing_ray(camera,i,j,width,height,ray);

      // Find first visible object hit by ray and its surface normal n
      double t;
      Eigen::Vector3d n;
      int hit_id;
      if(first_hit(ray,1.0,objects,hit_id,t,n))
      {
        // object-id image
        const int color_id = hit_id%(color_map.size()/3);
        id_image[0+3*(j+width*i)] = color_map[0+3*color_id];
        id_image[1+3*(j+width*i)] = color_map[1+3*color_id];
        id_image[2+3*(j+width*i)] = color_map[2+3*color_id];

        // depth image
        const double zNear = camera.d;
        double linearized_depth = zNear/(t*ray.direction.norm());
        linearized_depth = linearized_depth<1?linearized_depth:1;
        depth_image[j+width*i] = 255.0*(linearized_depth);

        // set pixel color to value computed from hit point, light, and n
        // normal image
        auto normal_to_rgb = [](const Eigen::Vector3d & n, unsigned char & r, unsigned char & g, unsigned char & b)
        {
          r = 255.0*(n(0)*0.5+0.5);
          g = 255.0*(n(1)*0.5+0.5);
          b = 255.0*(n(2)*0.5+0.5);
        };
        normal_to_rgb(
          n,
          normal_image[0+3*(j+width*i)],
          normal_image[1+3*(j+width*i)],
          normal_image[2+3*(j+width*i)]);
      }
    }
  }

  write_ppm("normal.ppm",normal_image,width,height,3);
  write_ppm("depth.ppm",depth_image,width,height,1);
  write_ppm("id.ppm",id_image,width,height,3);
}
