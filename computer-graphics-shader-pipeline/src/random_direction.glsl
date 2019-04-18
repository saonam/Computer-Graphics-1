// Generate a pseudorandom unit 3D vector
// 
// Inputs:
//   seed  3D seed
// Returns psuedorandom, unit 3D vector drawn from uniform distribution over
// the unit sphere (assuming random2 is uniform over [0,1]²).
//
// expects: random2.glsl, PI.glsl
vec3 random_direction( vec3 seed)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 

    // double u = ((double)i/num_faces_u - 0.5)*((2*M_PI));  //lon
    // double v = ((double)j/num_faces_v - 0.5)*((M_PI));    //lat

    // double x = cos(u)*cos(v);
    // double y = sin(u)*cos(v);
    // double z = sin(v);
    vec2 map_loc = random2(seed);
    float u = 2*M_PI*map_loc.x;
    float v = cos(2*map_loc.y-1);
    float x = cos(u)*cos(v);
    float y = sin(u)*cos(v);
    float z = sin(v);
    
    // return unit vector
    return normalize(vec3(x, y, z));
  /////////////////////////////////////////////////////////////////////////////
}
