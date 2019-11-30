#ifndef NEW_MATRIX_FUNCTIONS_H_
#define NEW_MATRIX_FUNCTIONS_H_

#include "arl/math/math_core.h"
#include "arl/math/matrix_vector/matrix_vector_headers.h"

#define ASSERT_MAT_VALID(mat)                             \
    ASSERT(mat.isAllocated()) << "Matrix not allocated!"; \
    ASSERT(mat.rows() > 0) << "Number of rows is 0!";     \
    ASSERT(mat.cols() > 0) << "Number of cols is 0!"

#define ASSERT_MAT_VALID_INTERNAL()                   \
    ASSERT(is_allocated_) << "Matrix not allocated!"; \
    ASSERT(num_rows_ > 0) << "Number of rows is 0!";  \
    ASSERT(num_cols_ > 0) << "Number of cols is 0!"

#define ASSERT_VEC_VALID_INTERNAL()                   \
    ASSERT(is_allocated_) << "Vector not allocated!"; \
    ASSERT(num_elements_ > 0) << "Number of elements is 0!"

namespace arl
{
/*template <typename T> class Matrix
{
private:
    Vector<T> sub_row_vec;
    Vector<T> sub_col_vec;

public:
};*/

template <typename T> T Matrix<T>::max() const
{
    ASSERT_MAT_VALID_INTERNAL();

    T max_val = data_[0];
    for (size_t c = 1; c < num_cols_; c++)
    {
        max_val = std::max(max_val, data_[c]);
    }

    for (size_t r = 1; r < num_rows_; r++)
    {
        T max_val_internal = data_[r * num_cols_];
        for (size_t c = 1; c < num_cols_; c++)
        {
            max_val_internal = std::max(max_val_internal, data_[r * num_cols_ + c]);
        }
        max_val = std::max(max_val, max_val_internal);
    }

    return max_val;
}

template <typename T> T Matrix<T>::min() const
{
    ASSERT_MAT_VALID_INTERNAL();

    T min_val = data_[0];
    for (size_t c = 1; c < num_cols_; c++)
    {
        min_val = std::min(min_val, data_[c]);
    }

    for (size_t r = 1; r < num_rows_; r++)
    {
        T min_val_internal = data_[r * num_cols_];
        for (size_t c = 1; c < num_cols_; c++)
        {
            min_val_internal = std::min(min_val_internal, data_[r * num_cols_ + c]);
        }
        min_val = std::min(min_val, min_val_internal);
    }

    return min_val;
}

template <typename T> Matrix<T> Matrix<T>::minAlongCols() const
{
    // Creates a vector with same number of elements as "num_cols_",
    // and each element in the vector is the min value of its corresponding column
    ASSERT_MAT_VALID_INTERNAL();
    Matrix<T> mres(1, num_cols_);

    for (size_t c = 0; c < num_cols_; c++)
    {
        mres(0, c) = data_[c];
    }

    for (size_t c = 0; c < num_cols_; c++)
    {
        for (size_t r = 1; r < num_rows_; r++)
        {
            mres(0, c) = std::min(mres(0, c), data_[r * num_cols_ + c]);
        }
    }

    return mres;
}

template <typename T> Matrix<T> Matrix<T>::minAlongRows() const
{
    // Creates a vector with same number of elements as "num_rows_",
    // and each element in the vector is the min value of its corresponding row
    ASSERT_MAT_VALID_INTERNAL();
    Matrix<T> mres(num_rows_, 1);

    for (size_t r = 0; r < num_rows_; r++)
    {
        mres(r, 0) = data_[r * num_cols_];
    }

    for (size_t r = 0; r < num_rows_; r++)
    {
        for (size_t c = 1; c < num_cols_; c++)
        {
            mres(r, 0) = std::min(mres(r, 0), data_[r * num_cols_ + c]);
        }
    }

    return mres;
}

template <typename T> Matrix<T> Matrix<T>::maxAlongCols() const
{
    // Creates a vector with same number of elements as "num_cols_",
    // and each element in the vector is the max value of its corresponding column
    ASSERT_MAT_VALID_INTERNAL();
    Matrix<T> mres(1, num_cols_);

    for (size_t c = 0; c < num_cols_; c++)
    {
        mres(0, c) = data_[c];
    }

    for (size_t c = 0; c < num_cols_; c++)
    {
        for (size_t r = 1; r < num_rows_; r++)
        {
            mres(0, c) = std::max(mres(0, c), data_[r * num_cols_ + c]);
        }
    }

    return mres;
}

template <typename T> Matrix<T> Matrix<T>::maxAlongRows() const
{
    // Creates a vector with same number of elements as "num_rows_",
    // and each element in the vector is the min value of its corresponding row
    ASSERT_MAT_VALID_INTERNAL();
    Matrix<T> mres(num_rows_, 1);

    for (size_t r = 0; r < num_rows_; r++)
    {
        mres(r, 0) = data_[r * num_cols_];
    }

    for (size_t r = 0; r < num_rows_; r++)
    {
        for (size_t c = 1; c < num_cols_; c++)
        {
            mres(r, 0) = std::max(mres(r, 0), data_[r * num_cols_ + c]);
        }
    }

    return mres;
}

template <typename T> T Matrix<T>::sum() const
{
    T s = 0.0;
    for (size_t r = 0; r < num_rows_; r++)
    {
        for (size_t c = 0; c < num_cols_; c++)
        {
            s = s + data_[r * num_cols_ + c];
        }
    }
    return s;
}

template <typename T> Matrix<T> Matrix<T>::sumAlongRows() const
{
    Matrix<T> mres(num_rows_, 1);
    for (size_t r = 0; r < num_rows_; r++)
    {
        T s = 0.0;
        for (size_t c = 0; c < num_cols_; c++)
        {
            s = s + data_[r * num_cols_ + c];
        }
        mres(r, 0) = s;
    }
    return mres;
}

template <typename T> Matrix<T> Matrix<T>::sumAlongCols() const
{
    Matrix<T> mres(1, num_cols_);
    for (size_t c = 0; c < num_cols_; c++)
    {
        T s = 0.0;
        for (size_t r = 0; r < num_rows_; r++)
        {
            s = s + data_[r * num_cols_ + c];
        }
        mres(0, c) = s;
    }
    return mres;
}

template <typename T> T Vector<T>::min() const
{
    // ASSERT_VEC_VALID_INTERNAL();
    T min_val = data_[0];

    for (size_t k = 1; k < vector_length_; k++)
    {
        min_val = std::min(data_[k], min_val);
    }

    return min_val;
}

template <typename T> T Vector<T>::max() const
{
    // ASSERT_VEC_VALID_INTERNAL();
    T max_val = data_[0];

    for (size_t k = 1; k < vector_length_; k++)
    {
        max_val = std::max(data_[k], max_val);
    }

    return max_val;
}

template <typename T> T Vector<T>::sum() const
{
    T s = 0.0;

    for (size_t k = 0; k < vector_length_; k++)
    {
        s = s + data_[k];
    }

    return s;
}
//

template <typename T> T angleBetweenVectors(const Vec3D<T> v0, const Vec3D<T> v1)
{
    return std::acos((v0 * v1) / (v0.norm() * v1.norm()));
}

template <typename T> T cosOfAngleBetweenVectors(const Vec3D<T> v0, const Vec3D<T> v1)
{
    return v0 * v1 / (v0.norm() * v1.norm());
}

template <typename T> Vec3D<T> projectVectorOntoVector(const Vec3D<T> v0, const Vec3D<T> v1)
{
    // Projects v0 onto v1
    return v0.norm() * cosOfAngleBetweenVectors(v0, v1) * v1.normalized();
}

template <typename T> Line3D<T> Plane<T>::projectLineOntoPlane(const Line3D<T>& line) const
{
    const Vec3D<T> line_vector = line.v;
    const Vec3D<T> plane_normal_vector(a, b, c);
    const T angle_between_vectors = line_vector.angleBetweenVectors();
    if (std::fabs(angle_between_vectors) < 1e-8)
    {
        LOG_WARNING() << "Line and plane normal vector almost parallel, degenerate case!";
    }
    const Point3D<T> p0 = line.p;
    const Point3D<T> p1 = line.p + line.v.normalized();
    const Point3D<T> pp0 = closestPointOnPlaneFromPoint(p0);
    const Point3D<T> pp1 = closestPointOnPlaneFromPoint(p1);
    return lineFromTwoPoints(pp0, pp1);
}

template <typename T> bool Circle2D<T>::isPointInCircle(const Point2D<T>& p) const
{
    if ((p - c).norm() < r)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T> bool Circle2D<T>::doesCircleIntersectThis(const Circle2D<T>& circle) const
{
    const T distance_between_centers = (circle.c - c).norm();
    if (distance_between_centers < (r + circle.r))
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
std::pair<Point2D<T>, Point2D<T>> Circle2D<T>::circleIntersection(const Circle2D<T>& circle) const
{
    if (!doesCircleIntersect(circle))
    {
        return std::pair<Point2D<T>, Point2D<T>>(Point2D<T>(NAN, NAN), Point2D<T>(NAN, NAN));
    }
    else
    {
        const Point2D<T> c0 = c;
        const Point2D<T> c1 = circle.c;
        const T r0 = r;
        const T r1 = circle.r;

        const Point2D<T> s0, s1;

        s0.x =
            (c0.x * c0.y * c0.y - c0.x * c0.x * c1.x - c0.x * c1.x * c1.x + c0.x * c1.y * c1.y +
                 c1.x * c0.y * c0.y + c1.x * c1.y * c1.y - c0.x * r0 * r0 + c0.x * r1 * r1 +
                 c1.x * r0 * r0 - c1.x * r1 * r1 + c0.x * c0.x * c0.x + c1.x * c1.x * c1.x -
                 c0.y * ((-c0.x * c0.x + 2.0 * c0.x * c1.x - c1.x * c1.x - c0.y * c0.y +
                          2.0 * c0.y * c1.y - c1.y * c1.y + r0 * r0 + 2.0 * r0 * r1 + r1 * r1) *
                         (c0.x * c0.x - 2.0 * c0.x * c1.x + c1.x * c1.x + c0.y * c0.y -
                          2.0 * c0.y * c1.y + c1.y * c1.y - r0 * r0 + 2.0 * r0 * r1 - r1 * r1)) ^
             0.5 + c1.y * ((-c0.x * c0.x + 2.0 * c0.x * c1.x - c1.x * c1.x - c0.y * c0.y +
                            2.0 * c0.y * c1.y - c1.y * c1.y + r0 * r0 + 2.0 * r0 * r1 + r1 * r1) *
                           (c0.x * c0.x - 2.0 * c0.x * c1.x + c1.x * c1.x + c0.y * c0.y -
                            2.0 * c0.y * c1.y + c1.y * c1.y - r0 * r0 + 2.0 * r0 * r1 - r1 * r1)) ^
             0.5 - 2.0 * c0.x * c0.y * c1.y - 2.0 * c1.x * c0.y * c1.y) /
            (2.0 * (c0.x * c0.x - 2.0 * c0.x * c1.x + c1.x * c1.x + c0.y * c0.y -
                    2.0 * c0.y * c1.y + c1.y * c1.y));
        s1.x =
            (c0.x * c0.y * c0.y - c0.x * c0.x * c1.x - c0.x * c1.x * c1.x + c0.x * c1.y * c1.y +
                 c1.x * c0.y * c0.y + c1.x * c1.y * c1.y - c0.x * r0 * r0 + c0.x * r1 * r1 +
                 c1.x * r0 * r0 - c1.x * r1 * r1 + c0.x * c0.x * c0.x + c1.x * c1.x * c1.x +
                 c0.y * ((-c0.x * c0.x + 2.0 * c0.x * c1.x - c1.x * c1.x - c0.y * c0.y +
                          2.0 * c0.y * c1.y - c1.y * c1.y + r0 * r0 + 2.0 * r0 * r1 + r1 * r1) *
                         (c0.x * c0.x - 2.0 * c0.x * c1.x + c1.x * c1.x + c0.y * c0.y -
                          2.0 * c0.y * c1.y + c1.y * c1.y - r0 * r0 + 2.0 * r0 * r1 - r1 * r1)) ^
             0.5 - c1.y * ((-c0.x * c0.x + 2.0 * c0.x * c1.x - c1.x * c1.x - c0.y * c0.y +
                            2.0 * c0.y * c1.y - c1.y * c1.y + r0 * r0 + 2.0 * r0 * r1 + r1 * r1) *
                           (c0.x * c0.x - 2.0 * c0.x * c1.x + c1.x * c1.x + c0.y * c0.y -
                            2.0 * c0.y * c1.y + c1.y * c1.y - r0 * r0 + 2.0 * r0 * r1 - r1 * r1)) ^
             0.5 - 2.0 * c0.x * c0.y * c1.y - 2.0 * c1.x * c0.y * c1.y) /
            (2.0 * (c0.x * c0.x - 2.0 * c0.x * c1.x + c1.x * c1.x + c0.y * c0.y -
                    2.0 * c0.y * c1.y + c1.y * c1.y));

        s0.y =
            (c0.x * c0.x * c0.y + c0.x * c0.x * c1.y + c1.x * c1.x * c0.y + c1.x * c1.x * c1.y -
                 c0.y * c1.y * c1.y - c0.y * c0.y * c1.y - c0.y * r0 * r0 + c0.y * r1 * r1 +
                 c1.y * r0 * r0 - c1.y * r1 * r1 + c0.y * c0.y * c0.y + c1.y * c1.y * c1.y +
                 c0.x * ((-c0.x * c0.x + 2.0 * c0.x * c1.x - c1.x * c1.x - c0.y * c0.y +
                          2.0 * c0.y * c1.y - c1.y * c1.y + r0 * r0 + 2.0 * r0 * r1 + r1 * r1) *
                         (c0.x * c0.x - 2.0 * c0.x * c1.x + c1.x * c1.x + c0.y * c0.y -
                          2.0 * c0.y * c1.y + c1.y * c1.y - r0 * r0 + 2.0 * r0 * r1 - r1 * r1)) ^
             0.5 - c1.x * ((-c0.x * c0.x + 2.0 * c0.x * c1.x - c1.x * c1.x - c0.y * c0.y +
                            2.0 * c0.y * c1.y - c1.y * c1.y + r0 * r0 + 2.0 * r0 * r1 + r1 * r1) *
                           (c0.x * c0.x - 2.0 * c0.x * c1.x + c1.x * c1.x + c0.y * c0.y -
                            2.0 * c0.y * c1.y + c1.y * c1.y - r0 * r0 + 2.0 * r0 * r1 - r1 * r1)) ^
             0.5 - 2.0 * c0.x * c1.x * c0.y - 2.0 * c0.x * c1.x * c1.y) /
            (2.0 * (c0.x * c0.x - 2.0 * c0.x * c1.x + c1.x * c1.x + c0.y * c0.y -
                    2.0 * c0.y * c1.y + c1.y * c1.y));
        s1.y =
            (c0.x * c0.x * c0.y + c0.x * c0.x * c1.y + c1.x * c1.x * c0.y + c1.x * c1.x * c1.y -
                 c0.y * c1.y * c1.y - c0.y * c0.y * c1.y - c0.y * r0 * r0 + c0.y * r1 * r1 +
                 c1.y * r0 * r0 - c1.y * r1 * r1 + c0.y * c0.y * c0.y + c1.y * c1.y * c1.y -
                 c0.x * ((-c0.x * c0.x + 2.0 * c0.x * c1.x - c1.x * c1.x - c0.y * c0.y +
                          2.0 * c0.y * c1.y - c1.y * c1.y + r0 * r0 + 2.0 * r0 * r1 + r1 * r1) *
                         (c0.x * c0.x - 2.0 * c0.x * c1.x + c1.x * c1.x + c0.y * c0.y -
                          2.0 * c0.y * c1.y + c1.y * c1.y - r0 * r0 + 2.0 * r0 * r1 - r1 * r1)) ^
             0.5 + c1.x * ((-c0.x * c0.x + 2.0 * c0.x * c1.x - c1.x * c1.x - c0.y * c0.y +
                            2.0 * c0.y * c1.y - c1.y * c1.y + r0 * r0 + 2.0 * r0 * r1 + r1 * r1) *
                           (c0.x * c0.x - 2.0 * c0.x * c1.x + c1.x * c1.x + c0.y * c0.y -
                            2.0 * c0.y * c1.y + c1.y * c1.y - r0 * r0 + 2.0 * r0 * r1 - r1 * r1)) ^
             0.5 - 2.0 * c0.x * c1.x * c0.y - 2.0 * c0.x * c1.x * c1.y) /
            (2.0 * (c0.x * c0.x - 2.0 * c0.x * c1.x + c1.x * c1.x + c0.y * c0.y -
                    2.0 * c0.y * c1.y + c1.y * c1.y));
        return std::pair<Point2D<T>, Point2D<T>>(s0, s1);
    }
}

template <typename T> Vec3D<T> Vec3D<T>::perpendicularVector() const
{
    if ((x == 0) && (y == 0) && (z == 0))
    {
        return Vec3D<T>(NAN, NAN, NAN);
    }
    else
    {
        const T a = x;
        const T b = y;
        const T c = z;
        T xn, yn, zn;
        if (x >= y && x >= z)
        {
            yn = 1.0;
            zn = 1.0;
            xn = -(b * yn + c * zn) / a;
        }
        else if (y >= x && y >= z)
        {
            xn = 1.0;
            zn = 1.0;
            yn = -(a * xn + c * zn) / b;
        }
        else if (z >= x && z >= y)
        {
            xn = 1.0;
            yn = 1.0;
            zn = -(a * xn + b * yn) / c;
        }

        return Vec3D<T>(xn, yn, zn);
    }
}

template <typename T>
AxisAngle<T> findAxisAngleBetweenVectors(const Vec3D<T>& v0, const Vec3D<T>& v1)
{
    const Vec3D<T> normal_vec = v0.crossProduct(v1);
    const T angle_between_vectors = v0.angleBetweenVectors(v1);
    return AxisAngle<T>(angle_between_vectors, normal_vec.x, normal_vec.y, normal_vec.z);
}

/*
template <typename T>
AxisAngle<T>::AxisAngle(const T phi_, const T x_, const T y_, const T z_)
{
    if(phi_ == 0.0 || ((x_ == 0) && (y_ == 0) && (z_ == 0)))
    {
        phi = 0.0;
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }
    else
    {
        phi = phi_;
        const T d = std::sqrt(x_*x_ + y_*y_ + z_*z_);
        x = x_ / d;
        y = y_ / d;
        z = z_ / d;
    }
}
*/

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

/*
template <typename T>
Circle2D<T> circleFromThreePoints(const Point2D<T>& p0, const Point2D<T>& p1, const Point2D<T>& p2)
{
    const Point2D<T> pc = (p0 + p1) / 2.0;
    const Vec2D<T> vn = p0 - p1;
    const Vec2D<T> v(-vn.y, vn.x);
    const T t = ((p0.x - pc.x) * (p0.x - pc.x) - (p2.x - pc.x) * (p2.x - pc.x) +
                 (p0.y - pc.y) * (p0.y - pc.y) - (p2.y - pc.y) * (p2.y - pc.y)) /
                (2.0 * v.x * (p0.x - pc.x) - 2.0 * v.x * (p2.x - pc.x) + 2.0 * v.y * (p0.y - pc.y) -
                 2.0 * v.y * (p2.y - pc.y));

    const Point2D<T> center_point = pc + t * v;
    const T radius = (p0 - center_point).norm();

    return Circle2D<T>(radius, center_point);
}
*/

}  // namespace arl

#endif
