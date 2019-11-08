// Copyright 2019 Arrowtwig
#ifndef GENERAL_MATRIX_MATH_FUNCTIONS_H_
#define GENERAL_MATRIX_MATH_FUNCTIONS_H_

#include <cmath>
#include <cstdarg>
#include "arl/math/math_core.h"

namespace arl
{
// TODO:
// - Concatenate matrices horizontally
// - Math functions for matrices

template <typename T>
Matrix<T> concatenateHorizontally(const std::initializer_list<Matrix<T>> &init_list)
{
    size_t num_rows;
    size_t idx = 0;
    for (auto list_mat : init_list)
    {
        if (idx == 0)
        {
            num_rows = list_mat.rows();
            assert(num_rows > 0);
        }
        else
        {
            assert(list_mat.rows() == num_rows);
        }
        assert(list_mat.isAllocated());
        idx++;
    }

    size_t new_num_cols = 0;
    for (auto list_mat : init_list)
    {
        assert(list_mat.cols() > 0);
        new_num_cols = new_num_cols + list_mat.cols();
    }
    Matrix<T> mres(num_rows, new_num_cols);

    size_t c_idx = 0;
    for (auto list_mat : init_list)
    {
        for (size_t c = 0; c < list_mat.cols(); c++)
        {
            for (size_t r = 0; r < list_mat.rows(); r++)
            {
                mres(r, c_idx) = list_mat(r, c);
            }
            c_idx++;
        }
    }

    return mres;
}

/*template <typename T> T max(const Matrix<T>& min)
{
    assert(min.size() > 0);
    T max_val = vin[0];
    for (size_t k = 1; k < vin.size(); k++)
    {
        max_val = std::max(vin[k], max_val);
    }

    return max_val;
}*/

/*template <typename T> T max(const Vector<T>& vin)
{
    assert(vin.size() > 0);
    T max_val = vin[0];
    for (size_t k = 1; k < vin.size(); k++)
    {
        max_val = std::max(vin[k], max_val);
    }

    return max_val;
}

template <typename T> T min(const Vector<T>& vin)
{
    assert(vin.size() > 0);
    T min_val = vin[0];
    for (size_t k = 1; k < vin.size(); k++)
    {
        min_val = std::min(vin[k], min_val);
    }

    return min_val;
}*/

template <typename T>
Matrix<T> log10(const Matrix<T> &min)
{
    assert((min.rows() > 0) && (min.cols() > 0) && (min.isAllocated()));
    Matrix<T> m(min.rows(), min.cols());

    for (size_t r = 0; r < min.rows(); r++)
    {
        for (size_t c = 0; c < min.cols(); c++)
        {
            m(r, c) = std::log10(min(r, c));
        }
    }

    return m;
}

template <typename T>
Matrix<T> pow(const Matrix<T> &min, const T e)
{
    assert((min.rows() > 0) && (min.cols() > 0) && (min.isAllocated()));
    Matrix<T> m(min.rows(), min.cols());

    for (size_t r = 0; r < min.rows(); r++)
    {
        for (size_t c = 0; c < min.cols(); c++)
        {
            m(r, c) = std::pow(min(r, c), e);
        }
    }

    return m;
}

template <typename T>
Matrix<T> log(const Matrix<T> &min)
{
    assert((min.rows() > 0) && (min.cols() > 0) && (min.isAllocated()));
    Matrix<T> m(min.rows(), min.cols());

    for (size_t r = 0; r < min.rows(); r++)
    {
        for (size_t c = 0; c < min.cols(); c++)
        {
            m(r, c) = std::log(min(r, c));
        }
    }

    return m;
}

template <typename T>
Matrix<T> exp(const Matrix<T> &min)
{
    assert((min.rows() > 0) && (min.cols() > 0) && (min.isAllocated()));
    Matrix<T> m(min.rows(), min.cols());

    for (size_t r = 0; r < min.rows(); r++)
    {
        for (size_t c = 0; c < min.cols(); c++)
        {
            m(r, c) = std::exp(min(r, c));
        }
    }

    return m;
}

template <typename T>
Matrix<T> cos(const Matrix<T> &min)
{
    assert((min.rows() > 0) && (min.cols() > 0) && (min.isAllocated()));
    Matrix<T> m(min.rows(), min.cols());

    for (size_t r = 0; r < min.rows(); r++)
    {
        for (size_t c = 0; c < min.cols(); c++)
        {
            m(r, c) = std::cos(min(r, c));
        }
    }

    return m;
}

template <typename T>
Matrix<T> sin(const Matrix<T> &min)
{
    assert((min.rows() > 0) && (min.cols() > 0) && (min.isAllocated()));
    Matrix<T> m(min.rows(), min.cols());

    for (size_t r = 0; r < min.rows(); r++)
    {
        for (size_t c = 0; c < min.cols(); c++)
        {
            m(r, c) = std::sin(min(r, c));
        }
    }

    return m;
}

template <typename T>
Matrix<T> linspace0ColMat(const T x0, const T x1, const size_t num_values)
{
    assert(num_values > 0);
    Matrix<T> m(num_values, 1);

    const double dx = (x1 - x0) / static_cast<double>(num_values - 1);
    m(0, 0) = x0;

    for (size_t r = 1; r < num_values; r++)
    {
        m(r, 0) = m(r - 1, 0) + dx;
    }

    return m;
}

template <typename T>
Matrix<T> linspace1ColMat(const T x0, const T dx, const size_t num_values)
{
    assert(num_values > 0);
    Matrix<T> m(num_values, 1);

    m(0, 0) = x0;

    for (size_t r = 1; r < num_values; r++)
    {
        m(r, 0) = m(r - 1, 0) + dx;
    }

    return m;
}

template <typename T>
Matrix<T> linspace2ColMat(const T x0, const T x1, const T dx)
{
    assert(dx > 0);
    assert(x1 > x0);

    const size_t num_values = (x1 - x0) / dx;

    return linspace0ColMat(x0, x1, num_values);
}

} // namespace arl

#endif