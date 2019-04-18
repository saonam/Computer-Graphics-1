// Create a bumpy surface by using procedural noise to generate a height (
// displacement in normal direction).
//
// Inputs:
//   is_moon  whether we're looking at the moon or centre planet
//   s  3D position of seed for noise generation
// Returns elevation adjust along normal (values between -0.1 and 0.1 are
//   reasonable.
float bump_height( bool is_moon, vec3 s)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
    float noise = 0;
    // float noise_value = 0;
    // float total = noise_value;
    // float persist = 1;
    // int octaves = 99;
    // float freq =0.9, ampl = 0.0041;
    // float turbsize, Xlines, Ylines,Zlines, turbPOW;
    // turbPOW = 200;
    // turbsize = 7;
    // Xlines = 1.4;
    // Ylines = 0.5;
    // Zlines = 0.9;
    // int GSIZE =1;
    // for(int i = 0; i < 2.6; i++){
    //     noise_value += improved_perlin_noise(s)*turbsize;
    //     total += ampl;
    //     freq += 2.0f;
    //     ampl += persist;
    //     turbsize /= 2.0;
    // }
    // vec3 Coord = s * GSIZE;
    // noise_value /= total;
    // noise_value = abs(noise_value);
    // float intermediate_tex = Coord.x*Xlines/GSIZE+Coord.y*Ylines/GSIZE+Coord.z
    //              * Zlines / GSIZE+turbPOW*noise_value/255;
    // float new_texture = abs(cos(intermediate_tex*M_PI));
  if (is_moon) {
    // height = smooth_heaviside(new_texture, 0.2);
  	noise = smooth_heaviside(improved_perlin_noise(s*2)*5, 4);
  } else {
    // height = smooth_heaviside(new_texture, 0.1);
  	noise = smooth_heaviside(improved_perlin_noise(s*3)*80, 0.4);
  }
  int ocean =1;
  if(!is_moon){
    if(ocean > noise){
      noise = abs(sin(smooth_heaviside(improved_perlin_noise(s*40)*0.005, 0.1)))-3;
    }else{
    noise = noise + abs(sin(smooth_heaviside(improved_perlin_noise(s*15)*0.4, 0.9)));          }

  }
  
  return noise;
  /////////////////////////////////////////////////////////////////////////////
}
