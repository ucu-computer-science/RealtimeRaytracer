#include <cmath>
#include "Ray.h"
#include "Triangle.h"
#include "glmExtension.h"

float Ray::getT(const Triangle* triangle) const
{
	const auto norm = triangle->getNorm();
	return (triangle->getD() - norm * pos) / (norm * dir);
}

bool Ray::intersect(const Triangle* triangle)
{
	float t = getT(triangle);
	if (std::isnan(t) || t <= 0 || t >= closestT)
		return false;

	auto p = pos + t * dir;

	if (triangle->detPositive)
	{
		if (triangle.optimizedDet(p, 1) < 0)
			return false;
		if (triangle.optimizedDet(p, 2) < 0)
			return false;
		if (triangle.optimizedDet(p, 3) < 0)
			return false;
	}
	else
	{
		if (triangle.optimizedDet(p, 1) > 0)
			return false;
		if (triangle.optimizedDet(p, 2) > 0)
			return false;
		if (triangle.optimizedDet(p, 3) > 0)
			return false;
	}

	closestT = t;
	closestTriangle = triangle;
	interPoint = &p;
	return true;
}
