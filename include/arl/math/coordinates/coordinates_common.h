#ifndef COORDINATES_COMMON_H_
#define COORDINATES_COMMON_H_

#include "arl/math/coordinates/class_defs/complex_class_def.h"
#include "arl/math/coordinates/class_defs/cylindrical_class_def.h"
#include "arl/math/coordinates/class_defs/polar_class_def.h"
#include "arl/math/coordinates/class_defs/spherical_class_def.h"
#include "arl/math/lin_alg/vector_low_dim/class_defs/vec2d_class_def.h"
#include "arl/math/lin_alg/vector_low_dim/class_defs/vec3d_class_def.h"
#include "arl/math/lin_alg/vector_low_dim/vec2d.h"
#include "arl/math/lin_alg/vector_low_dim/vec3d.h"
#include "arl/utilities/logging.h"

namespace arl
{
template <typename T> PolarVec<T> Complex<T>::toPolar() const
{
    return PolarVec<T>(abs(), std::atan2(imag, real));
}

template <typename T> Complex<T> PolarVec<T>::toComplex() const
{
    return Complex<T>(r * std::cos(phi), r * std::sin(phi));
}

template <typename T> CylindricalVec<T> SphericalVec<T>::toCylindricalVec() const
{
    return CylindricalVec<T>(r * std::sin(theta), r * std::cos(theta), phi);
}

template <typename T> SphericalVec<T> CylindricalVec<T>::toSphericalVec() const
{
    SphericalVec<T> sv;

    sv.r = std::sqrt(r * r + z * z);
    sv.theta = std::atan2(r, z);
    sv.phi = phi;

    return sv;
}

template <typename T> Complex<T> Vec2D<T>::toComplex() const
{
    return Complex<T>(x, y);
}

template <typename T> PolarVec<T> Vec2D<T>::toPolar() const
{
    return PolarVec<T>(std::sqrt(x * x + y * y), std::atan2(y, x));
}

template <typename T> CylindricalVec<T> Vec3D<T>::toCylindricalVec() const
{
    T phi;
    if (x == 0.0 && y == 0.0)
    {
        phi = 0.0;
    }
    else
    {
        phi = std::atan2(y, x);
    }

    return CylindricalVec<T>(std::sqrt(x * x + y * y), z, phi);
}

template <typename T> SphericalVec<T> Vec3D<T>::toSphericalVec() const
{
    SphericalVec<T> sv;
    sv.r = std::sqrt(x * x + y * y + z * z);
    sv.phi = std::acos(z / sv.r);
    sv.theta = std::atan2(y, x);
    return sv;
}

}  // namespace arl

#endif
