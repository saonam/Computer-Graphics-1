// A useful filter, behaves like a smoothly parameterized smooth Heaviside
// function.
// 
// Inputs:
//   x  input scalar (-inf, inf)
//   t  control steepness of step function: --> 0 more linear, --> inf more like
//     Heaviside function (piecewise constant function x<0--> -1 , x>0 --> 1)
// Returns scalar value 
float smooth_heaviside( float x, float t)
{
  return (1./(1.+exp(-2.*t*(x)))-1./2.)/(1./(1.+exp(-2.*t*1.))-1./2.);
}

