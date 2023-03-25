#pragma once

#include "Color.h"
#include "Vec3.h"

class Triangle
{
	struct PlaneEq
	{
		Vec3 norm;
		double d;

		PlaneEq(Vec3 norm, const double d) : norm{ norm }, d{ d } {}
	};

	Vec3 p1, p2, p3;
	PlaneEq planeEq;

	PlaneEq calcPlaneEq() const
	{
		Vec3 normal = (p2 - p1).cross(p3 - p1).normalized();
		return { normal, normal * p1 };
	}

public:
	Color color;
	double determinant;
	Triangle(Vec3 p1, Vec3 p2, Vec3 p3, Color color = Color::white()) : p1{ p1 }, p2{ p2 }, p3{ p3 }, planeEq{ calcPlaneEq() }, color{ color }, determinant(Vec3::det(p1, p2, p3)){}

	const PlaneEq& getPlaneEq() const { return planeEq; }
	const Vec3& getNorm() const { return planeEq.norm; }
	double getD() const { return planeEq.d; }

	const Vec3& P1() const { return p1; }
	const Vec3& P2() const { return p2; }
	const Vec3& P3() const { return p3; }

	void setColor(const Color color) { this->color = color; }
};

inline std::ostream& operator<<(std::ostream& os, const Triangle& t)
{
	os << "Triangle(" << t.P1() << ", " << t.P2() << ", " << t.P3() << ")";
	return os;
}
