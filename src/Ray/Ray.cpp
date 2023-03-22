#include "Ray.h"
#include "Triangle.h"

using namespace Vector;

float Ray::getT(const Triangle& triangle) const
{
	const auto norm = triangle.getPlaneEq().norm;
	const auto d = triangle.getPlaneEq().d;
	return (d - norm * pos) / (norm * dir);
}

bool Ray::intersects(const Triangle& triangle, Vec3& interPoint) const
{
	const float t = getT(triangle);
	if (t <= 0)
		return false;

	const auto p = pos + t * dir;
	const float d = Vec3::det(triangle.P1(), triangle.P2(), triangle.P3());

	if (Vec3::det(p, triangle.P2(), triangle.P3()) / d < 0)
		return false;
	if (Vec3::det(triangle.P1(), p, triangle.P3()) / d < 0)
		return false;
	if (Vec3::det(triangle.P1(), triangle.P2(), p) / d < 0)
		return false;

	interPoint = p;
	return true;
}
