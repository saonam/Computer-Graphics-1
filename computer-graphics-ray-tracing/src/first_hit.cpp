#include "first_hit.h"
#include <limits>

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  double temp_t = std::numeric_limits<double>::max();;
  int num_objects = objects.size();
  int flag_hit_surface = 0;
  int temp_id;
  Eigen::Vector3d temp_normal;

  for(int i = 0; i<num_objects; i++){
    double current_t;
    Eigen::Vector3d current_normal;
    bool hitSurface = objects.at(i)->intersect(ray, min_t, current_t, current_normal);
    if(hitSurface && current_t<temp_t){
      flag_hit_surface = 1;
      temp_t = current_t;
      temp_id = i;
      temp_normal = current_normal;
    }
  }
  // Replace with your code here:
  
  if(flag_hit_surface){
    t = temp_t;
    hit_id = temp_id;
    n = temp_normal;
    return true;
  } else{
    return false;
  }
  ////////////////////////////////////////////////////////////////////////////
}

