#ifndef COMPLEX_CLASS_H_
#define COMPLEX_CLASS_H_

namespace arl
{
template <typename T> struct Complex
{
    T real;
    T imag;

    Complex(const T real_, const T imag_);
    Complex();

    PolarVec<T> toPolar() const;
    Complex<T> conjugate() const;
    Complex<T> inv() const;
    Vec2D<T> toVec2D() const;
    T abs() const;
};
}  // namespace arl

#endif
