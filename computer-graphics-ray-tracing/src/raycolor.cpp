#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"
#include <iostream>

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
    if (num_recursive_calls > 10) return false;
    Eigen::Vector3d rbg_color(0, 0, 0);
    int hit_id;
    double t; 
    Eigen::Vector3d n;
    
    if (first_hit(ray, min_t, objects, hit_id, t, n)) {

        Eigen::Vector3d p = ray.origin+t*ray.direction;
        Ray reflected;
        reflected.origin = p;
        reflected.direction = reflect(ray.direction.normalized(), n);;
        Eigen::Vector3d reflect_light;
        
        double min_t = 0.000001;

        // Recursive call of raycolor, this algorithm is referenced from text book 
        if (raycolor(reflected, min_t, objects, lights, num_recursive_calls+1, reflect_light)) {
            Eigen::Vector3d& km = objects[hit_id]->material->km;
            rbg_color = rbg_color+(km.array()*reflect_light.array()).matrix();
        }

        Eigen::Vector3d blinnPhoneComponent = blinn_phong_shading(ray, hit_id, t, n, objects, lights);
        rbg_color = rbg_color+blinnPhoneComponent;
        
        rgb = rbg_color;
        return true;
    }
    rgb = rbg_color;
    return false;
}