#include "catmull_rom_interpolation.h"
#include <Eigen/Dense>

Eigen::Vector3d catmull_rom_interpolation(
  const std::vector<std::pair<double, Eigen::Vector3d> > & keyframes,
  double t)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code

// Interpolate a given set of 3d vector keyframes (e.g., of Euler angles) at a
// time t using a Catmull-Rom spline.
//
// Inputs:
//   keyframes  #keyframes list of pairs of key-times and key-values sorted in
//     ascending order of key-time
//   t  query time
// Returns inteprolated value at time t
  // Source: https://en.wikipedia.org/wiki/Centripetal_Catmull%E2%80%93Rom_spline
  if (keyframes.size() == 0) {
    return Eigen::Vector3d(0, 0, 0);
  }
  t = std::fmod(t, keyframes[keyframes.size()-1].first);

  int cur = 0;
  while (std::max(keyframes[cur].first, t) == t) {
    cur++;
  }

  // This is linear interpotation which is used when keyframe is two spase. 
  if (cur-2 < 0 || cur == keyframes.size()-1) {

    double time_change = keyframes[cur].first-t;
    double frame_change = keyframes[cur].first-keyframes[cur-1].first;

    t = time_change/frame_change;
    Eigen::Vector3d ret = t*keyframes[cur-1].second+(1-t)*keyframes[cur].second;
    return ret;
  }


  Eigen::Vector3d p0, p1, p2, p3, a1, a2, a3, b1, b2, c;
  double t0, t1, t2, t3;

  t0 = keyframes[cur-2].first;
  t1 = keyframes[cur-1].first;
  t2 = keyframes[cur].first;
  t3 = keyframes[cur+1].first;
  t = t - t0;
  t1 = t1 - t0;
  t2 = t2 - t0;
  t3 = t3 - t0;

  t0 = 0.0;
  
  p0 = keyframes[cur-2].second;
  p1 = keyframes[cur-1].second;
  p2 = keyframes[cur].second;
  p3 = keyframes[cur+1].second;

  a1 = ((t1-t)/(t1-t0))*p0+((t-t0)/(t1-t0))*p1;
  a2 = ((t2-t)/(t2-t1))*p1+((t-t1)/(t2-t1))*p2;
  a3 = ((t3-t)/(t3-t2))*p2+((t-t2)/(t3-t2))*p3;

  b1 = ((t2-t)/(t2-t0))*a1+((t-t0)/(t2-t0))*a2;
  b2 = ((t3-t)/(t3-t1))*a2+((t-t1)/(t3-t1))*a3;

  c = ((t2-t)/(t2-t1))*b1+((t-t1)/(t2-t1))*b2;
  return c;
  /////////////////////////////////////////////////////////////////////////////
};
