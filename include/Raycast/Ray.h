#pragma once

#include "Vec3.h"

class Triangle;

class Ray
{
public:
	Vec3 pos, dir;
	double closestT;
	const Triangle* closestTriangle;
	Vec3* interPoint;

	Ray(Vec3 pos, Vec3 dir) : pos{ pos }, dir{ dir }, closestT(__DBL_MAX__), closestTriangle(nullptr), interPoint{ nullptr } {}

	double getT(const Triangle& triangle) const;
	bool intersect(const Triangle& triangle);

	bool hit() const
	{
		return closestTriangle != nullptr;
	}
};

inline std::ostream& operator<<(std::ostream& os, const Ray& r)
{
	os << "Ray(pos: " << r.pos << ", dir: " << r.dir << ")";
	return os;
}
