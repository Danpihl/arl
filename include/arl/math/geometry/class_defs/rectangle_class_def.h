#ifndef RECTANGLE_CLASS_H_
#define RECTANGLE_CLASS_H_

#include "arl/math/misc/forward_decl.h"

namespace arl
{
template <typename T> struct Rect2D
{
    T x;
    T y;
    T w;
    T h;

    Rect2D(const T x_, const T y_, const T w_, const T h_);
    Rect2D();
};
}  // namespace arl

#endif
