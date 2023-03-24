#pragma once

#include "Vec3.h"

class Triangle;

class Ray
{
public:
	Vector::Vec3 pos, dir;
	double closestDis;
	const Triangle* closestTriangle;
	Vector::Vec3& interPoint;

	Ray(Vector::Vec3 pos, Vector::Vec3 dir) : pos{ pos }, dir{ dir }, closestDis(__DBL_MAX__), closestTriangle(nullptr){}

	double getT(const Triangle& triangle) const;
	bool intersects(const Triangle& triangle);
};

inline std::ostream& operator<<(std::ostream& os, const Ray& r)
{
	os << "Ray(pos: " << r.pos << ", dir: " << r.dir << ")";
	return os;
}


