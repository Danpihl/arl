#ifndef POLAR_CLASS_H_
#define POLAR_CLASS_H_

namespace arl
{
template <typename T> struct PolarVec
{
    T r;
    T phi;

    PolarVec(const T r_, const T phi_);
    PolarVec();

    Complex<T> toComplex() const;
    Vec2D<T> toVec2D() const;
};

template <typename T> using PolarPoint = PolarVec<T>;

}  // namespace arl

#endif
