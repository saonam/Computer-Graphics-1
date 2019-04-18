#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::Vector3d bps = Eigen::Vector3d(0,0,0);


  // ambient light shading, accourding to header, set light intensity to 0.1
  Eigen::Vector3d& ka = objects[hit_id]->material->ka;
  bps = bps+(ka.array()*Eigen::Vector3d(0.1, 0.1, 0.1).array()).matrix();

  int num_lights = lights.size();
  
  // Set minimum t of reflected light
  double min_t = 0.000001;
  
  Eigen::Vector3d p = ray.origin+t*ray.direction;

  for(int i = 0; i<num_lights; i++){
    Eigen::Vector3d I = lights[i]->I;
    double max_t;
    Eigen::Vector3d l;
    lights[i]->direction(p, l, max_t);

    // light position
    Ray incoming_light;
    incoming_light.origin = p;
    incoming_light.direction = l;

    int dummy_hit; 
    double not_hit_t; 
    Eigen::Vector3d dummy_norm;


    // Checking shadows 
    if(!first_hit(incoming_light, min_t, objects, dummy_hit, not_hit_t, dummy_norm) || not_hit_t >= max_t){
      
      Eigen::Vector3d v = (-ray.direction).normalized();
      double phong_exponent = objects[hit_id]->material->phong_exponent;
      Eigen::Vector3d kd = objects[hit_id]->material->kd;
      Eigen::Vector3d ks = objects[hit_id]->material->ks;

      Eigen::Vector3d I = lights[i]->I;
      Eigen::Vector3d h = (v+l).normalized();

      // Calculate blin-phong color
      bps = bps + (kd.array()*I.array()).matrix()*fmax(0, n.dot(l)) + 
                          (ks.array()*I.array()).matrix()*pow(fmax(0, n.dot(h)), phong_exponent);
    }
  }
  return bps;
  ////////////////////////////////////////////////////////////////////////////
}
