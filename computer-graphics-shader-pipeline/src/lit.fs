// Add (hard code) an orbiting (point or directional) light to the scene. Light
// the scene using the Blinn-Phong Lighting Model.
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
// expects: PI, blinn_phong
void main()
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 

    float t = (2.0*M_PI/16.0)*animation_seconds;
    vec4 light = view*vec4(5*cos(t), 6, 8*sin(t), 1);
    vec3 light_loc = light.xyz;
    vec3 view_loc = view_pos_fs_in.xyz;
    if (is_moon) {
    	color = blinn_phong(vec3(0.1, 0.1, 0.1), vec3(0.5, 0.5, 0.5), vec3(0.6, 0.6, 0.6), 700,
                    normalize(normal_fs_in), normalize(-view_loc), normalize(light_loc-view_loc));
        } else {color = blinn_phong(vec3(0.0, 0.0, 0.2), vec3(0, 0, 1), vec3(0.7, 0.7, 0.8), 500,
                    normalize(normal_fs_in), normalize(-view_loc), normalize(light_loc-view_loc)); 
    }
    
  /////////////////////////////////////////////////////////////////////////////
}

