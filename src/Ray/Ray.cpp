#include <cmath>
#include "Ray.h"
#include "Triangle.h"

double Ray::getT(const Triangle* triangle) const
{
	const auto norm = triangle->getNorm();
	return (triangle->getD() - norm * pos) / (norm * dir);
}

void Ray::intersect(const Triangle* triangle)
{
	double t = getT(triangle);
	if (std::isnan(t) || t <= 1 || t >= closestT)
		return;

	auto p = pos + t * dir;
	const double d = Vec3::det(triangle->P1(), triangle->P2(), triangle->P3());
	if (d>0)
	{
		if (Vec3::det(p, triangle->P2(), triangle->P3()) < 0)
			return;
		if (Vec3::det(triangle->P1(), p, triangle->P3()) < 0)
			return;
		if (Vec3::det(triangle->P1(), triangle->P2(), p) < 0)
			return;
	}
	else
	{
		if (Vec3::det(p, triangle->P2(), triangle->P3()) > 0)
			return;
		if (Vec3::det(triangle->P1(), p, triangle->P3()) > 0)
			return;
		if (Vec3::det(triangle->P1(), triangle->P2(), p) > 0)
			return;
	}


	closestT = t;
	closestTriangle = triangle;
	interPoint = &p;

}
