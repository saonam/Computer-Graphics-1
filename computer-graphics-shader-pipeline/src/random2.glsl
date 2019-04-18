// Generate a pseudorandom 2D vector based on a 2D or 3D seed.
//
// https://thebookofshaders.com/edit.php#11/2d-gnoise.frag
//
// Inputs:
//   st  2D seed
// Returns 2D random point in [0,1]²
vec2 random2(vec2 st){
  st = vec2( dot(st,vec2(127.1,311.7)),
             dot(st,vec2(269.5,183.3)) );
  return fract(sin(st)*43758.5453123);
}
// Inputs:
//   st  3D seed
// Returns 2D random point in [0,1]²
vec2 random2(vec3 st){
  vec2 S = vec2( dot(st,vec3(127.1,311.7,783.089)),
             dot(st,vec3(269.5,183.3,173.542)) );
  return fract(sin(S)*43758.5453123);
}

