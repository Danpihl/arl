#ifndef POLAR_H_
#define POLAR_H_

#include <cmath>
#include <vector>

#include "arl/math/lin_alg.h"
#include "arl/math/math_core.h"
#include "arl/utilities/logging.h"

namespace arl
{
// PolarCoord
template <typename T> PolarCoord<T>::PolarCoord(const T r_, const T phi_)
{
    r = r_;
    phi = phi_;
}

template <typename T> PolarCoord<T>::PolarCoord() {}

template <typename T> ComplexCoord<T> PolarCoord<T>::toComplex() const
{
    return ComplexCoord<T>(r * std::cos(phi), r * std::sin(phi));
}

template <typename T> Vec2D<T> PolarCoord<T>::toVec2D() const
{
    return Vec2D<T>(r * std::cos(phi), r * std::sin(phi));
}

}  // namespace arl

#endif
