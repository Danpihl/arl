#ifndef LINE_3D_CLASS_
#define LINE_3D_CLASS_

#include "arl/math/misc/forward_decl.h"

namespace arl
{
template <typename T> struct Line3D
{
    // Point on line
    Point3D<T> p;
    // Vector in line direction
    Vec3D<T> v;

    Line3D(const Point3D<T>& p_, const Vec3D<T>& v_);
    Line3D();

    Vec3D<T> vectorNormalToLine() const;
    Point3D<T> eval(const T t) const;
    Point3D<T> closestPointOnLineFromPoint(const Point3D<T>& q) const;
    Vec3D<T> vectorBetweenClosestPointOnLineAndPoint(const Point3D<T>& q) const;
    Line3D<T> translatedLine(const Vec3D<T>& v) const;
    std::vector<Point3D<T>> closestPointsBetweenLines(const Line3D<T>& line) const;
    std::pair<Point3D<T>, Vec3D<T>> projectPointAndVectorOntoLine(const Point3D<T>& q,
                                                                  const Vec3D<T>& v) const;
    Point3D<T> rotatePointAroundLine(const Point3D<T>& q, const T angle) const;
    Line3D<T> negatedLine() const;
    T pointDistanceFromLine(const Point3D<T>& q) const;
    T angleBetweenLines(const Line3D<T>& line) const;
    Line3D<T> rotateLineAroundLine(const Line3D<T>& line_to_be_rotated, const T angle) const;
};
}  // namespace arl

#endif
