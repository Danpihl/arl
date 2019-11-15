// Copyright 2019 Arrowtwig
#ifndef MATH_CORE_H_
#define MATH_CORE_H_

#include <assert.h>

#include <cmath>
#include <initializer_list>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

// #include "Eigen/Core"
// #include "Eigen/Eigen"
// #include "Eigen/SVD"

#include "arl/math/misc/math_macros.h"
#include "arl/utilities/logging.h"

namespace arl
{
/* ********************** Data structures declarations ********************** */

// Forward declarations
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
template <typename T> class Circle3D;
template <typename T> struct Sphere;
template <typename T> struct Interval1D;
struct IndexSpan;
struct EndIndex;
typedef EndIndex End;

template <typename T> using Point2D = Vec2D<T>;
template <typename T> using Point3D = Vec3D<T>;
template <typename T> using Point4D = Vec4D<T>;
template <typename T> using Point = Vector<T>;

template <typename T> struct QRMatrixPair
{
    Matrix<T> q;
    Matrix<T> r;

    QRMatrixPair(const size_t num_rows, const size_t num_cols);
};

template <typename T> struct LUMatrixPair
{
    Matrix<T> l;
    Matrix<T> u;

    LUMatrixPair(const size_t num_rows, const size_t num_cols);
};

template <typename T> struct SVDMatrixTriplet
{
    Matrix<T> u;
    Matrix<T> s;
    Matrix<T> v;

    SVDMatrixTriplet(const size_t num_rows, const size_t num_cols);
};

template <typename T> class Vector
{
protected:
    T* data_;
    size_t vector_length_;
    bool is_allocated_;

public:
    Vector();
    Vector(const size_t vector_length);
    Vector(const Vector<T>& v);

    Vec2D<T> toVec2D() const;
    Vec3D<T> toVec3D() const;
    Vec4D<T> toVec4D() const;

    Vector(const std::initializer_list<T>& il);
    Vector(const std::vector<T>& v);

    ~Vector();

    Vector<T>& operator=(const Vector<T>& v);
    T& operator()(const size_t idx);
    const T& operator()(const size_t idx) const;
    T& operator()(const EndIndex& end_idx);
    const T& operator()(const EndIndex& end_idx) const;

    template <typename Y> Vector<T> operator()(const Vector<Y>& idx_vector) const;
    Vector<T> operator()(const IndexSpan& idx_span) const;

    void removeElementAtIndex(const size_t idx);
    void removeElementsAtIndices(const IndexSpan& idx_span);
    size_t size() const;
    size_t numElements() const;
    bool isAllocated() const;
    void fill(T val);
    void resize(const size_t vector_length);
    size_t endIndex() const;
    T* getDataPointer() const;

    Vector<T> normalized() const;
    Vector<T> vectorBetweenPoints(const Point<T>& end_point) const;
    Vector<T> normalizedVectorBetweenPoints(const Point<T>& end_point) const;
    T squaredNorm() const;
    T norm() const;
    Matrix<T> outerProduct(const Vector<T>& v) const;
    Point<T> mirrorPointInThis(const Point<T>& point_to_mirror) const;
    T angleBetweenVectors(const Vector<T>& v) const;
    Matrix<T> toColumnVectorMat() const;
    Matrix<T> toRowVectorMat() const;
    size_t countNumNonZeroElements() const;
};

template <typename T> class Matrix
{
protected:
    T* data_;
    size_t num_rows_;
    size_t num_cols_;
    bool is_allocated_;

public:
    Matrix();
    Matrix(const size_t num_rows, const size_t num_cols);
    Matrix(const Matrix<T>& m);
    Matrix(const std::vector<std::vector<T>>& vm);
    Matrix(const std::initializer_list<std::initializer_list<T>>& il);
    ~Matrix();
    T& operator()(const size_t r, const size_t c);
    const T& operator()(const size_t r, const size_t c) const;

    Matrix<T> operator()(const size_t row, const IndexSpan& col_idx_span) const;
    Matrix<T> operator()(const IndexSpan& row_idx_span, const size_t col) const;
    Matrix<T> operator()(const IndexSpan& row_idx_span, const IndexSpan& col_idx_span) const;

    T& operator()(const EndIndex& row_end_idx, const size_t c);
    const T& operator()(const EndIndex& row_end_idx, const size_t c) const;
    T& operator()(const size_t r, const EndIndex& col_end_idx);
    const T& operator()(const size_t r, const EndIndex& col_end_idx) const;
    Matrix<T>& operator=(const Matrix<T>& m);

    void removeRowAtIndex(const size_t row_idx);
    void removeRowsAtIndices(const IndexSpan& idx_span);
    void removeColAtIndex(const size_t col_idx);
    void removeColsAtIndices(const IndexSpan& idx_span);
    void resize(const size_t num_rows, const size_t num_cols);
    size_t rows() const;
    size_t cols() const;
    size_t size() const;
    size_t numElements() const;
    void hCat(const Vector<T>& v);
    void vCat(const Vector<T>& v);
    bool isAllocated() const;
    void fill(const T val);
    void switchRows(size_t r0, size_t r1);
    void switchColumns(size_t c0, size_t c1);
    T* getDataPointer() const;
    Matrix<T> transposed() const;

    void addVectorToMatrixCols(const Vector<T>& v);
    void addVectorToMatrixRows(const Vector<T>& v);

    Vector<T> getColumnAsVector(size_t column_idx) const;
    Vector<T> getRowAsVector(size_t row_idx) const;
    Matrix<T> getColumn(size_t column_idx) const;
    Matrix<T> getRow(size_t row_idx) const;
    size_t lastRowIdx() const;
    size_t lastColIdx() const;
    Matrix<T> inverse() const;
    void invert();
    Vector<T> solve(const Vector<T>& b) const;
    T det() const;
    T norm() const;
    LUMatrixPair<T> lu() const;
    QRMatrixPair<T> qr() const;
    SVDMatrixTriplet<T> svd() const;
};

template <typename T> struct Vec2D
{
    T x;
    T y;

    Vec2D(const T x_, const T y_);
    Vec2D();
    Vec2D(const T v_array[2]);
    Vector<T> toVector() const;

    Complex<T> toComplex() const;
    PolarVec<T> toPolar() const;

    Vec2D<T> normalized() const;
    Vec2D<T> vectorBetweenPoints(const Point2D<T>& end_point) const;
    Vec2D<T> normalizedVectorBetweenPoints(const Point2D<T>& end_point) const;
    T squaredNorm() const;
    T norm() const;
    Vec2D<T> elementWiseMultiply(const Vec2D<T>& factor_vector) const;
    Vec2D<T> elementWiseDivide(const Vec2D<T>& numerator_vector) const;
    Matrix<T> outerProduct(const Vec2D<T>& v) const;
    Point2D<T> rotatePointAroundThis(const Point2D<T>& point_to_rotate, const T angle) const;
    Point2D<T> mirrorPointInThis(const Point2D<T>& point_to_mirror) const;
    T angleBetweenVectors(const Vec2D<T>& v) const;
    T angle() const;
};

template <typename T> struct Vec3D
{
    T x;
    T y;
    T z;

    Vec3D(const T x_, const T y_, const T z_);
    Vec3D();
    Vec3D(const T v_array[3]);
    Vector<T> toVector() const;

    CylindricalVec<T> toCylindricalVec() const;
    SphericalVec<T> toSphericalVec() const;

    Vec3D<T> normalized() const;
    Vec3D<T> vectorBetweenPoints(const Point3D<T>& end_point) const;
    Vec3D<T> normalizedVectorBetweenPoints(const Point3D<T>& end_point) const;
    T squaredNorm() const;
    T norm() const;
    Vec3D<T> elementWiseMultiply(const Vec3D<T>& factor_vector) const;
    Vec3D<T> elementWiseDivide(const Vec3D<T>& numerator_vector) const;
    Vec3D<T> crossProduct(const Vec3D<T>& right_vector) const;
    Matrix<T> toCrossProductMatrix() const;
    Matrix<T> outerProduct(const Vec3D<T>& v) const;
    Point3D<T> mirrorPointInThis(const Point3D<T>& point_to_mirror) const;
    T angleBetweenVectors(const Vec3D<T>& v) const;
};

template <typename T> struct Vec4D
{
    T x;
    T y;
    T z;
    T w;

    Vec4D(const T x_, const T y_, const T z_, const T w_);
    Vec4D();
    Vec4D(const T v_array[4]);

    Vector<T> toVector() const;
    Vec4D<T> normalized() const;
    Vec4D<T> vectorBetweenPoints(const Point4D<T>& end_point) const;
    Vec4D<T> normalizedVectorBetweenPoints(const Point4D<T>& end_point) const;
    T squaredNorm() const;
    T norm() const;
    Vec4D<T> elementWiseMultiply(const Vec4D<T>& factor_vector) const;
    Vec4D<T> elementWiseDivide(const Vec4D<T>& numerator_vector) const;
    Matrix<T> outerProduct(const Vec4D<T>& v) const;
    Point4D<T> mirrorPointInThis(const Point4D<T>& point_to_mirror) const;
    T angleBetweenVectors(const Vec4D<T>& v) const;
};

// Forward declaration for constructor in HomogeneousLine2D
template <typename T> struct ParametricLine2D;

template <typename T> struct HomogeneousLine2D
{
    T a;
    T b;
    T c;

    HomogeneousLine2D(const T a_, const T b_, const T c_);
    HomogeneousLine2D(const ParametricLine2D<T>& pl);
    HomogeneousLine2D();

    T evalX(const T x) const;
    T evalY(const T y) const;
    T eval(const Point2D<T>& p) const;
    Vec2D<T> normal() const;
    Vec2D<T> normalizedNormal() const;
    Vec2D<T> vectorAlongLine() const;

    HomogeneousLine2D<T> normalized() const;
    HomogeneousLine2D<T> negated() const;
    T pointDistanceFromLine(const Point2D<T>& p) const;
    Point2D<T> closestPointOnLineFromPoint(const Point2D<T>& p) const;
    Point2D<T> pointReflection(const Point2D<T>& p) const;
    Point2D<T> lineIntersection(const HomogeneousLine2D<T>& line) const;
    Point2D<T> lineReflection(const HomogeneousLine2D<T>& line_for_reflection) const;
    bool isOnNormalVectorSide(const Point2D<T>& p) const;
    HomogeneousLine2D<T> calculateLineRotatedAroundPoint(const Point2D<T>& p, const T angle) const;
    HomogeneousLine2D<T> translatedLine(const Vec2D<T>& v) const;
    std::pair<Point2D<T>, Vec2D<T>> projectPointAndVectorOntoLine(const Point2D<T>& p,
                                                                  const Vec2D<T>& v) const;
    T angleBetweenLines(const HomogeneousLine2D<T>& line) const;
};

template <typename T> struct ParametricLine2D
{
    Point2D<T> p;
    Vec2D<T> v;

    ParametricLine2D(const T px_, const T py_, const T vx_, const T vy_);
    ParametricLine2D(const Point2D<T>& p_, const Vec2D<T>& v_);
    ParametricLine2D(const HomogeneousLine2D<T>& hl);
    ParametricLine2D();
    T tFromX(const T x) const;
    T tFromY(const T y) const;
    Vec2D<T> eval(const T t) const;
    ParametricLine2D<T> calculateLineRotatedAroundPoint(const Point2D<T>& q, const T angle) const;
};

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

template <typename T> struct Plane
{
    T a;
    T b;
    T c;
    T d;

    Plane(const T a_, const T b_, const T c_, const T d_);
    Plane(const Point3D<T>& point, const Vec3D<T>& normal_vector);
    Plane();

    Plane<T> normalized() const;
    Vec3D<T> normal() const;
    Vec3D<T> normalizedNormal() const;
    Point3D<T> lineIntersection(const Line3D<T>& line) const;
    Point3D<T> closestPointOnPlaneFromPoint(const Point3D<T>& p) const;
    T pointDistanceFromPlane(const Point3D<T>& p) const;
    T eval(const Point3D<T>& p);
    T evalXY(const T x, const T y);
    T evalXZ(const T x, const T z);
    T evalYZ(const T y, const T z);

    Plane<T> rotatePlaneAroundLine(const Line3D<T>& line) const;
    Point3D<T> mirroredPoint(const Point3D<T>& point) const;
    Line3D<T> mirroredLine(const Line3D<T>& line) const;
    Plane<T> mirroredPlane(const Plane<T>& plane) const;
    std::pair<Point3D<T>, Point3D<T>> circleIntersection(const Circle3D<T> circle) const;
    Circle3D<T> sphereIntersection(const Sphere<T>& sphere) const;
    std::pair<Point3D<T>, Vec3D<T>> projectPointAndVectorOntoPlane(const Point3D<T>& point,
                                                                   const Vec3D<T>& vec) const;
    Line3D<T> projectLineOntoPlane(const Line3D<T> line) const;
    Plane<T> planeIntersection(const Plane<T>& plane) const;
    Plane<T> translatePlane(const Vec3D<T>& vec) const;
};

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

template <typename T> struct Sphere
{
    T r;
    Point3D<T> c;

    Sphere(const T r_, const Point3D<T>& c_);
    Sphere();

    bool doesLineIntersect(const Line3D<T>& line) const;
    std::vector<Point3D<T>> lineIntersectionPoint(const Line3D<T>& line) const;
};

template <typename T> struct PolarVec
{
    T r;
    T phi;

    PolarVec(const T r_, const T phi_);
    PolarVec();

    Complex<T> toComplex() const;
    Vec2D<T> toVec2D() const;
};

template <typename T> struct SphericalVec
{
    // phi for azimuth, theta for inclination
    T r;
    T phi;
    T theta;

    SphericalVec(const T r_, const T phi_, const T theta_);
    SphericalVec();

    CylindricalVec<T> toCylindricalVec() const;
    Vec3D<T> toVec3D() const;
};

template <typename T> struct CylindricalVec
{
    T r;
    T z;
    T phi;

    CylindricalVec(const T r_, const T z_, const T phi_);
    CylindricalVec();

    SphericalVec<T> toSphericalVec() const;
    Vec3D<T> toVec3D() const;
};

template <typename T> using PolarPoint = PolarVec<T>;
template <typename T> using SphericalPoint = SphericalVec<T>;
template <typename T> using CylindricalPoint = CylindricalVec<T>;

template <typename T> struct Complex
{
    T real;
    T imag;

    Complex(const T real_, const T imag_);
    Complex();

    PolarVec<T> toPolar() const;
    Complex<T> conjugate() const;
    Complex<T> inv() const;
    Vec2D<T> toVec2D() const;
    T abs() const;
};

template <typename T> struct Quaternion
{
    // w is real component, (x, y, z) are imaginary components
    T w;
    T x;
    T y;
    T z;

    Quaternion(const T w_, const T x_, const T y_, const T z_);
    Quaternion();

    Matrix<T> toRotationMatrix() const;
    AxisAngle<T> toAxisAngle() const;
    RollPitchYaw<T> toRollPitchYaw() const;

    T norm() const;
    T squaredNorm() const;
    Quaternion<T> normalized() const;
};

template <typename T> struct RollPitchYaw
{
    // Angles in radians
    T roll;
    T pitch;
    T yaw;

    // Coordinate system:
    // x forward, roll around x, positive rotation clockwise
    // y left, pitch around y, positive rotation down
    // z up, yaw around z, positive rotation to the left

    RollPitchYaw(const T roll_, const T pitch_, const T yaw_);
    RollPitchYaw();

    Matrix<T> toRotationMatrix() const;
    Quaternion<T> toQuaternion() const;
    AxisAngle<T> toAxisAngle() const;
};

template <typename T> struct AxisAngle
{
    T phi;
    T x;
    T y;
    T z;

    AxisAngle(const T phi_, const T x_, const T y_, const T z_);
    AxisAngle(const T x_, const T y_, const T z_);
    AxisAngle(const Vec3D<T>& v);
    AxisAngle();

    AxisAngle<T> normalized() const;

    Matrix<T> toRotationMatrix() const;
    Quaternion<T> toQuaternion() const;
    RollPitchYaw<T> toRollPitchYaw() const;
};

template <typename T> struct Rect2D
{
    T x;
    T y;
    T w;
    T h;

    Rect2D(const T x_, const T y_, const T w_, const T h_);
    Rect2D();
};

template <typename T> class PoseSE3
{
private:
    Matrix<T> rotation_matrix;
    Vec3D<T> translation_vector;

public:
    Matrix<T> getRotationMatrix() const;
    Vec3D<T> getTranslationVector() const;
    Matrix<T> getPoseMatrix() const;
    Matrix<T> getInversePoseMatrix() const;
    void invert();

    PoseSE3(const Matrix<T>& rotation_matrix, const Vec3D<T>& translation_vector);
    PoseSE3(const Matrix<T>& pose_matrix);
    PoseSE3();
};

struct IndexSpan
{
    const size_t from;
    const size_t to;

    IndexSpan() = delete;
    IndexSpan(const size_t from_, const size_t to_) : from(from_), to(to_) {}
};

struct EndIndex
{
    const int offset;

    EndIndex() : offset(0) {}
    EndIndex(const int offset_) : offset(offset_)
    {
        assert(offset_ <= 0 && "Offset must be either 0 or negative!");
    }
};

template <typename T> struct Interval1D
{
    T from;
    T to;

    Interval1D() = default;
    Interval1D(const T from_, const T to_) : from(from_), to(to_) {}
};

template <typename T> class PolygonNVertices2D
{
private:
    Point2D<T>* vertices_;
    int n_vertices_;
    bool is_allocated_;

public:
    PolygonNVertices2D();
    PolygonNVertices2D(const size_t n_vertices);
    ~PolygonNVertices2D();
};

template <typename T> class PolygonNVertices3D
{
private:
    Point3D<T>* vertices_;
    int n_vertices_;
    bool is_allocated_;

public:
    PolygonNVertices3D();
    PolygonNVertices3D(const size_t n_vertices);
    ~PolygonNVertices3D();
};

template <typename T> class OrderedSet3D
{
private:
    T* points_;
    int n_points_;
    bool is_allocated_;

public:
    OrderedSet3D();
    OrderedSet3D(const size_t n_points);
    ~OrderedSet3D();

    // Point3D<T> operator[](const size_t idx) const;
    Point3D<T>& operator[](const size_t idx);
    const Point3D<T>& operator[](const size_t idx) const;

    void setPointAt(const Point3D<T>& p, const size_t idx);

    T& xAt(const size_t idx);
    const T& xAt(const size_t idx) const;
    T& yAt(const size_t idx);
    const T& yAt(const size_t idx) const;
    T& zAt(const size_t idx);
    const T& zAt(const size_t idx) const;

    // Point3D<T>& pointAt(const size_t idx);
    // const Point3D<T>& pointAt(const size_t idx) const;
};

template <typename T> class OrderedSet2D
{
private:
    T* points_;
    int n_points_;
    bool is_allocated_;

public:
    OrderedSet2D();
    OrderedSet2D(const size_t n_points);
    ~OrderedSet2D();
};

template <typename T> struct Triangle2D
{
    Point2D<T> p0;
    Point2D<T> p1;
    Point2D<T> p2;
    Triangle2D();
    Triangle2D(const Point2D<T>& p0_, const Point2D<T>& p1_, const Point2D<T>& p2_);
};

template <typename T> struct Triangle3D
{
    Point3D<T> p0;
    Point3D<T> p1;
    Point3D<T> p2;
    Triangle3D();
    Triangle3D(const Point3D<T>& p0_, const Point3D<T>& p1_, const Point3D<T>& p2_);
};

template <typename T> class PinholeCamera
{
private:
    Vector<T> distortion_coefficients;
    // Camera pose is defined as taking points in the local camera coordinate system
    // to the global coordinate system, where the pose is defined
    // P_global = R_camera_pose * P_camera + t_camera_pose
    PoseSE3<T> pose;

public:
    OrderedSet2D<T> project3DPointsToCamera(OrderedSet3D<T> points);
    PoseSE3<T> getPose();
};

template <typename T> Matrix<T> array2x2ToMatrix(const double a[2][2])
{
    Matrix<T> m(2, 2);
    for (size_t r = 0; r < 2; r++)
    {
        for (size_t c = 0; c < 2; c++)
        {
            m(r, c) = a[r][c];
        }
    }

    return m;
}

template <typename T> Matrix<T> array3x3ToMatrix(const double a[3][3])
{
    Matrix<T> m(3, 3);
    for (size_t r = 0; r < 3; r++)
    {
        for (size_t c = 0; c < 3; c++)
        {
            m(r, c) = a[r][c];
        }
    }

    return m;
}

template <typename T> Matrix<T> array4x4ToMatrix(const double a[4][4])
{
    Matrix<T> m(4, 4);
    for (size_t r = 0; r < 4; r++)
    {
        for (size_t c = 0; c < 4; c++)
        {
            m(r, c) = a[r][c];
        }
    }

    return m;
}

}  // namespace arl

#endif
