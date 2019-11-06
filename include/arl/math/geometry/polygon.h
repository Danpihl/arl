
#ifndef POLYGON_H_
#define POLYGON_H_

#include <cmath>
#include <vector>

#include "arl/math/lin_alg.h"
#include "arl/math/math_core.h"
#include "arl/utilities/logging.h"

namespace arl
{
template <typename T> PolygonNVertices2D<T>::PolygonNVertices2D()
{
    is_allocated_ = false;
}

template <typename T> PolygonNVertices2D<T>::PolygonNVertices2D(const size_t n_vertices)
{
    n_vertices_ = n_vertices;
    vertices_ = new Point2D<T>[n_vertices];
    is_allocated_ = true;
}

template <typename T> PolygonNVertices2D<T>::~PolygonNVertices2D()
{
    delete[] vertices_;
}

template <typename T> PolygonNVertices3D<T>::PolygonNVertices3D()
{
    is_allocated_ = false;
}

template <typename T> PolygonNVertices3D<T>::PolygonNVertices3D(const size_t n_vertices)
{
    n_vertices_ = n_vertices;
    vertices_ = new Point3D<T>[n_vertices];
    is_allocated_ = true;
}

template <typename T> PolygonNVertices3D<T>::~PolygonNVertices3D()
{
    delete[] vertices_;
}

}  // namespace arl

#endif
