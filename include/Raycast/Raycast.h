#pragma once

#include "Ray.h"
#include "Vec3.h"

class Triangle;
class Ray;

class Raycast
{
public:
	Ray& ray;

	explicit Raycast(Ray& ray) : ray(ray) { }

	static Raycast castRay(Ray& ray);
};

inline std::ostream& operator<<(std::ostream& os, const Raycast& r)
{
	if (r.ray.hit())
		os << "Raycast(hitPos: " << *r.ray.interPoint << ")";
	else
		os << "Raycast(hitPos: NOHIT)";
	return os;
}
