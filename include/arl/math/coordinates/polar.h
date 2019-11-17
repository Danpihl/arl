#ifndef POLAR_H_
#define POLAR_H_

#include "arl/math/math_core.h"

#include "arl/math/lin_alg.h"

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

}  // namespace arl

#endif
