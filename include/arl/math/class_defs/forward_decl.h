#ifndef FORWARD_DECL_H_
#define FORWARD_DECL_H_

namespace arl
{
template <typename T> struct Vec2D;
template <typename T> struct Vec3D;
template <typename T> struct Vec4D;
template <typename T> class Vector;
template <typename T> struct Complex;
template <typename T> struct PolarVec;
template <typename T> struct CylindricalVec;
template <typename T> struct SphericalVec;
template <typename T> struct RollPitchYaw;
template <typename T> struct AxisAngle;
template <typename T> class Matrix;
template <typename T> class Vector;
template <typename T> class Circle3D;
template <typename T> struct Circle2D;
template <typename T> struct Line3D;
template <typename T> struct Plane;
template <typename T> struct Sphere;

template <typename T> struct PolarVec;
template <typename T> struct SphericalVec;
template <typename T> struct CylindricalVec;
template <typename T> struct Complex;

template <typename T> struct Quaternion;
template <typename T> struct RollPitchYaw;
template <typename T> struct AxisAngle;

template <typename T> struct Rect2D;
template <typename T> class PoseSE3;

template <typename T> class PolygonNVertices2D;
template <typename T> class PolygonNVertices3D;

template <typename T> class OrderedSet3D;
template <typename T> class OrderedSet2D;

template <typename T> struct Triangle2D;
template <typename T> struct Triangle3D;

template <typename T> class PinholeCamera;

template <typename T> struct Interval1D;
template <typename T> struct ParametricLine2D;
template <typename T> struct HomogeneousLine2D;
struct IndexSpan;
struct EndIndex;
typedef EndIndex End;

template <typename T> using Point2D = Vec2D<T>;
template <typename T> using Point3D = Vec3D<T>;
template <typename T> using Point4D = Vec4D<T>;
template <typename T> using Point = Vector<T>;

}  // namespace arl

#endif
