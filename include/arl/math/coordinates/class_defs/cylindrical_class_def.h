#ifndef CYLINDRICAL_CLASS_H_
#define CYLINDRICAL_CLASS_H_

#include "arl/math/misc/forward_decl.h"

namespace arl
{
template <typename T> struct CylindricalCoord
{
    T r;
    T z;
    T phi;

    CylindricalCoord(const T r_, const T z_, const T phi_);
    CylindricalCoord();

    SphericalCoord<T> toSphericalCoord() const;
    Vec3D<T> toVec3D() const;
};

template <typename T> using CylindricalPoint = CylindricalCoord<T>;
}  // namespace arl

#endif
