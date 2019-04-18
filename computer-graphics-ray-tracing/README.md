# Computer Graphics – Ray Tracing

> **To get started:** Clone this repository using:
> 
>     git clone http://github.com/alecjacobson/computer-graphics-ray-tracing.git
>
> **Do not fork:** Clicking "Fork" will create a _public_ repository. If you'd like to use GitHub while you work on your assignment, then mirror this repo as a new _private_ repository: https://stackoverflow.com/questions/10065526/github-how-to-make-a-fork-of-public-repository-private

## Background

### Read Sections 4.5-4.9 of _Fundamentals of Computer Graphics (4th Edition)_.

Many of the classes and functions of this assignment are borrowed or adapted
from the previous [ray casting assignment](https://github.com/alecjacobson/computer-graphics-ray-casting).

Unlike that assignment, this [ray
tracer](https://en.wikipedia.org/wiki/Ray_tracing_(graphics)) will produce
_approximately_ accurate renderings of scenes illuminated with light.
Ultimately, the shading and lighting models here are _useful_ hacks. The basic
[recursive](https://en.wikipedia.org/wiki/Ray_tracing_(graphics)#Recursive_ray_tracing_algorithm)
structure of the program is core to many methods for rendering with [global
illumination](https://en.wikipedia.org/wiki/Global_illumination) effects (e.g.,
shadows, reflections, etc.).

![Running `./raytracing` should produce this image.](images/sphere-and-plane.png)

## Floating point numbers

For this assignment we will use the `Eigen::Vector3d` to represent points and
vectors, but _also_ RGB colors. For all computation (before finally writing the
.ppm file) we will use double precision floating point numbers and `0` will
represent no light and `1` will represent the brightest color we can display.

[Floating point
numbers](https://en.wikipedia.org/wiki/Floating-point_arithmetic) $≠$ [real
numbers](https://en.wikipedia.org/wiki/Real_number), they don't even cover all
of the [rational numbers](https://en.wikipedia.org/wiki/Rational_number). This
creates a number of challenges in numerical method and rendering is not immune
to them. We see this in the need for a [fudge
factor](https://en.wikipedia.org/wiki/Fudge_factor) to discard ray-intersections
when computing shadows or reflections that are too close to the originating
surface (i.e., false intersections due to numerical error).

> **Question:** If we build a ray and a plane with floating point coefficients,
> will the intersection point have floating point coefficients? What if we
> consider rational coefficients? What if we consider a sphere instead of a
> plane?
>
> **Hint:** Can we _exactly_ represent $1/3$ as a `double`? Can we represent
> $\sqrt{2}$ as a rational?

### Dynamic Range & Burning

Light obeys the [superposition
principle](https://en.wikipedia.org/wiki/Superposition_principle). Simply put,
the light reflected of some part of an objects is the _sum_ of contributions
from light coming in all directions (e.g., from all light sources). If there are
many bright lights in the scene and the object has a bright color, it is easy
for this sum to add up to more than one. At first this seems counter-intuitive:
How can we exceed 100% light? But this premise is false, the $1.0$ does not mean
the physically brightest possible light in the world, but rather the brightest
light our screen can display (or the brightest color we can store in our chosen
image format). [High dynamic range (HDR)
images](https://en.wikipedia.org/wiki/High-dynamic-range_imaging) store a larger
range beyond this usual [0,1]. For this assignment, we will simply _clamp_ the
total light values at a pixel to 1.

This issue is compounded by the problem that the [Blinn-Phong
shading](https://en.wikipedia.org/wiki/Blinn–Phong_shading_model) does not
correctly [conserve energy](https://en.wikipedia.org/wiki/Energy_conservation)
as happens with light in the physical world.

![Running `./raytracing ../data/bunny.json` should produce this image.
Notice the ["burned out"](https://en.wikipedia.org/wiki/Burned_(image)) white
regions where the collected light has been clamped to \[1,1,1\]
(white).](images/bunny.png)

> **Question:** Can we ever get a pixel value _less than zero_?
>
> **Hint:** Can a light be more than off?
>
> **Side note:** This doesn't stop crafty visual effects artists from using
> "negative lights" to manipulate scenes for aesthetic purposes.


## Whitelist

There are many ways to "multiply" two vectors. One way is to compute the
[component-wise](https://en.wikipedia.org/wiki/Hadamard_product_(matrices))
multiplication: $\mathbf{c} = \mathbf{a} \circ \mathbf{b}$ or in index notation:
$c_i = a_i b_i$. That is, multiply each corresponding component and store the
result in the corresponding component of the output vector. Using the Eigen
library this is accomplished by telling Eigen to treat each of the vectors as
"array" (where [matrix multiplication](), [dot product](), [cross product]()
would not make sense) and then using the usual `*` multiplication:

```
Eigen::Vector3d a,b;
...
// Component-wise multiplication
Eigen::Vector3d c = (a.array() * b.array()).matrix();
```

The `.matrix()` converts the "array" view of the vector back to a "matrix"
(i.e., vector) view of the vector.

Eigen also has a built in way to normalize a vector (divide a vector by its
length): `a.normalized()`.

C++ standard library includes a value for $∞$ via `#include <limits>`. For
example, for `double` floating point, use `std::numeric_limits<double>::infinity()`.

## Tasks

### `src/Plane.cpp`,<br> `src/Sphere.cpp`,<br> `src/Triangle.cpp`,<br> `src/TriangleSoup.cpp`,<br> `src/first_hit.cpp`,<br> `src/viewing_ray.cpp`,<br> `src/write_ppm.cpp`

See the previous [ray casting
assignment](https://github.com/alecjacobson/computer-graphics-ray-casting).

### `PointLight::direction` in `src/PointLight.cpp`

Compute the direction to a point light source and its _parametric_ distance from
a query point.

### `DirectionalLight::direction` in `src/DirectionalLight.cpp`

Compute the direction to a direction light source and its _parametric_ distance from a
query point (infinity).

### `src/raycolor.cpp`

Make use of `first_hit.cpp` to shoot a ray into the scene, collect hit
information and use this to return a color value. 

### `src/blinn_phong_shading.cpp`

Compute the lit color of a hit object in the scene using [Blinn-Phong shading
model](https://en.wikipedia.org/wiki/Blinn–Phong_shading_model). This function
should also shoot an additional ray to each light source to check for shadows.

![It is recommended to add and debug each term in your shading model. The
ambient term will look like a faint object-ID image. The diffuse term will
illuminate the scene, and create a dull, Lambertian look to each object. The
specular term will add shiny highlights. Then, mask the diffuse and specular
terms by checking for shadows. Finally, add a recursive call to account for
mirror reflections.](images/sphere-and-plane.gif)

### `src/reflect.cpp`

Given an "incoming" vector and a normal vector, compute the mirror reflected
"outgoing" vector.

![`./raytracing ../data/sphere-packing.json` should produce this
image of highly reflective, metallic looking
surfaces.](images/sphere-packing.png)

### `src/creative.json`

Be creative! Design a scene using any of the available Object types (spheres,
planes, triangles, triangle soups), Light types (directional, point), Material
parameters, colors (materials and/or lights), and don't forget about the camera
parameters.

The [.json format](https://en.wikipedia.org/wiki/JSON) is rather
straightforward. But you may find this [validator](https://jsonlint.com) useful.

> ### HW2 Solution
> If you don't trust your solutiosn to the files from HW2:

>     src/Plane.cpp
>     src/Sphere.cpp
>     src/Triangle.cpp
>     src/TriangleSoup.cpp
>     src/first_hit.cpp
>     src/viewing_ray.cpp
>     src/write_ppm.cpp
>
> You can use precompiled binaries (provided for mac and linux for now) using a
> the cmake command:
>
>     mkdir build
>     cd build
>     cmake -DCMAKE_BUILD_TYPE=Debug -DHW2LIB_DIR=../lib/debug/linux/ ..
>     make
>
> This will use the library at `../lib/debug/linux/libhw2.a` instead of
> compiling the above files in `src/`.
>

------------------------------------------------------------------------

> **Pro Tip:** After you're confident that your program is working _correctly_,
> you can dramatic improve the performance simply by enabling [compiler
> optimization](https://en.wikipedia.org/wiki/Optimizing_compiler): 
>
> ```
> mkdir build-release
> cd build-release
> cmake ../ -DCMAKE_BUILD_TYPE=Release
> make
> ```
