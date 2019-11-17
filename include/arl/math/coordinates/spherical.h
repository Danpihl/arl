#ifndef SPHERICAL_H_
#define SPHERICAL_H_

#include "arl/math/math_core.h"

#include "arl/math/lin_alg.h"
#include "arl/utilities/logging.h"

#include <cmath>
#include <vector>

namespace arl
{
template <typename T> SphericalVec<T>::SphericalVec(const T r_, const T phi_, const T theta_)
{
    r = r_;
    phi = phi_;
    theta = theta_;
}

template <typename T> SphericalVec<T>::SphericalVec() {}

template <typename T> CylindricalVec<T> SphericalVec<T>::toCylindricalVec() const
{
    return CylindricalVec<T>(r * std::sin(theta), r * std::cos(theta), phi);
}

template <typename T> Vec3D<T> SphericalVec<T>::toVec3D() const
{
    return r * Vec3D<T>(std::sin(theta) * std::cos(phi),
                        std::sin(theta) * std::sin(phi),
                        std::cos(theta));
}
}  // namespace arl

#endif
