#ifndef CYLINDRICAL_H_
#define CYLINDRICAL_H_

#include <cmath>
#include <vector>

#include "arl/math/coordinates/class_defs/cylindrical_class_def.h"
#include "arl/math/lin_alg/vector_low_dim/vec3d.h"
#include "arl/utilities/logging.h"

namespace arl
{
template <typename T> CylindricalVec<T>::CylindricalVec(const T r_, const T z_, const T phi_)
{
    r = r_;
    z = z_;
    phi = phi_;
}

template <typename T> CylindricalVec<T>::CylindricalVec() {}

template <typename T> Vec3D<T> CylindricalVec<T>::toVec3D() const
{
    return Vec3D<T>(r * std::cos(phi), r * std::sin(phi), z);
}
}  // namespace arl

#endif
