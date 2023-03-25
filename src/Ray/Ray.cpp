#include <cmath>
#include "Ray.h"
#include "Triangle.h"

double Ray::getT(const Triangle* triangle) const
{
	const auto norm = triangle->getNorm();
	return (triangle->getD() - norm * pos) / (norm * dir);
}

bool Ray::intersect(const Triangle* triangle)
{
	double t = getT(triangle);
	if (std::isnan(t) || t <= 0 || t >= closestT)
		return false;

	auto p = pos + t * dir;
	double d = Vec3::det(triangle->P1(), triangle->P2(), triangle->P3());

	if (Vec3::det(p, triangle->P2(), triangle->P3()) / d < 0)
		return false;
	if (Vec3::det(triangle->P1(), p, triangle->P3()) / d < 0)
		return false;
	if (Vec3::det(triangle->P1(), triangle->P2(), p) / d < 0)
		return false;

	closestT = t;
	closestTriangle = triangle;
	interPoint = &p;
	return true;
}
