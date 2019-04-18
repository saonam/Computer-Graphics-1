// Given a 3d position as a seed, compute a smooth procedural noise
// value: "Perlin Noise", also known as "Gradient noise".
//
// Inputs:
//   st  3D seed
// Returns a smooth value between (-1,1)
//
// expects: random_direction, smooth_step
float perlin_noise( vec3 st) 
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
	int x_int = int(st.x);
	int y_int = int(st.y);
	int z_int = int(st.z);
	float x_float = st.x-int(x_int);
	float y_float = st.y-int(y_int);
	float z_float = st.z-int(z_int);
	float u = smooth_step(x_float);
	float v = smooth_step(y_float);
	float w = smooth_step(z_float);

	vec3 p_1, p_2, p_3, p_4, p_5, p_6, p_7, p_8;
	p_1 = vec3(x_int, y_int, z_int);
	p_2 = vec3(x_int, y_int+1.0, z_int);
	p_3 = vec3(x_int, y_int, z_int+1.0);
	p_4 = vec3(x_int, y_int+1.0, z_int+1.0);
	p_5 = vec3(x_int+1.0, y_int, z_int);
	p_6 = vec3(x_int+1.0, y_int+1.0, z_int);
	p_7 = vec3(x_int+1.0, y_int, z_int+1.0);
	p_8 = vec3(x_int+1.0, y_int+1.0, z_int+1.0);
	
	float u1 = mix(dot(random_direction(p_1), vec3(x_float, y_float, z_float)),
		dot(random_direction(p_5), vec3(x_float-1, y_float, z_float)), u);
	float u2 = mix(dot(random_direction(p_2), vec3(x_float, y_float-1, z_float)),
		dot(random_direction(p_6), vec3(x_float-1, y_float-1, z_float)), u);
	float v1 = mix(u1, u2, v);
	u1 = mix(dot(random_direction(p_3), vec3(x_float, y_float, z_float-1)),
		dot(random_direction(p_7), vec3(x_float-1, y_float, z_float-1)), u);
	u2 = mix(dot(random_direction(p_4), vec3(x_float, y_float-1, z_float-1)),
		dot(random_direction(p_8), vec3(x_float-1, y_float-1, z_float-1)), u);
	float v2 = mix(u1, u2, v);

  	return mix(v1, v2, w);
  /////////////////////////////////////////////////////////////////////////////
}

