// Copyright 2019 Arrowtwig
#ifndef POL_SPHEREICAL_CYL_H_
#define POL_SPHEREICAL_CYL_H_

#include "arl/math/math_core.h"
#include "arl/math/matrix_vector/matrix_vector_headers.h"

#include "arl/utilities/logging.h"

#include <cmath>
#include <vector>

namespace arl
{
// PolarVec
template <typename T> PolarVec<T>::PolarVec(const T r_, const T phi_)
{
    r = r_;
    phi = phi_;
}

template <typename T> PolarVec<T>::PolarVec() {}

template <typename T> Complex<T> PolarVec<T>::toComplex() const
{
    return Complex<T>(r * std::cos(phi), r * std::sin(phi));
}

template <typename T> Vec2D<T> PolarVec<T>::toVec2D() const
{
    return Vec2D<T>(r * std::cos(phi), r * std::sin(phi));
}

// SphericalVec
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

// CylindricalVec

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
