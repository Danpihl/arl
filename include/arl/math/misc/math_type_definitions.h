#ifndef MATH_TYPE_DEFINITIONS_H_
#define MATH_TYPE_DEFINITIONS_H_

#include "arl/math/misc/forward_decl.h"

namespace arl
{
typedef PoseSE3<double> PoseSE3d;
typedef AxisAngle<double> AxisAngled;
typedef Circle2D<double> Circle2Dd;
typedef Circle3D<double> Circle3Dd;
typedef Complex<double> Complexd;
typedef HomogeneousLine2D<double> HomogeneousLine2Dd;
typedef ParametricLine2D<double> ParametricLine2Dd;
typedef Line3D<double> Line3Dd;
typedef OrderedSet2D<double> OrderedSet2Dd;
typedef Plane<double> Planed;
typedef PolarVec<double> PolarVecd;
typedef SphericalVec<double> SphericalVecd;
typedef CylindricalVec<double> CylindricalVecd;
typedef Quaternion<double> Quaterniond;
typedef Rect2D<double> Rect2Dd;
typedef RollPitchYaw<double> RollPitchYawd;
typedef Sphere<double> Sphered;
typedef Triangle2D<double> Triangle2Dd;
typedef Triangle3D<double> Triangle3Dd;
typedef Matrix<double> Matrixd;
typedef Vector<double> Vectord;
typedef Point<double> Pointd;
typedef Vec2D<double> Vec2Dd;
typedef Vec3D<double> Vec3Dd;
typedef Vec4D<double> Vec4Dd;
typedef Point2D<double> Point2Dd;
typedef Point3D<double> Point3Dd;
typedef Point4D<double> Point4Dd;

typedef PoseSE3<float> PoseSE3f;
typedef AxisAngle<float> AxisAnglef;
typedef Circle2D<float> Circle2Df;
typedef Circle3D<float> Circle3Df;
typedef Complex<float> Complexf;
typedef HomogeneousLine2D<float> HomogeneousLine2Df;
typedef ParametricLine2D<float> ParametricLine2Df;
typedef Line3D<float> Line3Df;
typedef OrderedSet2D<float> OrderedSet2Df;
typedef Plane<float> Planef;
typedef PolarVec<float> PolarVecf;
typedef SphericalVec<float> SphericalVecf;
typedef CylindricalVec<float> CylindricalVecf;
typedef Quaternion<float> Quaternionf;
typedef Rect2D<float> Rect2Df;
typedef RollPitchYaw<float> RollPitchYawf;
typedef Sphere<float> Spheref;
typedef Triangle2D<float> Triangle2Df;
typedef Triangle3D<float> Triangle3Df;
typedef Matrix<float> Matrixf;
typedef Vector<float> Vectorf;
typedef Point<float> Pointf;
typedef Vec2D<float> Vec2Df;
typedef Vec3D<float> Vec3Df;
typedef Vec4D<float> Vec4Df;
typedef Point2D<float> Point2Df;
typedef Point3D<float> Point3Df;
typedef Point4D<float> Point4Df;

typedef Vec2D<int> Vec2Di;

}  // namespace arl

#endif
