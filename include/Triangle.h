#pragma once
#ifndef RAY_TRACING_TRIANGLE_H
#define RAY_TRACING_TRIANGLE_H
#include "Vec3.h"


class Triangle {

	struct PlaneEq {
		Vec3 norm;
		float d;
		PlaneEq(Vec3 norm, const float d) : norm{ norm }, d{ d } {}
		~PlaneEq() = default;
	};


	Vec3 p1, p2, p3;
	PlaneEq planeEq;
	[[nodiscard]] float det(const Vec3& v1, const Vec3& v2, const Vec3& v3) const;
	[[nodiscard]] PlaneEq calcPlaneEq() const {
		return  { (p2 - p1).cross(p3 - p1), det(p1, p2 - p1, p3 - p1) };
	}
public:
	Triangle(Vec3 p1, Vec3 p2, Vec3 p3) : p1{ p1 }, p2{ p2 }, p3{ p3 }, planeEq{ calcPlaneEq() }{};
	~Triangle() = default;
	[[nodiscard]] const PlaneEq& getPlaneEq() const {
		return planeEq;
	}
	[[nodiscard]] const Vec3& getP1() const {
		return p1;
	}
	[[nodiscard]] const Vec3& getP2() const {
		return p2;
	}
	[[nodiscard]] const Vec3& getP3() const {
		return p3;
	}



};
#endif