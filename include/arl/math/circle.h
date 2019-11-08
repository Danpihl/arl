// Copyright 2019 Arrowtwig
#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "arl/math/math_core.h"
#include "arl/math/matrix_vector/matrix_vector_headers.h"

#include <cmath>

#include <vector>

namespace arl
{
/* **************************************************************** */
/* ************************** Section 2D ************************** */
/* **************************************************************** */
template <typename T>
Circle2D<T>::Circle2D(const T r_, const T cx_, const T cy_)
{
    r = r_;
    c.x = cx_;
    c.y = cy_;
}

template <typename T>
Circle2D<T>::Circle2D(const T r_, const Vec2D<T> &c_)
{
    r = r_;
    c.x = c_.x;
    c.y = c_.y;
}

template <typename T>
Circle2D<T>::Circle2D() {}

template <typename T>
HomogeneousLine2D<T> Circle2D<T>::tangentLine(const T angle) const
{
    // Computes the tangent line that touches the point P = [r*cos(angle); r*sin(angle)]
    Point2D<T> perimiter_point = r * Point2D<T>(std::cos(angle), std::sin(angle));
    Vec2D<T> center_to_perimiter_vector = c.vectorBetweenPoints(perimiter_point);

    HomogeneousLine2D<T> line =
        HomogeneousLine2D<T>(center_to_perimiter_vector.x, center_to_perimiter_vector.y, 0);
    line.c = -(line.a * perimiter_point.x + line.b * perimiter_point.y);

    return line;
}

template <typename T>
bool Circle2D<T>::doesLineIntersect(const HomogeneousLine2D<T> &line) const
{
    float centerpoint_line_distance = line.pointDistanceFromLine(c);
    if (centerpoint_line_distance < r)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
Point2D<T> Circle2D<T>::closestPointOnPerimeterFromPoint(const Point2D<T> &p) const
{
    Vec2D<T> center_to_point_vector = c.normalizedVectorBetweenPoints(p);
    return c + r * center_to_point_vector;
}

template <typename T>
std::vector<Point2D<T>> Circle2D<T>::lineIntersectionPoints(const HomogeneousLine2D<T> &line) const
{
    // Derived using
    // E1 = cy - sqrt(r^2 - (x - cx)^2) == -(a*x + c)/b
    // E2 = cy + sqrt(r^2 - (x - cx)^2) == -(a*x + c)/b

    std::vector<Point2D<T>> return_vector = {Point2D<T>(0.0, 0.0), Point2D<T>(0.0, 0.0)};
    return_vector.resize(2);

    if (this->doesLineIntersect(line))
    {
        const float a = line.a;
        const float b = line.b;
        const float c_ = line.c;
        const float cx = c.x;
        const float cy = c.y;
        const float r = r;
        const float a2 = a * a;
        const float b2 = b * b;
        const float c2 = c * c;
        const float r2 = r * r;
        const float a2b2 = a2 + b2;
        const float cx2 = cx * cx;
        const float cy2 = cy * cy;

        // x0 = -(a*c + b*(- a^2*cx^2 + a^2*r^2 - 2*a*b*cx*cy - 2*a*c*cx - b^2*cy^2 + b^2*r^2 -
        // 2*b*c*cy - c^2)^(1/2) - b^2*cx + a*b*cy)/(a^2 + b^2);
        // x1 = -(a*c - b*(- a^2*cx^2 + a^2*r^2 - 2*a*b*cx*cy - 2*a*c*cx - b^2*cy^2 + b^2*r^2 -
        // 2*b*c*cy
        // - c^2)^(1/2) - b^2*cx + a*b*cy)/(a^2 + b^2);
        // TODO: Check content of sqrt() to make sure it isn't negative
        const float x0 =
            -(a * c_ +
              b * std::sqrt(-a2 * cx2 + a2 * r2 - 2.0f * a * b * cx * cy - 2.0f * a * c_ * cx -
                            b2 * cy2 + b2 * r2 - 2.0f * b * c_ * cy - c2) -
              b2 * cx + a * b * cy) /
            a2b2;
        const float x1 =
            -(a * c_ -
              b * std::sqrt(-a2 * cx2 + a2 * r2 - 2.0f * a * b * cx * cy - 2.0f * a * c_ * cx -
                            b2 * cy2 + b2 * r2 - 2.0f * b * c_ * cy - c2) -
              b2 * cx + a * b * cy) /
            a2b2;
        return_vector[0] = Point2D<T>(x0, line.evalX(x0));
        return_vector[1] = Point2D<T>(x1, line.evalX(x1));
    }
    else
    {
        return_vector[0] = Point2D<T>(NAN, NAN);
        return_vector[1] = Point2D<T>(NAN, NAN);
    }

    return return_vector;
}

/* **************************************************************** */
/* ************************** Section 3D ************************** */
/* **************************************************************** */

template <typename T>
Circle3D<T>::Circle3D(const Vec3D<T> &v_, const Vec3D<T> &c_) : v(v_), c(c_)
{
    calculateOrthogonalVectors();
}

template <typename T>
Circle3D<T>::Circle3D() {}

template <typename T>
void Circle3D<T>::calculateOrthogonalVectors()
{
    assert(v.x != 0.0 || v.y != 0.0 || v.z != 0.0);

    if (v.x > v.y && v.x && v.z)
    {
        const double x = -(v.y + v.z) / v.x;
        a = Vec3D<T>(x, 1.0, 1.0).normalized();
    }
    else if (v.y > v.x && v.y > v.z)
    {
        const double y = -(v.x + v.z) / v.y;
        a = Vec3D<T>(1.0, y, 1.0).normalized();
    }
    else
    {
        const double z = -(v.x + v.y) / v.z;
        a = Vec3D<T>(1.0, 1.0, z).normalized();
    }
    b = a.crossProduct(v);
}

} // namespace arl

#endif
