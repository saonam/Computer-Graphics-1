// Using gl_TessCoord interpolate between values stored at three corners of a
// triangle.
// 
// Inputs:
//   v0  value at corner 0
//   v1  value at corner 1
//   v2  value at corner 2
// Return linearly interpolated value based on gl_TessCoord.
vec3 interpolate(vec3 bary, vec3 v0, vec3 v1, vec3 v2)
{
  return bary.x * v0 + bary.y * v1 + bary.z * v2;
}
vec4 interpolate(vec3 bary, vec4 v0, vec4 v1, vec4 v2)
{
  return bary.x * v0 + bary.y * v1 + bary.z * v2;
}
