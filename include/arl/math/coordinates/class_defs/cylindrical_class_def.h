#ifndef CYLINDRICAL_CLASS_H_
#define CYLINDRICAL_CLASS_H_

namespace arl
{
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

template <typename T> using CylindricalPoint = CylindricalVec<T>;
}  // namespace arl

#endif
