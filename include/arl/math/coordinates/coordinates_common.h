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
template <typename T> PolarCoord<T> ComplexCoord<T>::toPolar() const
{
    return PolarCoord<T>(abs(), std::atan2(imag, real));
}

template <typename T> ComplexCoord<T> PolarCoord<T>::toComplexCoord() const
{
    return ComplexCoord<T>(r * std::cos(phi), r * std::sin(phi));
}

template <typename T> CylindricalCoord<T> SphericalCoord<T>::toCylindricalCoord() const
{
    return CylindricalCoord<T>(r * std::sin(theta), r * std::cos(theta), phi);
}

template <typename T> SphericalCoord<T> CylindricalCoord<T>::toSphericalCoord() const
{
    SphericalCoord<T> sv;

    sv.r = std::sqrt(r * r + z * z);
    sv.theta = std::atan2(r, z);
    sv.phi = phi;

    return sv;
}

template <typename T> ComplexCoord<T> Vec2D<T>::toComplexCoord() const
{
    return ComplexCoord<T>(x, y);
}

template <typename T> PolarCoord<T> Vec2D<T>::toPolar() const
{
    return PolarCoord<T>(std::sqrt(x * x + y * y), std::atan2(y, x));
}

template <typename T> CylindricalCoord<T> Vec3D<T>::toCylindricalCoord() const
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

    return CylindricalCoord<T>(std::sqrt(x * x + y * y), z, phi);
}

template <typename T> SphericalCoord<T> Vec3D<T>::toSphericalCoord() const
{
    SphericalCoord<T> sv;
    sv.r = std::sqrt(x * x + y * y + z * z);
    sv.phi = std::acos(z / sv.r);
    sv.theta = std::atan2(y, x);
    return sv;
}

}  // namespace arl

#endif
