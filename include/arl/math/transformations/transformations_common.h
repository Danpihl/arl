#ifndef TRANSFORMATIONS_COMMON_H_
#define TRANSFORMATIONS_COMMON_H_

#include "arl/math/lin_alg/matrix_dynamic/matrix_dynamic.h"
#include "arl/math/lin_alg/vector_low_dim/vec3d.h"
#include "arl/math/transformations/class_defs/axis_angle_class_def.h"
#include "arl/math/transformations/class_defs/pose_class_def.h"
#include "arl/math/transformations/class_defs/quaternion_class_def.h"
#include "arl/math/transformations/class_defs/roll_pitch_yaw_class_def.h"
#include "arl/utilities/logging.h"

namespace arl
{
template <typename T> Quaternion<T> AxisAngle<T>::toQuaternion() const
{
    Vec3D<T> v = Vec3D<T>(x, y, z).normalized();
    Quaternion<T> q;
    q.x = v.x * std::sin(phi / 2.0);
    q.y = v.y * std::sin(phi / 2.0);
    q.z = v.z * std::sin(phi / 2.0);
    q.w = std::cos(phi / 2.0);
    return q;
}

template <typename T> RollPitchYaw<T> AxisAngle<T>::toRollPitchYaw() const
{
    const Quaternion<T> q = toQuaternion();
    return q.toRollPitchYaw();
}

template <typename T> Quaternion<T> RollPitchYaw<T>::toQuaternion() const
{
    T cy = std::cos(yaw * 0.5);
    T sy = std::sin(yaw * 0.5);
    T cp = std::cos(pitch * 0.5);
    T sp = std::sin(pitch * 0.5);
    T cr = std::cos(roll * 0.5);
    T sr = std::sin(roll * 0.5);

    Quaternion<T> q;

    q.w = cy * cp * cr + sy * sp * sr;
    q.x = cy * cp * sr - sy * sp * cr;
    q.y = sy * cp * sr + cy * sp * cr;
    q.z = sy * cp * cr - cy * sp * sr;

    return q;
}

template <typename T> AxisAngle<T> RollPitchYaw<T>::toAxisAngle() const
{
    Quaternion<T> q = toQuaternion();
    return q.toAxisAngle();
}

template <typename T> RollPitchYaw<T> Quaternion<T>::toRollPitchYaw() const
{
    RollPitchYaw<T> rpy;
    // Roll (x-axis rotation)
    T sinr_cosp = 2.0 * (w * x + y * z);
    T cosr_cosp = 1.0 - 2.0 * (x * x + y * y);
    rpy.roll = std::atan2(sinr_cosp, cosr_cosp);

    // Pitch (y-axis rotation)
    T sinp = 2.0 * (w * y - z * x);
    if (std::fabs(sinp) >= 1)
    {
        rpy.pitch = std::copysign(M_PI / 2.0, sinp);  // Use 90 degrees if out of range
    }
    else
    {
        rpy.pitch = std::asin(sinp);
    }

    // Yaw (z-axis rotation)
    T siny_cosp = 2.0 * (w * z + x * y);
    T cosy_cosp = 1.0 - 2.0 * (y * y + z * z);
    rpy.yaw = std::atan2(siny_cosp, cosy_cosp);
    return rpy;
}

template <typename T> AxisAngle<T> Quaternion<T>::toAxisAngle() const
{
    AxisAngle<T> axis_angle;
    axis_angle.phi = 2.0 * std::acos(w);
    axis_angle.x = x / std::sqrt(1 - w * w);
    axis_angle.y = y / std::sqrt(1 - w * w);
    axis_angle.z = z / std::sqrt(1 - w * w);

    return axis_angle;
}

}  // namespace arl

#endif
