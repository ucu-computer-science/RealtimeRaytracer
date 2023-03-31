#pragma once

#include <ostream>
#include "Ray.h"

class Triangle;
class Ray;

class Raycast
{
public:
	Ray& ray;

	explicit Raycast(Ray& ray) : ray(ray) { }
	~Raycast() = default;
	static Raycast castRay(Ray ray);
};

inline std::ostream& operator<<(std::ostream& os, const Raycast& r)
{
	if (r.ray.hit())
		os << "Raycast(hitPos: " << to_string(r.ray.interPoint) << ")";
	else
		os << "Raycast(hitPos: NOHIT)";
	return os;
}
