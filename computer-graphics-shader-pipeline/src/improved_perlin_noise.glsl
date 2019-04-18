// Given a 3d position as a seed, compute an even smoother procedural noise
// value. "Improving Noise" [Perlin 2002].
//
// Inputs:
//   st  3D seed
// Values between  -½ and ½ ?
//
// expects: random_direction, improved_smooth_step

float improved_perlin_noise( vec3 st) 
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
	float x_int = (floor(st.x));
	float y_int = (floor(st.y));
	float z_int = (floor(st.z));
	float x_float = st.x-int(x_int);
	float y_float = st.y-int(y_int);
	float z_float = st.z-int(z_int);
	float u = improved_smooth_step(x_float);
	float v = improved_smooth_step(y_float);
	float w = improved_smooth_step(z_float);

	vec3 p_1, p_2, p_3, p_4, p_5, p_6, p_7, p_8;
	p_1 = vec3(x_int, y_int, z_int);
	p_2 = vec3(x_int, y_int+1, z_int);
	p_3 = vec3(x_int, y_int, z_int+1);
	p_4 = vec3(x_int, y_int+1, z_int+1);
	p_5 = vec3(x_int+1, y_int, z_int);
	p_6 = vec3(x_int+1, y_int+1, z_int);
	p_7 = vec3(x_int+1, y_int, z_int+1);
	p_8 = vec3(x_int+1, y_int+1, z_int+1);

	vec3 d_1 = random_direction(p_1);
	vec3 d_2 = random_direction(p_2);
	vec3 d_3 = random_direction(p_3);
	vec3 d_4 = random_direction(p_4);
	vec3 d_5 = random_direction(p_5);
	vec3 d_6 = random_direction(p_6);
	vec3 d_7 = random_direction(p_7);
	vec3 d_8 = random_direction(p_8);

	
	float u1 = (dot(st-p_5, d_5)-dot(st-p_1, d_1))*u+dot(st-p_1, d_1);
	float u2 = (dot(st-p_6, d_6)-dot(st-p_2, d_2))*u+dot(st-p_2, d_2);
	float v1 = (dot(st-p_7, d_7)-dot(st-p_3, d_3))*u+dot(st-p_3, d_3);
	float v2 = (dot(st-p_8, d_8)-dot(st-p_4, d_4))*u+dot(st-p_4, d_4);
	float m = ((v2-v1)*v+v1);
	float n = (u2-u1)*v+u1;
	float ret = mix(n, m, w);
	return ret/2.0;
  /////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////
}

