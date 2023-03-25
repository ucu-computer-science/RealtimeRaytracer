#pragma once

#include "Vec3.h"
#include "cmath"
#include <cfloat>
class Triangle;

class Ray
{
public:
	Vec3 pos, dir;
	double closestT;
	const Triangle* closestTriangle;
	Vec3* interPoint;


	Ray(Vec3 pos, Vec3 dir) : pos{ pos }, dir{ dir }, closestT(DBL_MAX), closestTriangle(nullptr), interPoint{ nullptr } {}
	Ray() = default;
	~Ray() = default;
	double getT(const Triangle* triangle) const;
	bool intersect(const Triangle* triangle);

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
