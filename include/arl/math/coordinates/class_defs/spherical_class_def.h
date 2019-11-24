#ifndef SPHERICAL_CLASS_H_
#define SPHERICAL_CLASS_H_

namespace arl
{
template <typename T> struct SphericalVec
{
    // phi for azimut, theta for inclination
    T r;
    T phi;
    T theta;

    SphericalVec(const T r_, const T phi_, const T theta_);
    SphericalVec();

    CylindricalVec<T> toCylindricalVec() const;
    Vec3D<T> toVec3D() const;
};

template <typename T> using SphericalPoint = SphericalVec<T>;
}  // namespace arl

#endif
