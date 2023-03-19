#ifndef RAY_H
#define RAY_H

#include "Triangle.h"
#include "Vec3.h"

class Ray {

	Vec3 pos, dir;
	[[nodiscard]] float det(const Vec3& v1, const Vec3& v2, const Vec3& v3) const;
public:
	Ray(Vec3 pos, Vec3 dir) : pos{ pos }, dir{ dir }{}
	~Ray() = default;
	[[nodiscard]] float getT(const Triangle& triangle) const {
		const auto norm = triangle.getPlaneEq().norm;
		const auto d = triangle.getPlaneEq().d;
		return (norm * pos + d) / (norm * (pos - dir));
	}
	[[nodiscard]] Vec3 getPlaneIntersectionPoint(const Triangle& triangle) const {
		const float t = getT(triangle);
		return (1 - t) * pos + t * dir;
	}
	[[nodiscard]] bool intersects(const Triangle& triangle) const {
		const auto p = getPlaneIntersectionPoint(triangle);

		const float d = det(triangle.P1(), triangle.P2(), triangle.P3());


		if (det(p, triangle.P2(), triangle.P3()) / d < 0)
			return false;
		if (det(triangle.P1(), p, triangle.P3()) / d < 0)
			return false;
		if (det(triangle.P2(), triangle.P2(), p) / d < 0)
			return false;
		return true;
	}
};


#endif // RAY_H
