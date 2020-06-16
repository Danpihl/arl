#ifndef ORDERED_SET_CLASS_H_
#define ORDERED_SET_CLASS_H_

#include "arl/math/misc/forward_decl.h"

namespace arl
{
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
}  // namespace arl

#endif
