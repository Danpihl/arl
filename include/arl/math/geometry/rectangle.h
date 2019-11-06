
#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include <cmath>

#include "arl/math/lin_alg.h"
#include "arl/math/math_core.h"
#include "arl/utilities/logging.h"

namespace arl
{
template <typename T> Rect2D<T>::Rect2D(const T x_, const T y_, const T w_, const T h_)
{
    x = x_;
    y = y_;
    w = w_;
    h = h_;
}

template <typename T> Rect2D<T>::Rect2D() {}

}  // namespace arl

#endif
