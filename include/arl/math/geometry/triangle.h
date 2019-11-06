
#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <cmath>

#include "arl/math/lin_alg.h"
#include "arl/math/math_core.h"
#include "arl/utilities/logging.h"

namespace arl
{
template <typename T> Triangle2D<T>::Triangle2D() {}

template <typename T>
Triangle2D<T>::Triangle2D(const Point2D<T>& p0_, const Point2D<T>& p1_, const Point2D<T>& p2_)
    : p0(p0_), p1(p1_), p2(p2_)
{
}

template <typename T> Triangle3D<T>::Triangle3D() {}

template <typename T>
Triangle3D<T>::Triangle3D(const Point3D<T>& p0_, const Point3D<T>& p1_, const Point3D<T>& p2_)
    : p0(p0_), p1(p1_), p2(p2_)
{
}

}  // namespace arl

#endif
