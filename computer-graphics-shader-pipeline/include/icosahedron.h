#ifndef ICOSAHEDRON_H
#define ICOSAHEDRON_H
#include <Eigen/Core>

// Construct a triangle mesh of an icosahedron.
//
// Outputs:
//   V  12 by 3 list of 3D mesh vertex positions
//   F  20 by 3 list of triangle indices into V
template <
  typename DerivedV,
  typename DerivedF
>
inline void icosahedron(
  Eigen::PlainObjectBase<DerivedV> & V,
  Eigen::PlainObjectBase<DerivedF> & F);

// Implementation

template <
  typename DerivedV,
  typename DerivedF
>
inline void icosahedron(
  Eigen::PlainObjectBase<DerivedV> & V,
  Eigen::PlainObjectBase<DerivedF> & F)
{
  V = (DerivedV(12,3) <<
    0,0,1,
    0.72360679774997894,-0.52573111211913359,0.44721359549995793,
    0.72360679774997894,0.52573111211913359,0.44721359549995793,
    -0.27639320225002095,0.85065080835203999,0.44721359549995793,
    -0.89442719099991586,1.0953573965284052e-16,0.44721359549995793,
    -0.27639320225002112,-0.85065080835203988,0.44721359549995793,
    0.89442719099991586,0,-0.44721359549995793,
    0.27639320225002106,0.85065080835203988,-0.44721359549995793,
    -0.72360679774997883,0.5257311121191337,-0.44721359549995793,
    -0.72360679774997894,-0.52573111211913348,-0.44721359549995793,
    0.27639320225002084,-0.85065080835203999,-0.44721359549995793,
    0,0,-1).finished();
  F = (DerivedF(20,3)<<
    0,1,2,
    0,2,3,
    0,3,4,
    0,4,5,
    0,5,1,
    1,6,2,
    2,7,3,
    3,8,4,
    4,9,5,
    5,10,1,
    6,7,2,
    7,8,3,
    8,9,4,
    9,10,5,
    10,6,1,
    6,11,7,
    7,11,8,
    8,11,9,
    9,11,10,
    10,11,6).finished();
}
#endif
