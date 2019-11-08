// Copyright 2019 Arrowtwig
#ifndef SPHERE_H_
#define SPHERE_H_

#include "arl/math/math_core.h"
#include "arl/math/matrix_vector/matrix_vector_headers.h"

#include <cmath>
#include <vector>

namespace arl
{
template <typename T>
Sphere<T>::Sphere(const T r_, const Point3D<T> &c_)
{
    r = r_;
    c = c_;
}
template <typename T>
Sphere<T>::Sphere() {}

template <typename T>
bool Sphere<T>::doesLineIntersect(const Line3D<T> &line) const
{
    const Point3D<T> closest_point = line.closestPointOnLineFromPoint(c);

    // T distance_between_points = (closest_point - c).squaredNorm();
    // return distance_between_points < r * r;

    T distance_between_points = (closest_point - c).norm();
    return distance_between_points < r;
}

template <typename T>
std::vector<Point3D<T>> Sphere<T>::lineIntersectionPoint(const Line3D<T> &line) const
{
    // There are two intersection points
    std::vector<Point3D<T>> intersection_points = {Point3D<T>(), Point3D<T>()};

    if (!doesLineIntersect(line))
    {
        intersection_points[0].x = NAN;
        intersection_points[0].y = NAN;
        intersection_points[0].z = NAN;

        intersection_points[1].x = NAN;
        intersection_points[1].y = NAN;
        intersection_points[1].z = NAN;
    }
    else
    {
        const Vec3D<T> normalized_line_vector = line.v.normalized();
        const Point3D<T> closest_point = line.closestPointOnLineFromPoint(c);

        T squared_distance_between_points = (closest_point - c).squaredNorm();

        T cath = std::sqrt(squared_distance_between_points - r * r);

        intersection_points[0] = c + cath * normalized_line_vector;
        intersection_points[1] = c - cath * normalized_line_vector;
    }

    return intersection_points;
}

} // namespace arl

#endif
