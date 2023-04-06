#pragma once

#include "Color.h"
#include "glm/vec3.hpp"
#include "glm/geometric.hpp"
#include "glm/gtx/string_cast.hpp"
#include <iostream>

class Triangle
{
	struct PlaneEq
	{
		glm::vec3 norm;
		float d;

		PlaneEq(glm::vec3 norm, float d) : norm{norm}, d{d} {}
	};

	PlaneEq calcPlaneEq(bool normalize) const
	{
		glm::vec3 normal = cross(p2 - p1, p3 - p1);
		return {normalize ? glm::normalize(normal) : normal, dot(normal, p1)};
	}
      int64_t filler{};
public:
	glm::vec3 p1, p2, p3;
	PlaneEq planeEq;
	Color color;
	float reflection;
	bool isTwoSided;

	// precalculated
	glm::vec3 row1{};
	glm::vec3 row2{};
	glm::vec3 row3{};
	float valRow1{};
	float valRow2{};
	float valRow3{};



	void recalculateValues()
	{
		auto e1 = p2 - p1;
		auto e2 = p3 - p1;
		auto normal = calcPlaneEq(false).norm;

		// Depending on which component of the normal is largest, calculate coefficients:
		if (fabs(normal.x) > fabs(normal.y) && fabs(normal.x) > fabs(normal.z))
		{
			row1 = {0.0f, e2.z / normal.x, -e2.y / normal.x};
			valRow1 = cross(p3, p1).x / normal.x;
			row2 = {0.0f, -e1.z / normal.x, e1.y / normal.x};
			valRow2 = -cross(p2, p1).x / normal.x;
			row3 = {1.0f, normal.y / normal.x, normal.z / normal.x};
			valRow3 = -dot(p1, normal) / normal.x;
		}
		else if (fabs(normal.y) > fabs(normal.z))
		{
			row1 = {-e2.z / normal.y, 0.0f, e2.x / normal.y};
			valRow1 = cross(p3, p1).y / normal.y;
			row2 = {e1.z / normal.y, 0.0f, -e1.x / normal.y};
			valRow2 = -cross(p2, p1).y / normal.y;
			row3 = {normal.x / normal.y, 1.0f, normal.z / normal.y};
			valRow3 = -dot(p1, normal) / normal.y;
		}
		else if (fabs(normal.z) > 0.0f)
		{
			row1 = {e2.y / normal.z, -e2.x / normal.z, 0.0f};
			valRow1 = cross(p3, p1).z / normal.z;
			row2 = {-e1.y / normal.z, e1.x / normal.z, 0.0f};
			valRow2 = -glm::cross(p2, p1).z / normal.z;
			row3 = {normal.x / normal.z, normal.y / normal.z, 1.0f};
			valRow3 = -dot(p1, normal) / normal.z;
		}
		else
		{
			// This triangle is degenerate. Set the transformation matrix to
			// the 0 matrix, which in turn will yield 0 values in places that
			// intersection calculations will detect and treat as a miss.
			row1 = {};
			valRow1 = 0.0f;
			row2 = {};
			valRow2 = 0.0f;
			row3 = {};
			valRow3 = 0.0f;
		}
	}
	void recalculatePlaneEq()
	{
		planeEq = calcPlaneEq(true);
	}
	Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, Color color = Color::white(),
	         bool isTwoSided = false) : p1{p1}, p2{p2}, p3{p3}, planeEq{calcPlaneEq(true)},
	                                    color{color}, reflection{0}, isTwoSided(isTwoSided)
	{
		recalculateValues();
	}
};

inline std::ostream& operator<<(std::ostream& os, const Triangle& t)
{
	os << "Triangle(" << to_string(t.p1) << ", " << to_string(t.p2) << ", " << to_string(t.p3) << ")";
	return os;
}