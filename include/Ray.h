#ifndef RAY_H
#define RAY_H

#include "Triangle.h"
#include "Vec3.h"

class Ray {

	Vec3& pos, & dir;
	[[nodiscard]] float det(const Vec3& v1, const Vec3& v2, const Vec3& v3) const{ return Vec3::det(v1, v2, v3);}; // todo
public:
	Ray(Vec3& pos, Vec3& dir) : pos{ pos }, dir{ dir }{}
	~Ray() = default;
	[[nodiscard]] float getT(const Triangle& triangle) const {
		auto norm = triangle.getPlaneEq().norm;
		auto d = triangle.getPlaneEq().d;
		return (norm * pos + d) / (norm * (pos - dir));
	}
	[[nodiscard]] Vec3 getPlaneIntersectionPoint(const Triangle& triangle) const {
		float t = getT(triangle);
		return (1 - t) * pos + t * dir;
	}
	[[nodiscard]] bool intersects(const Triangle& triangle) const {
		auto I = getPlaneIntersectionPoint(triangle);

		float d = det(triangle.P1(), triangle.P2(), triangle.P3());


		if (det(I, triangle.P2(), triangle.P3()) / d < 0)
			return false;
		if (det(triangle.P1(), I, triangle.P3()) / d < 0)
			return false;
		if (det(triangle.P2(), triangle.P2(), I) / d < 0)
			return false;
		return true;
	}
};


#endif // RAY_H
