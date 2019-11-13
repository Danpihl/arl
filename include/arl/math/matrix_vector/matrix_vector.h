// Copyright 2019 Arrowtwig
#ifndef VECTOR_MATRIX_H_
#define VECTOR_MATRIX_H_

#include "arl/math/math_core.h"
#include "arl/math/matrix_vector/matrix.h"
#include "arl/math/matrix_vector/vec2d.h"
#include "arl/math/matrix_vector/vec3d.h"
#include "arl/math/matrix_vector/vec4d.h"
#include "arl/math/matrix_vector/vector.h"
#include "arl/math/misc/math_macros.h"
#include "arl/utilities/logging.h"

#include <cmath>

namespace arl
{
template <typename T> void Matrix<T>::addVectorToMatrixCols(const Vector<T>& v)
{
    ASSERT(is_allocated_) << "Matrix not allocated!";
    ASSERT(v.isAllocated()) << "Vector not allocated!";
    ASSERT(num_rows_ == v.size()) << "Error in dimension!";

    for (size_t c = 0; c < num_cols_; c++)
    {
        for (size_t r = 0; r < num_rows_; r++)
        {
            data_[r * num_cols_ + c] = data_[r * num_cols_ + c] + v(r);
        }
    }
}

template <typename T> void Matrix<T>::addVectorToMatrixRows(const Vector<T>& v)
{
    ASSERT(is_allocated_) << "Matrix not allocated!";
    ASSERT(v.isAllocated()) << "Vector not allocated!";
    ASSERT(num_cols_ == v.size()) << "Error in dimension!";

    for (size_t r = 0; r < num_rows_; r++)
    {
        for (size_t c = 0; c < num_cols_; c++)
        {
            data_[r * num_cols_ + c] = data_[r * num_cols_ + c] + v(c);
        }
    }
}

template <typename T> Vector<T> Matrix<T>::getColumnVector(size_t column_idx) const
{
    ASSERT(column_idx < num_cols_) << "Tried to access column outside of matrix bounds!";
    Vector<T> column_vector(num_rows_);

    for (size_t k = 0; k < num_rows_; k++)
    {
        column_vector(k) = data_[num_cols_ * k + column_idx];
    }
    return column_vector;
}

template <typename T> Vector<T> Matrix<T>::getRowVector(size_t row_idx) const
{
    ASSERT(row_idx < num_rows_) << "Tried to access row outside of matrix bounds!";
    Vector<T> row_vector(num_cols_);

    for (size_t k = 0; k < num_cols_; k++)
    {
        row_vector(k) = data_[num_cols_ * row_idx + k];
    }
    return row_vector;
}

template <typename T> void Matrix<T>::hCat(const Vector<T>& v)
{
    ASSERT(is_allocated_) << "Matrix not allocated!";
    ASSERT(v.isAllocated()) << "Vector not allocated!";
    ASSERT(num_rows_ == v.size()) << "Mismatch in number of cols!";

    T* temp_data;
    DATA_ALLOCATION(temp_data, num_rows_ * (num_cols_ + 1), T, "Matrix");

    for (size_t r = 0; r < num_rows_; r++)
    {
        for (size_t c = 0; c < num_rows_; c++)
        {
            temp_data[r * num_cols_ + c] = data_[r * num_cols_ + c];
        }
    }

    num_cols_ = num_cols_ + 1;

    for (size_t r = 0; r < num_rows_; r++)
    {
        temp_data[r * num_cols_ + num_cols_ - 1] = v(r);
    }

    delete[] data_;
    data_ = temp_data;
}

template <typename T> void Matrix<T>::vCat(const Vector<T>& v)
{
    ASSERT(is_allocated_) << "Matrix not allocated!";
    ASSERT(v.isAllocated()) << "Vector not allocated!";
    ASSERT(num_rows_ == v.size()) << "Mismatch in number of cols!";

    T* temp_data;
    DATA_ALLOCATION(temp_data, (num_rows_ + 1) * num_cols_, T, "Matrix");

    for (size_t r = 0; r < num_rows_; r++)
    {
        for (size_t c = 0; c < num_rows_; c++)
        {
            temp_data[r * num_cols_ + c] = data_[r * num_cols_ + c];
        }
    }

    num_rows_ = num_rows_ + 1;

    for (size_t c = 0; c < num_rows_; c++)
    {
        temp_data[(num_rows_ - 1) * num_cols_ + c] = v(c);
    }

    delete[] data_;
    data_ = temp_data;
}

template <typename T> Matrix<T> hCat(const Matrix<T>& m, const Vector<T>& v)
{
    ASSERT(m.isAllocated()) << "Matrix not allocated!";
    ASSERT(v.isAllocated()) << "Vector not allocated!";

    ASSERT(m.rows() == v.size()) << "Mismatch in number of cols!";

    Matrix<T> mres(m.rows(), m.cols() + 1);

    for (size_t r = 0; r < m.rows(); r++)
    {
        for (size_t c = 0; c < m.cols(); c++)
        {
            mres(r, c) = m(r, c);
        }
    }

    for (size_t r = 0; r < m.rows(); r++)
    {
        mres(r, mres.endColIdx()) = v(r);
    }

    return mres;
}

template <typename T> Matrix<T> vCat(const Matrix<T>& m, const Vector<T>& v)
{
    ASSERT(m.isAllocated()) << "Matrix not allocated!";
    ASSERT(v.isAllocated()) << "Vector not allocated!";

    ASSERT(m.cols() == v.size()) << "Mismatch in number of cols!";

    Matrix<T> mres(m.rows() + 1, m.cols());

    for (size_t r = 0; r < m.rows(); r++)
    {
        for (size_t c = 0; c < m.cols(); c++)
        {
            mres(r, c) = m(r, c);
        }
    }

    for (size_t c = 0; c < m.cols(); c++)
    {
        mres(mres.endRowIdx(), c) = v(c);
    }

    return mres;
}

template <typename T> Matrix<T> hCat(const Vector<T>& v, const Matrix<T>& m)
{
    Matrix<T> m0(v.size(), 1);
    return vCat(m0, m);
}

template <typename T> Matrix<T> vCat(const Vector<T>& v, const Matrix<T>& m)
{
    Matrix<T> m0(1, v.size());
    return vCat(m0, m);
}

template <typename T> Matrix<T> hCat(const Matrix<T>& m, const Vec4D<T>& v)
{
    Vector<T> vg = v.toVector();
    return hCat(m, vg);
}

template <typename T> Matrix<T> vCat(const Matrix<T>& m, const Vec4D<T>& v)
{
    Vector<T> vg = v.toVector();
    return vCat(m, vg);
}

template <typename T> Matrix<T> hCat(const Matrix<T>& m, const Vec3D<T>& v)
{
    Vector<T> vg = v.toVector();
    return hCat(m, vg);
}

template <typename T> Matrix<T> vCat(const Matrix<T>& m, const Vec3D<T>& v)
{
    Vector<T> vg = v.toVector();
    return vCat(m, vg);
}

template <typename T> Matrix<T> hCat(const Matrix<T>& m, const Vec2D<T>& v)
{
    Vector<T> vg = v.toVector();
    return hCat(m, vg);
}

template <typename T> Matrix<T> vCat(const Matrix<T>& m, const Vec2D<T>& v)
{
    Vector<T> vg = v.toVector();
    return vCat(m, vg);
}

template <typename T> Matrix<T> hCat(const Vec4D<T>& v, const Matrix<T>& m)
{
    Vector<T> vg = v.toVector();
    return hCat(vg, m);
}

template <typename T> Matrix<T> vCat(const Vec4D<T>& v, const Matrix<T>& m)
{
    Vector<T> vg = v.toVector();
    return vCat(vg, m);
}

template <typename T> Matrix<T> hCat(const Vec3D<T>& v, const Matrix<T>& m)
{
    Vector<T> vg = v.toVector();
    return hCat(vg, m);
}

template <typename T> Matrix<T> vCat(const Vec3D<T>& v, const Matrix<T>& m)
{
    Vector<T> vg = v.toVector();
    return vCat(vg, m);
}

template <typename T> Matrix<T> hCat(const Vec2D<T>& v, const Matrix<T>& m)
{
    Vector<T> vg = v.toVector();
    return hCat(vg, m);
}

template <typename T> Matrix<T> vCat(const Vec2D<T>& v, const Matrix<T>& m)
{
    Vector<T> vg = v.toVector();
    return vCat(vg, m);
}

template <typename T>
Vector<T> Matrix<T>::operator()(const size_t row, const IndexSpan& col_idx_span) const
{
    const size_t new_vec_length = col_idx_span.to - col_idx_span.from + 1;

    assert((row < num_rows_) && (col_idx_span.to < num_cols_));

    Vector<T> vec(new_vec_length);

    for (size_t c = 0; c < new_vec_length; c++)
    {
        vec(c) = data_[row * num_cols_ + c + col_idx_span.from];
    }

    return vec;
}

template <typename T>
Vector<T> Matrix<T>::operator()(const IndexSpan& row_idx_span, const size_t col) const
{
    const size_t new_vec_length = row_idx_span.to - row_idx_span.from + 1;

    assert((row_idx_span.to < num_rows_) && (col < num_cols_));

    Vector<T> vec(new_vec_length);

    for (size_t r = 0; r < new_vec_length; r++)
    {
        vec(r) = data_[(r + row_idx_span.from) * num_cols_ + col];
    }

    return vec;
}

template <typename T> Matrix<T> Vector<T>::outerProduct(const Vector<T>& v) const
{
    assert(vector_length_ == v.size());
    Matrix<T> mat(vector_length_, vector_length_);

    for (size_t r = 0; r < vector_length_; r++)
    {
        for (size_t c = 0; c < vector_length_; c++)
        {
            mat(r, c) = data_[r] * v(c);
        }
    }

    return mat;
}

template <typename T> Matrix<T> Vector<T>::toColumnVectorMat() const
{
    Matrix<T> mres(vector_length_, 1);

    for (size_t r = 0; r < vector_length_; r++)
    {
        mres(r, 0) = data_[r];
    }

    return mres;
}

template <typename T> Matrix<T> Vector<T>::toRowVectorMat() const
{
    Matrix<T> mres(1, vector_length_);

    for (size_t c = 0; c < vector_length_; c++)
    {
        mres(0, c) = data_[c];
    }

    return mres;
}

// Vec234D

template <typename T> Matrix<T> Vec2D<T>::outerProduct(const Vec2D<T>& v) const
{
    Vector<T> vv0 = toVector();
    Vector<T> vv1 = v.toVector();

    return vv0.outerProduct(vv1);
}

template <typename T> Matrix<T> Vec3D<T>::outerProduct(const Vec3D<T>& v) const
{
    Vector<T> vv0 = toVector();
    Vector<T> vv1 = v.toVector();

    return vv0.outerProduct(vv1);
}

template <typename T> Vec4D<T> Vector<T>::toVec4D() const
{
    ASSERT(is_allocated_) << "Error, parent vector not allocated!";
    ASSERT(vector_length_ >= 4) << "Error, parent vector not of size 4 or larger!";
    Vec4D<T> v(data_[0], data_[1], data_[2], data_[3]);
    return v;
}

template <typename T> Vec3D<T> Vector<T>::toVec3D() const
{
    ASSERT(is_allocated_) << "Error, parent vector not allocated!";
    ASSERT(vector_length_ >= 3) << "Error, parent vector not of size 3 or larger!";
    Vec3D<T> v(data_[0], data_[1], data_[2]);
    return v;
}

template <typename T> Vec2D<T> Vector<T>::toVec2D() const
{
    ASSERT(is_allocated_) << "Error, parent vector not allocated!";
    ASSERT(vector_length_ >= 2) << "Error, parent vector not of size 2 or larger!";
    Vec2D<T> v(data_[0], data_[1]);
    return v;
}

template <typename T> Matrix<T> Vec4D<T>::outerProduct(const Vec4D<T>& v) const
{
    Vector<T> vv0 = toVector();
    Vector<T> vv1 = v.toVector();

    /*vv0(0) = x;
    vv0(1) = y;
    vv0(2) = z;
    vv0(3) = w;

    vv1(0) = v.x;
    vv1(1) = v.y;
    vv1(2) = v.z;
    vv1(3) = v.w;*/

    return vv0.outerProduct(vv1);
}

template <typename T> Vector<T> Vec2D<T>::toVector() const
{
    const Vector<T> v({x, y});
    return v;
}

template <typename T> Vector<T> Vec3D<T>::toVector() const
{
    const Vector<T> v({x, y, z});
    return v;
}

template <typename T> Vector<T> Vec4D<T>::toVector() const
{
    const Vector<T> v({x, y, z, w});
    return v;
}

template <typename T> Matrix<T> Vec3D<T>::toCrossProductMatrix() const
{
    Matrix<T> m(3, 3);
    m(0, 0) = 0.0;
    m(0, 1) = -z;
    m(0, 2) = y;

    m(1, 0) = z;
    m(1, 1) = 0.0;
    m(1, 2) = -x;

    m(2, 0) = -y;
    m(2, 1) = x;
    m(2, 2) = 0.0;
    return m;
}

template <typename T> Vec3D<T> crossProductMatrixToVec3D(const Matrix<T>& m)
{
    return Vec3D<T>(m(2, 1), m(0, 2), m(1, 0));
}

template <typename T>
AxisAngle<T> estimateRotationFromTwoVectors(const Vec3D<T>& v_unrotated, const Vec3D<T>& v_rotated)
{
    Vec3D<T> rotation_vector = v_unrotated.crossProduct(v_rotated);
    T phi = v_unrotated.angleBetweenVectors(v_rotated);

    return AxisAngle<T>(phi, rotation_vector.x, rotation_vector.y, rotation_vector.z);
}

}  // namespace arl

#endif
