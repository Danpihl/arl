
#ifndef MATRIX_MATH_FUNCTIONS_H_
#define MATRIX_MATH_FUNCTIONS_H_

#include <cmath>
#include <cstdarg>

#include "arl/math/lin_alg/matrix_dynamic/matrix_dynamic.h"
#include "arl/math/lin_alg/vector_dynamic/vector_dynamic.h"
#include "arl/utilities/logging.h"

namespace arl
{
// TODO:
// - Concatenate matrices horizontally
// - Math functions for matrices

template <typename T>
Vector<T> linspaceFromPointsAndCount(const T x0, const T x1, const size_t num_values);

template <typename T>
std::pair<Matrix<T>, Matrix<T>> meshGrid(
    const T x0, const T x1, const T y0, const T y1, const size_t xn, const size_t yn)
{
    const Vector<T> x_vec = linspaceFromPointsAndCount(x0, x1, xn);
    const Vector<T> y_vec = linspaceFromPointsAndCount(y0, y1, yn);

    Matrix<T> x_mat(yn, xn), y_mat(yn, xn);
    for (size_t r = 0; r < yn; r++)
    {
        for (size_t c = 0; c < xn; c++)
        {
            x_mat(r, c) = x_vec(c);
            y_mat(r, c) = y_vec(r);
        }
    }

    return std::pair<Matrix<T>, Matrix<T>>(x_mat, y_mat);
}

template <typename T>
std::pair<Matrix<T>, Matrix<T>> meshgrid(const Vector<T>& x_vec, const Vector<T>& y_vec)
{
    Matrix<T> x_mat(y_vec.size(), x_vec.size()), y_mat(y_vec.size(), x_vec.size());

    for (size_t r = 0; r < y_vec.size(); r++)
    {
        for (size_t c = 0; c < x_vec.size(); c++)
        {
            x_mat(r, c) = x_vec(c);
            y_mat(r, c) = y_vec(r);
        }
    }

    return std::pair<Matrix<T>, Matrix<T>>(x_mat, y_mat);
}

template <typename T>
Matrix<T> concatenateHorizontally(const std::initializer_list<Matrix<T>>& init_list)
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

template <typename T>
Matrix<T> concatenateVertically(const std::initializer_list<Matrix<T>>& init_list)
{
    size_t num_cols;
    size_t idx = 0;
    for (auto list_mat : init_list)
    {
        if (idx == 0)
        {
            num_cols = list_mat.cols();
            assert(num_cols > 0);
        }
        else
        {
            assert(list_mat.cols() == num_cols);
        }
        assert(list_mat.isAllocated());
        idx++;
    }

    size_t new_num_rows = 0;
    for (auto list_mat : init_list)
    {
        assert(list_mat.rows() > 0);
        new_num_rows = new_num_rows + list_mat.rows();
    }
    Matrix<T> mres(new_num_rows, num_cols);

    size_t r_idx = 0;
    for (auto list_mat : init_list)
    {
        for (size_t r = 0; r < list_mat.rows(); r++)
        {
            for (size_t c = 0; c < list_mat.cols(); c++)
            {
                mres(r_idx, c) = list_mat(r, c);
            }
            r_idx++;
        }
    }

    return mres;
}

template <typename T> Matrix<T> log10(const Matrix<T>& m_in)
{
    assert((m_in.rows() > 0) && (m_in.cols() > 0) && (m_in.isAllocated()));
    Matrix<T> m(m_in.rows(), m_in.cols());

    for (size_t r = 0; r < m_in.rows(); r++)
    {
        for (size_t c = 0; c < m_in.cols(); c++)
        {
            m(r, c) = std::log10(m_in(r, c));
        }
    }

    return m;
}

template <typename T> Matrix<T> pow(const Matrix<T>& m_in, const T e)
{
    assert((m_in.rows() > 0) && (m_in.cols() > 0) && (m_in.isAllocated()));
    Matrix<T> m(m_in.rows(), m_in.cols());

    for (size_t r = 0; r < m_in.rows(); r++)
    {
        for (size_t c = 0; c < m_in.cols(); c++)
        {
            m(r, c) = std::pow(m_in(r, c), e);
        }
    }

    return m;
}

template <typename T> Matrix<T> log(const Matrix<T>& m_in)
{
    assert((m_in.rows() > 0) && (m_in.cols() > 0) && (m_in.isAllocated()));
    Matrix<T> m(m_in.rows(), m_in.cols());

    for (size_t r = 0; r < m_in.rows(); r++)
    {
        for (size_t c = 0; c < m_in.cols(); c++)
        {
            m(r, c) = std::log(m_in(r, c));
        }
    }

    return m;
}

template <typename T> Matrix<T> exp(const Matrix<T>& m_in)
{
    assert((m_in.rows() > 0) && (m_in.cols() > 0) && (m_in.isAllocated()));
    Matrix<T> m(m_in.rows(), m_in.cols());

    for (size_t r = 0; r < m_in.rows(); r++)
    {
        for (size_t c = 0; c < m_in.cols(); c++)
        {
            m(r, c) = std::exp(m_in(r, c));
        }
    }

    return m;
}

template <typename T> Matrix<T> cos(const Matrix<T>& m_in)
{
    assert((m_in.rows() > 0) && (m_in.cols() > 0) && (m_in.isAllocated()));
    Matrix<T> m(m_in.rows(), m_in.cols());

    for (size_t r = 0; r < m_in.rows(); r++)
    {
        for (size_t c = 0; c < m_in.cols(); c++)
        {
            m(r, c) = std::cos(m_in(r, c));
        }
    }

    return m;
}

template <typename T> Matrix<T> sin(const Matrix<T>& m_in)
{
    assert((m_in.rows() > 0) && (m_in.cols() > 0) && (m_in.isAllocated()));
    Matrix<T> m(m_in.rows(), m_in.cols());

    for (size_t r = 0; r < m_in.rows(); r++)
    {
        for (size_t c = 0; c < m_in.cols(); c++)
        {
            m(r, c) = std::sin(m_in(r, c));
        }
    }

    return m;
}

template <typename T> Matrix<T> sqrt(const Matrix<T>& m_in)
{
    assert((m_in.rows() > 0) && (m_in.cols() > 0) && (m_in.isAllocated()));
    Matrix<T> m(m_in.rows(), m_in.cols());

    for (size_t r = 0; r < m_in.rows(); r++)
    {
        for (size_t c = 0; c < m_in.cols(); c++)
        {
            m(r, c) = std::sqrt(m_in(r, c));
        }
    }

    return m;
}

template <typename T> T max(const Matrix<T>& m_in)
{
    assert((m_in.rows() > 0) && (m_in.cols() > 0) && (m_in.isAllocated()));
    T max_val = m_in(0, 0);

    for (size_t r = 0; r < m_in.rows(); r++)
    {
        for (size_t c = 0; c < m_in.cols(); c++)
        {
            max_val = std::max(max_val, m_in(r, c));
        }
    }

    return max_val;
}

template <typename T> T min(const Matrix<T>& m_in)
{
    assert((m_in.rows() > 0) && (m_in.cols() > 0) && (m_in.isAllocated()));
    T min_val = m_in(0, 0);

    for (size_t r = 0; r < m_in.rows(); r++)
    {
        for (size_t c = 0; c < m_in.cols(); c++)
        {
            min_val = std::min(min_val, m_in(r, c));
        }
    }

    return min_val;
}

template <typename T> T maxAbs(const Matrix<T>& m_in)
{
    assert((m_in.rows() > 0) && (m_in.cols() > 0) && (m_in.isAllocated()));
    T max_val = m_in(0, 0);

    for (size_t r = 0; r < m_in.rows(); r++)
    {
        for (size_t c = 0; c < m_in.cols(); c++)
        {
            max_val = std::max(max_val, std::abs(m_in(r, c)));
        }
    }

    return max_val;
}

template <typename T> T minAbs(const Matrix<T>& m_in)
{
    assert((m_in.rows() > 0) && (m_in.cols() > 0) && (m_in.isAllocated()));
    T min_val = m_in(0, 0);

    for (size_t r = 0; r < m_in.rows(); r++)
    {
        for (size_t c = 0; c < m_in.cols(); c++)
        {
            min_val = std::min(min_val, std::fabs(m_in(r, c)));
        }
    }

    return min_val;
}

template <typename T> Matrix<T> abs(const Matrix<T>& m_in)
{
    assert((m_in.rows() > 0) && (m_in.cols() > 0) && (m_in.isAllocated()));
    Matrix<T> m(m_in.rows(), m_in.cols());

    for (size_t r = 0; r < m_in.rows(); r++)
    {
        for (size_t c = 0; c < m_in.cols(); c++)
        {
            m(r, c) = std::fabs(m_in(r, c));
        }
    }

    return m;
}

template <typename T>
Matrix<T> linspaceFromPointsAndCountColMat(const T x0, const T x1, const size_t num_values)
{
    assert(num_values > 0);
    Matrix<T> m(num_values, 1);

    const T dx = (x1 - x0) / static_cast<T>(num_values - 1);
    m(0, 0) = x0;

    for (size_t r = 1; r < num_values; r++)
    {
        m(r, 0) = m(r - 1, 0) + dx;
    }

    return m;
}

template <typename T>
Matrix<T> linspaceFromPointIncAndCountColMat(const T x0, const T dx, const size_t num_values)
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

template <typename T> Matrix<T> linspaceFromPointsAndIncColMat(const T x0, const T x1, const T dx)
{
    assert(dx > 0);
    assert(x1 > x0);

    const size_t num_values = (x1 - x0) / dx;

    return linspaceFromPointsAndCountColMat(x0, x1, num_values);
}

template <typename U> size_t totalNumRowsInternal(const U& m)
{
    return m.rows();
}

template <typename U, typename... Us> size_t totalNumRowsInternal(const U& m, const Us&... matrices)
{
    return totalNumRowsInternal(matrices...) + m.rows();
}

template <typename... Us> size_t totalNumRows(const Us&... matrices)
{
    return totalNumRowsInternal(matrices...);
}

template <typename U> size_t totalNumColsInternal(const U& m)
{
    return m.cols();
}

template <typename U, typename... Us> size_t totalNumColsInternal(const U& m, const Us&... matrices)
{
    return totalNumColsInternal(matrices...) + m.cols();
}

template <typename... Us> size_t totalNumCols(const Us&... matrices)
{
    return totalNumColsInternal(matrices...);
}

template <typename T, typename U>
void hCatMatricesInternal(size_t col_idx, Matrix<T>& m_res, const U& mat)
{
    for (size_t r = 0; r < mat.rows(); r++)
    {
        for (size_t c = 0; c < mat.cols(); c++)
        {
            m_res(r, c + col_idx) = mat(r, c);
        }
    }
}

template <typename T, typename U, typename... Us>
void hCatMatricesInternal(size_t col_idx, Matrix<T>& m_res, const U& mat, const Us&... matrices)
{
    for (size_t r = 0; r < mat.rows(); r++)
    {
        for (size_t c = 0; c < mat.cols(); c++)
        {
            m_res(r, c + col_idx) = mat(r, c);
        }
    }

    hCatMatricesInternal(col_idx + mat.cols(), m_res, matrices...);
}

template <typename U, typename... Us>
Matrix<typename U::data_type> hCatMatrices(const U& mat, const Us&... matrices)
{
    Matrix<typename U::data_type> m_res(mat.rows(), totalNumCols(matrices...) + mat.cols());

    for (size_t r = 0; r < mat.rows(); r++)
    {
        for (size_t c = 0; c < mat.cols(); c++)
        {
            m_res(r, c) = mat(r, c);
        }
    }

    hCatMatricesInternal(mat.cols(), m_res, matrices...);

    return m_res;
}

template <typename T, typename U>
void vCatMatricesInternal(size_t row_idx, Matrix<T>& m_res, const U& mat)
{
    for (size_t r = 0; r < mat.rows(); r++)
    {
        for (size_t c = 0; c < mat.cols(); c++)
        {
            m_res(r + row_idx, c) = mat(r, c);
        }
    }
}

template <typename T, typename U, typename... Us>
void vCatMatricesInternal(size_t row_idx, Matrix<T>& m_res, const U& mat, const Us&... matrices)
{
    for (size_t r = 0; r < mat.rows(); r++)
    {
        for (size_t c = 0; c < mat.cols(); c++)
        {
            m_res(r + row_idx, c) = mat(r, c);
        }
    }

    vCatMatricesInternal(row_idx + mat.rows(), m_res, matrices...);
}

template <typename U, typename... Us>
Matrix<typename U::data_type> vCatMatrices(const U& mat, const Us&... matrices)
{
    Matrix<typename U::data_type> m_res(totalNumRows(matrices...) + mat.rows(), mat.cols());

    for (size_t r = 0; r < mat.rows(); r++)
    {
        for (size_t c = 0; c < mat.cols(); c++)
        {
            m_res(r, c) = mat(r, c);
        }
    }

    vCatMatricesInternal(mat.rows(), m_res, matrices...);

    return m_res;
}

}  // namespace arl

#endif