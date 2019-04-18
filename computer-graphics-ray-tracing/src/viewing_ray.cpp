#include "viewing_ray.h"

void viewing_ray(
  const Camera & camera, 
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
	// ray.origin[0] = camera.e[0];
	// ray.origin[1] = camera.e[1];
	// ray.origin[2] = camera.e[2];
	ray.origin = camera.e;

	double l = -camera.width/2;
	double r = camera.width/2;
	double b = -camera.height/2;
	double t = camera.height/2;
	double focus_distance = camera.d;

	double u = l+(r-l)*(j + 0.5)/width;
	double v = b+camera.height-(t-b)*(i + 0.5)/height;

	ray.direction = -focus_distance*camera.w + u*camera.u + v*camera.v;

}

