#pragma once

#include "Vec3.h"

class Triangle;

class Ray
{
public:
	Vector::Vec3 pos, dir;

	Ray(Vector::Vec3 pos, Vector::Vec3 dir) : pos{ pos }, dir{ dir }{}

	float getT(const Triangle& triangle) const;
	bool intersects(const Triangle& triangle, Vector::Vec3& interPoint) const;
};

inline std::ostream& operator<<(std::ostream& os, const Ray& r)
{
	os << "Ray(pos: " << r.pos << ", dir: " << r.dir << ")";
	return os;
}


