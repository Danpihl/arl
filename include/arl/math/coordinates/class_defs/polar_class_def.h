#ifndef POLAR_CLASS_H_
#define POLAR_CLASS_H_

#include "arl/math/misc/forward_decl.h"

namespace arl
{
template <typename T> struct PolarCoord
{
    T r;
    T phi;

    PolarCoord(const T r_, const T phi_);
    PolarCoord();

    ComplexCoord<T> toComplexCoord() const;
    Vec2D<T> toVec2D() const;
};

template <typename T> using PolarPoint = PolarCoord<T>;

}  // namespace arl

#endif
