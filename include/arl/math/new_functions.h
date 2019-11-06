#ifndef NEW_MATRIX_FUNCTIONS_H_
#define NEW_MATRIX_FUNCTIONS_H_

#include "arl/math/math_core.h"
#include "arl/math/matrix_vector/matrix_vector_headers.h"

namespace arl
{
//

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
