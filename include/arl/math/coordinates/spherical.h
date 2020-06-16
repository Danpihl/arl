#ifndef SPHERICAL_H_
#define SPHERICAL_H_

#include <cmath>
#include <vector>

#include "arl/math/coordinates/class_defs/cylindrical_class_def.h"
#include "arl/math/lin_alg/vector_low_dim/vec3d.h"
#include "arl/utilities/logging.h"

namespace arl
{
template <typename T> SphericalCoord<T>::SphericalCoord(const T r_, const T phi_, const T theta_)
{
    r = r_;
    phi = phi_;
    theta = theta_;
}

template <typename T> SphericalCoord<T>::SphericalCoord() {}

template <typename T> Vec3D<T> SphericalCoord<T>::toVec3D() const
{
    return r * Vec3D<T>(std::sin(theta) * std::cos(phi),
                        std::sin(theta) * std::sin(phi),
                        std::cos(theta));
}
}  // namespace arl

#endif
