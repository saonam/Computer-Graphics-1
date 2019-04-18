// Input:
//   N  3D unit normal vector
// Outputs:
//   T  3D unit tangent vector
//   B  3D unit bitangent vector
void tangent(in vec3 N, out vec3 T, out vec3 B)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
    T = vec3(1,0,0);
    B = vec3(0,1,0);
    if (length(cross(N, T)) < length(cross(N, B)))
        T = cross(N, B);
    else 
        T = cross(N, T);
    T = normalize(T);
    B = normalize(cross(T, N));
  /////////////////////////////////////////////////////////////////////////////
}
