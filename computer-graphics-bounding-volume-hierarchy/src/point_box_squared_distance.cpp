#include "point_box_squared_distance.h"
#include <iostream>

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
    double ret=0;
    if(box.min_corner(0)-query(0)>0){
    	ret += (box.min_corner(0)-query(0))*(box.min_corner(0)-query(0));
    }else if(box.max_corner(0)-query(0)<0){
    	ret += (box.max_corner(0)-query(0))*(box.max_corner(0)-query(0));
    }

    if(box.min_corner(1)-query(1)>0){
    	ret += (box.min_corner(1)-query(1))*(box.min_corner(1)-query(1));
    }else if(box.max_corner(1)-query(1)<0){
    	ret += (box.max_corner(1)-query(1))*(box.max_corner(1)-query(1));
    }

    if(box.min_corner(2)-query(2)>0){
    	ret += (box.min_corner(2)-query(2))*(box.min_corner(2)-query(2));
    }else if(box.max_corner(2)-query(2)<0){
    	ret += (box.max_corner(2)-query(2))*(box.max_corner(2)-query(2));
    }

    return ret;

}
  ////////////////////////////////////////////////////////////////////////////
