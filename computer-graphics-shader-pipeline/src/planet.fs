// Generate a procedural planet and orbiting moon. Use layers of (improved)
// Perlin noise to generate planetary features such as vegetation, gaseous
// clouds, mountains, valleys, ice caps, rivers, oceans. Don't forget about the
// moon. Use `animation_seconds` in your noise input to create (periodic)
// temporal effects.
//
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
out vec3 color;
// expects: model, blinn_phong, bump_height, bump_position,
// improved_perlin_noise, tangent
// void main()
// {
//   /////////////////////////////////////////////////////////////////////////////
//   // Replace with your code 
//   color = vec3(1,1,1);
//   /////////////////////////////////////////////////////////////////////////////
// }

void main()
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  //color = vec3(1,1,1);

	vec3 const_normal = normal_fs_in;
	mat4 model = model(is_moon, animation_seconds);
	vec3 T, B;
    tangent(sphere_fs_in, T, B);

    vec3 newPos = bump_position(is_moon, sphere_fs_in);
    vec3 newNormal = normalize(cross((bump_position(is_moon, sphere_fs_in+0.0001*T)-newPos)/0.0001,
                                     (bump_position(is_moon, sphere_fs_in+0.0001*B)-newPos)/0.0001));
    if (dot(sphere_fs_in, newNormal) <= 0){
        newNormal = -newNormal;
    }

    float t = (2.0*M_PI/16.0)*animation_seconds;
    vec4 light = view*vec4(5*cos(t), 1, 5*sin(t), 1);
    vec3 light_loc = light.xyz;
    vec3 view_loc = view_pos_fs_in.xyz;
    vec3 normal_fs_in = normalize(((transpose(inverse(view)))*(transpose(inverse(model)))* vec4(newNormal, 1.0)).xyz);
    if (is_moon) {
	color = blinn_phong(vec3(0.1, 0.1, 0.1), vec3(0.5, 0.5, 0.5), vec3(0.6, 0.6, 0.6), 500,
               normalize(normal_fs_in), normalize(-view_loc), normalize(light_loc-view_loc));
    } else {
		float ocean = -1;
		vec3 ocean_color = vec3(0.05, 0.3, 1);
		vec3 earth_color = vec3(abs(cos((sphere_fs_in.y)*M_PI))*0.6,
			min(max(0.2, abs(cos((sphere_fs_in.y)*M_PI))),0.8),
			abs(cos((sphere_fs_in.y)*M_PI))*0.1);
		if (ocean > bump_height(is_moon, sphere_fs_in) && 
			sqrt(pow(abs(sphere_fs_in.x), 2)+pow(abs(sphere_fs_in.y), 2))/(animation_seconds - 2) <= 0.3
			// 	abs(sphere_fs_in.x)/(animation_seconds - 2) <= 0.3
			// &&	abs(sphere_fs_in.y)/(animation_seconds - 2) <= 0.3
			// && 	abs(sphere_fs_in.z)/(animation_seconds - 2) <= 0.3
		 && animation_seconds > 1){
			color = blinn_phong(vec3(0.1, 0.1, 0.1), ocean_color, vec3(0.6, 0.6, 0.6), 500,
               normalize(normal_fs_in), normalize(-view_loc), normalize(light_loc-view_loc));

		} else {
			color = blinn_phong(vec3(0.1, 0.1, 0.1), earth_color, vec3(0.6, 0.6, 0.6), 500,
               normalize(normal_fs_in), normalize(-view_loc), normalize(light_loc-view_loc));
		}
	}
	  float cload_t =  animation_seconds/16.0 * 2 * M_PI;
	  mat4 cloud_rot = transpose(mat4(
      cos(cload_t), 0, -sin(cload_t),0,
      0,1,0,0,
      sin(cload_t),0,cos(cload_t),0,
      0,0,0,1
    ));

	if (!is_moon && animation_seconds > 3 && 
		sqrt(pow(abs(sphere_fs_in.x), 2)+pow(abs(sphere_fs_in.y), 2))/(animation_seconds - 3) <= 0.3)
		// abs(sphere_fs_in.x)/(animation_seconds - 3) <= 0.3 &&
		// abs(sphere_fs_in.y)/(animation_seconds - 3) <= 0.3 &&
		// abs(sphere_fs_in.z)/(animation_seconds - 3) <= 0.3) 
{
		vec3 cloud = vec3(1, 1, 1);
		float noise_value = 0;
	    float total = noise_value;
	    float persist = 0.1;
	    int octaves = 4;
	    float ampl = 2;
	    float turbsize, Xlines, Ylines,Zlines, turbPOW;
	    Xlines = 5;
	    Ylines = 50;
	    Zlines = 0.5;
	    turbPOW = 1;
	    turbsize = 2;
	    int GSIZE = 9;
	    for(int i = 0; i < 8; i++){
	        noise_value += improved_perlin_noise(sphere_fs_in)*turbsize;
	        total += ampl;
	        // freq += 2.0f;
	        ampl += persist;
	        turbsize /= 1.0;
	    }
	    noise_value /= total;
	    noise_value = abs(noise_value);

	    vec3 Coord = cloud * GSIZE;

	    float intermediate_tex = Coord.x*Xlines/GSIZE+Coord.y*Ylines/GSIZE+Coord.z
	                 * Zlines / GSIZE + turbPOW*noise_value/255;

	    float new_texture = 0.6*abs(sin(intermediate_tex*M_PI/2));

		vec3 cloud_animation = (cloud_rot*vec4(sphere_fs_in, 1)*new_texture).xyz;
		color = color+blinn_phong(vec3(0.05, 0.05, 0.05), vec3(smooth_heaviside(sin(improved_perlin_noise(cloud_animation*5)*2+
				cloud_animation.x*0.4+cloud_animation.z*0.4+cloud_animation.y*0.4)*1.5, 0.0003)), vec3(0.1, 0.1, 0.1), 5,
               normalize(const_normal), normalize(-view_loc), normalize(light_loc-view_loc));
		// vec3(abs(sin(improved_perlin_noise(cloud_animation*4)/1.5)+
		// 		cloud_animation.x*0.3+cloud_animation.z*0.1+cloud_animation.y*0.6)*1.5);
	}
	

  /////////////////////////////////////////////////////////////////////////////
}
