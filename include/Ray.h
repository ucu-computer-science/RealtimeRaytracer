//
// Created by ADMIN on 19-Mar-23.
//

#ifndef RAY_TRACING_RAY_H
#define RAY_TRACING_RAY_H


#include "Triangle.h"
#include "Vec3.h"

class Ray {

	Vec3& pos, & dir;
	[[nodiscard]] float det(const Vec3& v1, const Vec3& v2, const Vec3& v3) const;
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

		float d = det(triangle.getP1(), triangle.getP2(), triangle.getP3());


		if (det(I, triangle.getP2(), triangle.getP3()) / d < 0)
			return false;
		if (det(triangle.getP1(), I, triangle.getP3()) / d < 0)
			return false;
		if (det(triangle.getP2(), triangle.getP2(), I) / d < 0)
			return false;
		return true;
	}
};


#endif //RAY_TRACING_RAY_H