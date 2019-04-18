// Set the pixel color using Blinn-Phong shading (e.g., with constant blue and
// gray material color) with a bumpy texture.
// 
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
//                     linearly interpolated from tessellation evaluation shader
//                     output
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
//               rgb color of this pixel
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
	mat4 model = model(is_moon, animation_seconds);
    vec3 T, B;
    tangent(sphere_fs_in, T, B);

    vec3 newPos = bump_position(is_moon, sphere_fs_in);
    vec3 newNormal = normalize(cross((bump_position(is_moon, sphere_fs_in+0.0001*T)-newPos)/0.0001,
                                     (bump_position(is_moon, sphere_fs_in+0.0001*B)-newPos)/0.0001));
    if (dot(sphere_fs_in, newNormal) <= 0){
        newNormal = -newNormal;
    }
    // if()

    float t = (2.0*M_PI/16.0)*animation_seconds;
    vec4 light = view*vec4(5*cos(t), 6, 8*sin(t), 1);
    vec3 light_loc = light.xyz;
    vec3 view_loc = view_pos_fs_in.xyz;
    vec3 normal_fs_in = normalize(((transpose(inverse(view)))*(transpose(inverse(model)))* vec4(newNormal, 1.0)).xyz);


 //    float noise_value = 0;
 //    float total = noise_value;
 //    float persist = 10;
 //    int octaves = 9;
 //    float freq =0.98, ampl = 0.0001;
 //    float turbsize, Xlines, Ylines,Zlines, turbPOW;
 //    Xlines = 1;
 //    Ylines = 1;
 //    Zlines = 0.2;
 //    turbPOW = 2;
 //    turbsize = 1;
 //    int GSIZE =1;
 //    for(int i = 0; i < 6; i++){
 //        noise_value += improved_perlin_noise(sphere_fs_in)*turbsize;
 //        total += ampl;
 //        freq += 2.0f;
 //        ampl += persist;
 //        turbsize /= 5.0;
 //    }
 //    noise_value /= total;
 //    noise_value = abs(noise_value);
 //    float intermediate_tex = turbPOW*noise_value/255;
 //    float new_texture = 0.7*abs(sin(intermediate_tex*M_PI));
	// vec3 s = sphere_fs_in;
    if (is_moon) {
    	color = blinn_phong(vec3(0.1, 0.1, 0.1), vec3(0.5, 0.5, 0.5), vec3(0.6, 0.6, 0.6), 500,
                    normalize(normal_fs_in), normalize(-view_loc), normalize(light_loc-view_loc));
        } 

    else {color = blinn_phong(vec3(0.01, 0.01, 0.09), 
        			vec3(0.05, 0.01, 0.7), vec3(0.6, 0.6, 0.6), 500,
                    normalize(normal_fs_in), normalize(-view_loc), normalize(light_loc-view_loc)); 
    }
 
}

// void main(){
//     vec3 T, B;
//     tangent(sphere_fs_in, T, B);
//     color  = vec3(bump_height(is_moon, sphere_fs_in),
//         bump_height(is_moon, sphere_fs_in),
//         bump_height(is_moon, sphere_fs_in));

// }
    
