#ifndef ROLL_PITCH_YAW_H_
#define ROLL_PITCH_YAW_H_

#include <cmath>

#include "arl/math/lin_alg/matrix_dynamic/matrix_dynamic.h"
#include "arl/math/lin_alg/vector_low_dim/vec3d.h"
#include "arl/math/transformations/class_defs/roll_pitch_yaw_class_def.h"
#include "arl/utilities/logging.h"

namespace arl
{
template <typename T> RollPitchYaw<T>::RollPitchYaw(const T roll_, const T pitch_, const T yaw_)
{
    roll = roll_;
    pitch = pitch_;
    yaw = yaw_;
}

template <typename T> RollPitchYaw<T>::RollPitchYaw() {}

template <typename T> Matrix<T> rotationMatrixFromYaw(const T yaw)
{
    Matrix<T> m(3, 3);
    const T ca = std::cos(yaw);
    const T sa = std::sin(yaw);

    m(0, 0) = ca;
    m(0, 1) = -sa;
    m(0, 2) = 0.0;

    m(1, 0) = sa;
    m(1, 1) = ca;
    m(1, 2) = 0.0;

    m(2, 0) = 0.0;
    m(2, 1) = 0.0;
    m(2, 2) = 1.0;

    return m;
}

template <typename T> Matrix<T> rotationMatrixFromRoll(const T roll)
{
    Matrix<T> m(3, 3);
    const T ca = std::cos(roll);
    const T sa = std::sin(roll);

    m(0, 0) = 1.0;
    m(0, 1) = 0.0;
    m(0, 2) = 0.0;

    m(1, 0) = 0.0;
    m(1, 1) = ca;
    m(1, 2) = -sa;

    m(2, 0) = 0.0;
    m(2, 1) = sa;
    m(2, 2) = ca;

    return m;
}

template <typename T> Matrix<T> rotationMatrixFromPitch(const T pitch)
{
    Matrix<T> m(3, 3);
    const T ca = std::cos(pitch);
    const T sa = std::sin(pitch);

    m(0, 0) = ca;
    m(0, 1) = 0.0;
    m(0, 2) = sa;

    m(1, 0) = 0.0;
    m(1, 1) = 1.0;
    m(1, 2) = 0.0;

    m(2, 0) = -sa;
    m(2, 1) = 0.0;
    m(2, 2) = ca;

    return m;
}

template <typename T> Matrix<T> RollPitchYaw<T>::toRotationMatrix() const
{
    return rotationMatrixFromYaw(yaw) * rotationMatrixFromPitch(pitch) *
           rotationMatrixFromRoll(roll);
}

template <typename T> RollPitchYaw<T> rotationMatrixToRollPitchYaw(const Matrix<T>& m)
{
    return RollPitchYaw<T>(
        std::atan2(m(2, 1), m(2, 2)), std::asin(-m(2, 0)), std::atan2(m(1, 0), m(0, 0)));
}

}  // namespace arl

#endif
