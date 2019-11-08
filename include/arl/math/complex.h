// Copyright 2019 Arrowtwig
#ifndef COMPLEX_H_
#define COMPLEX_H_

#include "arl/math/math_core.h"
#include "arl/math/matrix_vector/matrix_vector_headers.h"

#include <cmath>
#include <vector>

// Reference: https://github.com/N1ckK/MandelbrotZoom/blob/master/complex.h

namespace arl
{
template <typename T>
Complex<T>::Complex() {}
template <typename T>
Complex<T>::Complex(const T real_, const T imag_)
{
    real = real_;
    imag = imag_;
}

template <typename T>
PolarVec<T> Complex<T>::toPolar() const
{
    return PolarVec<T>(abs(), std::atan2(imag, real));
}

template <typename T>
T Complex<T>::abs() const
{
    return std::sqrt(real * real + imag * imag);
}

template <typename T>
Complex<T> Complex<T>::conjugate() const
{
    return Complex<T>(real, -imag);
}

template <typename T>
Vec2D<T> Complex<T>::toVec2D() const
{
    return Vec2D<T>(real, imag);
}

template <typename T>
Complex<T> Complex<T>::inv() const
{
    return Complex<T>(real / (real * real + imag * imag), -imag / (real * real + imag * imag));
}

// Non class methods

template <typename T>
Complex<T> operator*(const Complex<T> &c, const T f)
{
    return Complex<T>(f * c.real, f * c.imag);
}

template <typename T>
Complex<T> operator*(const T f, const Complex<T> &c)
{
    return Complex<T>(f * c.real, f * c.imag);
}

template <typename T>
Complex<T> operator*(const Complex<T> &c0, const Complex<T> &c1)
{
    return Complex<T>(c0.real * c1.real - c0.imag * c1.imag, c0.real * c1.imag + c0.imag * c1.real);
}

template <typename T>
Complex<T> operator+(const Complex<T> &c0, const Complex<T> &c1)
{
    return Complex<T>(c0.real + c1.real, c0.imag + c1.imag);
}

template <typename T>
Complex<T> operator-(const Complex<T> &c0, const Complex<T> &c1)
{
    return Complex<T>(c0.real - c1.real, c0.imag - c1.imag);
}

template <typename T>
T pow(const Complex<T> &c, int n)
{
    if (n == 0)
    {
        return Complex<T>(1.0, 0.0);
    }
    else if (n < 0)
    {
        return pow(c.inv(), -n);
    }
    else if (n == 1)
    {
        return c;
    }
    else
    {
        return pow(c, n - 1) * c;
    }
}

template <typename T>
Complex<T> operator/(const Complex<T> &c0, const Complex<T> &c1)
{
    return c0 * c1.inv();
}

template <typename T>
Complex<T> operator/(const Complex<T> &c, const T f)
{
    return Complex<T>(c.real / f, c.imag / f);
}

template <typename T>
Complex<T> operator/(const T f, const Complex<T> &c)
{
    return f * c.inv();
}

} // namespace arl

#endif
