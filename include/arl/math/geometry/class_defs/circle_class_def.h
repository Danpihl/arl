#ifndef CIRCLE_CLASS_H_
#define CIRCLE_CLASS_H_

namespace arl
{
template <typename T> struct Circle2D
{
    T r;           // Radius
    Point2D<T> c;  // Center point

    Circle2D(const T r_, const T cx_, const T cy_);
    Circle2D(const T r_, const Vec2D<T>& c_);
    Circle2D();

    HomogeneousLine2D<T> tangentLine(const T angle) const;
    bool doesLineIntersect(const HomogeneousLine2D<T>& line) const;
    Point2D<T> closestPointOnPerimeterFromPoint(const Point2D<T>& p) const;
    std::vector<Point2D<T>> lineIntersectionPoints(const HomogeneousLine2D<T>& line) const;
};

template <typename T> class Circle3D
{
private:
    Vec3D<T> v;
    Vec3D<T> a;
    Vec3D<T> b;
    Point3D<T> c;
    void calculateOrthogonalVectors();

public:
    Circle3D(const Vec3D<T>& v_, const Vec3D<T>& c_);
    Circle3D();
};

}  // namespace arl

#endif
