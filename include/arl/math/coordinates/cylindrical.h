#ifndef CYLINDRICAL_H_
#define CYLINDRICAL_H_

#include "arl/math/math_core.h"

#include "arl/math/lin_alg.h"
#include "arl/utilities/logging.h"

#include <cmath>
#include <vector>

namespace arl
{
template <typename T> CylindricalVec<T>::CylindricalVec(const T r_, const T z_, const T phi_)
{
    r = r_;
    z = z_;
    phi = phi_;
}

template <typename T> CylindricalVec<T>::CylindricalVec() {}

template <typename T> SphericalVec<T> CylindricalVec<T>::toSphericalVec() const
{
    SphericalVec<T> sv;

    sv.r = std::sqrt(r * r + z * z);
    sv.theta = std::atan2(r, z);
    sv.phi = phi;

    return sv;
}

template <typename T> Vec3D<T> CylindricalVec<T>::toVec3D() const
{
    return Vec3D<T>(r * std::cos(phi), r * std::sin(phi), z);
}
}  // namespace arl

#endif
