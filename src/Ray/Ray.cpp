#include "Ray.h"

#include <cmath>

#include "Triangle.h"

using namespace Vector;

double Ray::getT(const Triangle& triangle) const
{
	const auto norm = triangle.getPlaneEq().norm;
	const auto d = triangle.getPlaneEq().d;
	return (d - norm * pos) / (norm * dir);
}

bool Ray::intersects(const Triangle& triangle)
{
	double t = getT(triangle);
	if (std::isnan(t) || t <= 1 || t >= closestT)
		return false;

	auto p = pos + t * dir;
	double d = Vec3::det(triangle.P1(), triangle.P2(), triangle.P3());

	if (Vec3::det(p, triangle.P2(), triangle.P3()) / d < 0)
		return false;
	if (Vec3::det(triangle.P1(), p, triangle.P3()) / d < 0)
		return false;
	if (Vec3::det(triangle.P1(), triangle.P2(), p) / d < 0)
		return false;

	closestT = t;
	closestTriangle = &triangle;
	interPoint = &p;
	return true;
}
