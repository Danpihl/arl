// Copyright 2019 Arrowtwig
#ifndef GENERAL_MATH_FUNCTIONS_H_
#define GENERAL_MATH_FUNCTIONS_H_

#include "arl/utilities/logging.h"
#include <cmath>
#include <cstdarg>
#include <utility>

#include "arl/math/math_core.h"

namespace arl
{
template <typename T> bool any(const Vector<T>& v)
{
    bool b = false;
    for (size_t k = 0; k < v.size(); k++)
    {
        b = b || v(k);
    }
    return b;
}

template <typename T> bool all(const Vector<T>& v)
{
    bool b = true;
    for (size_t k = 0; k < v.size(); k++)
    {
        b = b && v(k);
    }
    return b;
}

template <typename T> Vector<size_t> find(const Vector<T>& v)
{
    std::vector<size_t> std_vec;
    for (size_t k = 0; k < v.size(); k++)
    {
        if (v(k))
        {
            std_vec.push_back(k);
        }
    }
    Vector<size_t> vres = std_vec;
    return vres;
}

template <typename T> Vector<T> concatenate(const std::initializer_list<Vector<T>>& init_list)
{
    size_t new_length = 0;

    for (auto le : init_list)
    {
        new_length = new_length + le.size();
    }
    Vector<T> vres(new_length);

    size_t idx = 0;
    for (auto le : init_list)
    {
        for (size_t k = 0; k < le.size(); k++)
        {
            vres(idx) = le(k);
            idx++;
        }
    }

    return vres;
}

template <typename T> Vector<T> round(const Vector<T>& vin)
{
    assert(vin.size() > 0);
    Vector<T> v(vin.size());
    for (size_t k = 0; k < vin.size(); k++)
    {
        v(k) = std::round(vin(k));
    }

    return v;
}

template <typename T> T max(const Vector<T>& vin)
{
    assert(vin.size() > 0);
    T max_val = vin(0);
    for (size_t k = 1; k < vin.size(); k++)
    {
        max_val = std::max(vin(k), max_val);
    }

    return max_val;
}

template <typename T> T min(const Vector<T>& vin)
{
    assert(vin.size() > 0);
    T min_val = vin(0);
    for (size_t k = 1; k < vin.size(); k++)
    {
        min_val = std::min(vin(k), min_val);
    }

    return min_val;
}

template <typename T> Vector<T> log10(const Vector<T>& vin)
{
    assert(vin.size() > 0);
    Vector<T> v(vin.size());
    for (size_t k = 0; k < vin.size(); k++)
    {
        v(k) = std::log10(vin(k));
    }

    return v;
}

template <typename T> Vector<T> pow(const Vector<T>& vin, const T e)
{
    assert(vin.size() > 0);
    Vector<T> v(vin.size());
    for (size_t k = 0; k < vin.size(); k++)
    {
        v(k) = std::pow(vin(k), e);
    }

    return v;
}

template <typename T> Vector<T> log(const Vector<T>& vin)
{
    assert(vin.size() > 0);
    Vector<T> v(vin.size());
    for (size_t k = 0; k < vin.size(); k++)
    {
        v(k) = std::log(vin(k));
    }

    return v;
}

template <typename T> Vector<T> exp(const Vector<T>& vin)
{
    assert(vin.size() > 0);
    Vector<T> v(vin.size());
    for (size_t k = 0; k < vin.size(); k++)
    {
        v(k) = std::exp(vin(k));
    }

    return v;
}

template <typename T> Vector<T> cos(const Vector<T>& vin)
{
    assert(vin.size() > 0);
    Vector<T> v(vin.size());
    for (size_t k = 0; k < vin.size(); k++)
    {
        v(k) = std::cos(vin(k));
    }

    return v;
}

template <typename T> Vector<T> sin(const Vector<T>& vin)
{
    assert(vin.size() > 0);
    Vector<T> v(vin.size());
    for (size_t k = 0; k < vin.size(); k++)
    {
        v(k) = std::sin(vin(k));
    }

    return v;
}

template <typename T> Vector<T> linspace0(const T x0, const T x1, const size_t num_values)
{
    assert(num_values > 0);
    Vector<T> v(num_values);

    const double dx = (x1 - x0) / static_cast<double>(num_values - 1);
    v(0) = x0;

    for (size_t k = 1; k < num_values; k++)
    {
        v(k) = v(k - 1) + dx;
    }

    return v;
}

template <typename T> Vector<T> linspace1(const T x0, const T dx, const size_t num_values)
{
    assert(num_values > 0);
    Vector<T> v(num_values);

    v(0) = x0;

    for (size_t k = 1; k < num_values; k++)
    {
        v(k) = v(k - 1) + dx;
    }

    return v;
}

template <typename T> Vector<T> linspace2(const T x0, const T x1, const T dx)
{
    assert(dx > 0);
    assert(x1 > x0);

    const size_t num_values = (x1 - x0) / dx;

    return linspace0(x0, x1, num_values);
}

}  // namespace arl

#endif