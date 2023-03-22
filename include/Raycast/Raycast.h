#pragma once

#include "Triangle.h"
#include "Vec3.h"

using Vector::Vec3;

class Triangle;
class Ray;

class Raycast
{
public:
	bool hit;
	Triangle* triangle;
	Vec3 hitPos;

	explicit Raycast(const bool hit, Triangle* triangle = nullptr, const Vec3& pos = Vec3())
		: hit(hit), triangle(triangle), hitPos(pos) {}

	static Raycast castRay(Ray ray);
};

inline std::ostream& operator<<(std::ostream& os, const Raycast& r)
{
	os << "Raycast(hitPos: " << r.hitPos << ")";
	return os;
}
