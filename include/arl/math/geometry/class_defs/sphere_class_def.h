#ifndef SPHERE_CLASS_H_
#define SPHERE_CLASS_H_

namespace arl
{
template <typename T> struct Sphere
{
    T r;
    Point3D<T> c;

    Sphere(const T r_, const Point3D<T>& c_);
    Sphere();

    bool doesLineIntersect(const Line3D<T>& line) const;
    std::vector<Point3D<T>> lineIntersectionPoint(const Line3D<T>& line) const;
};
}  // namespace arl

#endif
