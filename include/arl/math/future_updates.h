
template <typename T> class ThirdOrderBezierCurve3D
{
private:
public:
};

template <typename T> class RingBuffer
{
private:
public:
};

template <typename T> class FIRFilter
{
private:
public:
};

template <typename T> class IIRFilter
{
private:
public:
};

template <typename T> class PinholeCamera
{
private:
    Vector<T> distortion_coefficients_;
    // Camera pose is defined as taking points in the local camera coordinate system
    // to the global coordinate system, where the pose is defined
    // P_global = R_camera_pose * P_camera + t_camera_pose
    PoseSE3<T> pose_;
    T focal_length_x_;
    T focal_length_y_;
    T center_x_;
    T center_y_;

public:
    OrderedSet2D<T> project3DPointsToCamera(OrderedSet3D<T> points);
    PoseSE3<T> getPose();
};