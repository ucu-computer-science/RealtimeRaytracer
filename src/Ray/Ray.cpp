#include <cmath>
#include "Ray.h"
#include "Triangle.h"
#include "glmExtension.h"
#include "iostream"

float Ray::getT(const Triangle* triangle) const
{
	return (triangle->getD() - dot(triangle->getNorm(), pos)) / dot(triangle->getNorm(), dir);
}

bool Ray::intersect(const Triangle* triangle)
{
	float t = getT(triangle);

	if (std::isnan(t) || t <= 0 || t >= closestT)
		return false;

	auto p = pos + t * dir;

	if (triangle->detSign > 0)
	{
		if (triangle->optimizedDet(p, 1) < 0)
			return false;
		if (triangle->optimizedDet(p, 2) < 0)
			return false;
		if (triangle->optimizedDet(p, 3) < 0)
			return false;
	}
	else if (triangle->detSign < 0)
	{
		if (triangle->optimizedDet(p, 1) > 0)
			return false;
		if (triangle->optimizedDet(p, 2) > 0)
			return false;
		if (triangle->optimizedDet(p, 3) > 0)
			return false;
	}
	else
	{
		return false;
	}

	closestT = t;
	closestTriangle = triangle;
	interPoint = &p;
	return true;
}
