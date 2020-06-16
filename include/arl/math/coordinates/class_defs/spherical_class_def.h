#ifndef SPHERICAL_CLASS_H_
#define SPHERICAL_CLASS_H_

#include "arl/math/misc/forward_decl.h"

namespace arl
{
template <typename T> struct SphericalCoord
{
    // phi for azimuth, theta for inclination
    T r;
    T phi;
    T theta;

    SphericalCoord(const T r_, const T phi_, const T theta_);
    SphericalCoord();

    CylindricalCoord<T> toCylindricalCoord() const;
    Vec3D<T> toVec3D() const;
};

template <typename T> using SphericalPoint = SphericalCoord<T>;
}  // namespace arl

#endif
