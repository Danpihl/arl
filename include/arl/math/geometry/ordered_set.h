// Copyright 2019 Arrowtwig
#ifndef ORDERED_SET_H_
#define ORDERED_SET_H_

#include "arl/math/math_core.h"

#include "arl/math/lin_alg.h"
#include "arl/utilities/logging.h"

#include <cmath>
#include <vector>

namespace arl
{
template <typename T> OrderedSet3D<T>::OrderedSet3D()
{
    is_allocated_ = false;
}

template <typename T> OrderedSet3D<T>::OrderedSet3D(const size_t n_points)
{
    n_points_ = n_points;
    points_ = new T[3 * n_points];
    is_allocated_ = true;
}

template <typename T> OrderedSet3D<T>::~OrderedSet3D()
{
    delete[] points_;
}

/*template <typename T> Point3D<T> OrderedSet3D<T>::operator[](const size_t idx) const
{
    assert(idx < n_points_ && "Index out of bounds!");
    return Point3D<T>(points_[idx], points_[n_points_ + idx], points_[2 * n_points_ + idx]);
}*/

// TODO: Test operator[] functions below, not sure if this works with object going out of reference
template <typename T> Point3D<T>& OrderedSet3D<T>::operator[](const size_t idx)
{
    assert(idx < n_points_ && "Index out of bounds!");
    Point3D<T> p;
    p.x = &points_[idx];
    p.y = &points_[n_points_ + idx];
    p.z = &points_[2 * n_points_ + idx];

    return p;
}

template <typename T> const Point3D<T>& OrderedSet3D<T>::operator[](const size_t idx) const
{
    assert(idx < n_points_ && "Index out of bounds!");
    Point3D<T> p;
    p.x = &points_[idx];
    p.y = &points_[n_points_ + idx];
    p.z = &points_[2 * n_points_ + idx];

    return p;
}

template <typename T> void OrderedSet3D<T>::setPointAt(const Point3D<T>& p, const size_t idx)
{
    assert(idx < n_points_ && "Index out of bounds!");
    points_[idx] = p.x;
    points_[n_points_ + idx] = p.y;
    points_[2 * n_points_ + idx] = p.z;
}

template <typename T> T& OrderedSet3D<T>::xAt(const size_t idx)
{
    assert(idx < n_points_ && "Index out of bounds!");
    return points_[idx];
}

template <typename T> const T& OrderedSet3D<T>::xAt(const size_t idx) const
{
    assert(idx < n_points_ && "Index out of bounds!");
    return points_[idx];
}

template <typename T> T& OrderedSet3D<T>::yAt(const size_t idx)
{
    assert(idx < n_points_ && "Index out of bounds!");
    return points_[n_points_ + idx];
}

template <typename T> const T& OrderedSet3D<T>::yAt(const size_t idx) const
{
    assert(idx < n_points_ && "Index out of bounds!");
    return points_[n_points_ + idx];
}

template <typename T> T& OrderedSet3D<T>::zAt(const size_t idx)
{
    assert(idx < n_points_ && "Index out of bounds!");
    return points_[2 * n_points_ + idx];
}

template <typename T> const T& OrderedSet3D<T>::zAt(const size_t idx) const
{
    assert(idx < n_points_ && "Index out of bounds!");
    return points_[2 * n_points_ + idx];
}

// OrderedSet2D

template <typename T> OrderedSet2D<T>::OrderedSet2D()
{
    is_allocated_ = false;
}

template <typename T> OrderedSet2D<T>::OrderedSet2D(const size_t n_points)
{
    n_points_ = n_points;
    points_ = new T[3 * n_points];
    is_allocated_ = false;
}

template <typename T> OrderedSet2D<T>::~OrderedSet2D()
{
    delete[] points_;
}

}  // namespace arl

#endif
