#ifndef POLYGON_CLASS_H_
#define POLYGON_CLASS_H_

namespace arl
{
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

}  // namespace arl

#endif
