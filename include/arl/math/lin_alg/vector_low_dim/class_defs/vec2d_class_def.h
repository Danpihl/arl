#ifndef VEC2D_CLASS_H_
#define VEC2D_CLASS_H_

namespace arl
{
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
}  // namespace arl

#endif
