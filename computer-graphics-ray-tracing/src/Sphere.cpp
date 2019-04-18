#include "Sphere.h"
#include "Ray.h"
#include <cmath>
#include <algorithm>
#include <Eigen/Geometry>

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
    Eigen::Vector3d d; 
    Eigen::Vector3d e; 
    Eigen::Vector3d c; 

    d = ray.direction;
    e = ray.origin;
    c = center;

    // Set up discriminat terms. 
    double A = d.dot(d);
    double B = 2*(d.dot(e-c));
    double C = (e-c).dot(e-c)-pow(radius, 2);
    double discriminant = pow(B, 2)-4*A*C;

    // If not intersect with sphere
    if (discriminant < 0){
        return false;


    }

    // If tangent to sphere surface. 
    else if (discriminant <= 0.000001) {
        double temp_t = (-B)/(2*A);
        if (temp_t>=min_t) {
            t = temp_t;
            n = ((e+t*d)-c)/radius;
            n = n.normalized();
            return true;
        }
        return false;
    }


    // if there are two solution, we need to check if eye is inside or outside. 
    double temp_t1 = (-B+sqrt(discriminant))/(2*A);
    double temp_t2 = (-B-sqrt(discriminant))/(2*A);

    // if eye is out side
    if (temp_t1 >= min_t && temp_t2 >= min_t && temp_t1 >= 0 && temp_t2 >= 0) {
        t = std::min(temp_t1, temp_t2);
        n = ((e+t*d)-c)/radius;
        n = n.normalized();
        return true;
    } 

    // if eye is inside. 
    else if (temp_t1 < min_t && temp_t2 >= min_t) {
        t = temp_t2;
        n = ((e+t*d)-c)/radius;
        n = n.normalized();
        return true;
    } 
    else if (temp_t2 < min_t && temp_t1 >= min_t) {
        t = temp_t1;
        n = ((e+t*d)-c)/radius;
        n = n.normalized();
        return true;
    } 
    return false;
}
