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

	if (triangle->determinant > 0)
	{
		if (Vec3::det(p, triangle->P2(), triangle->P3()) < 0)
			return false;
		if (Vec3::det(triangle->P1(), p, triangle->P3()) < 0)
			return false;
		if (Vec3::det(triangle->P1(), triangle->P2(), p) < 0)
			return false;
	}
	else
	{
		if (Vec3::det(p, triangle->P2(), triangle->P3()) > 0)
			return false;
		if (Vec3::det(triangle->P1(), p, triangle->P3()) > 0)
			return false;
		if (Vec3::det(triangle->P1(), triangle->P2(), p) > 0)
			return false;
	}


	closestT = t;
	closestTriangle = triangle;
	interPoint = &p;
	return true;
}
