#pragma once

#include "Color.h"
#include "glmExtension.h"
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

		PlaneEq(glm::vec3 norm, float d) : norm{ norm }, d{ d } {}
	};

	glm::vec3 p1, p2, p3;
	PlaneEq planeEq;
	glm::vec3 cofVec1;
	glm::vec3 cofVec2;
	glm::vec3 cofVec3;

	PlaneEq calcPlaneEq() const
	{
		glm::vec3 normal = cross(p2 - p1, p3 - p1);
		return { normal, dot(normal, p1) };
	}
	int setDetSign() const
	{
//#define DEBUG
#ifdef DEBUG
		//std::cout << to_string(p1) << ' ' << to_string(p2) << ' ' << to_string(p3) << '\n';
		std::cout << to_string(getNorm());
#endif

		float d = det(p1, p2, p3);
		if (d > 0)
			return 1;
		if (d < 0)
			return -1;
		return 0;
	}

public:
	Color color;
	int detSign;
	glm::vec3 edge1;
	glm::vec3 edge2;
	glm::vec3 row1;
	glm::vec3 row2;
	glm::vec3 row3;
	float valRow1;
	float valRow2;
	float valRow3;


	Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, Color color = Color::white()) : p1{ p1 + 0.0001f },
		p2{ p2 + 0.0001f }, p3{ p3 + 0.0001f },
		planeEq{ calcPlaneEq() }, cofVec1(getRowCofactorVec(1)), cofVec2(getRowCofactorVec(2)),
		cofVec3(getRowCofactorVec(3)), color{ color }, detSign(setDetSign()),
	edge1(P2() - P1()), edge2(P3() - P1())
	{
		auto e1 = edge1;
		auto e2 = edge2;
		// Compute normal:
		auto normal = getNorm();

		// Depending on which component of the normal is largest, calculate coefficients:
		if (fabs(normal.x) > fabs(normal.y) && fabs(normal.x) > fabs(normal.z)) {
			row1 = {0.0f, e2.z / normal.x, -e2.y / normal.x};
			valRow1 = cross(p3, p1).x / normal.x;

			row2 = {0.0f, -e1.z / normal.x, e1.y / normal.x};
			valRow2 = -cross(p2, p1).x / normal.x;

			row3 = {1.0f, normal.y / normal.x, normal.z / normal.x};
			valRow3 = -dot(p1, normal) / normal.x;




		}
		else if (fabs(normal.y) > fabs(normal.z)) {
			row1 = {-e2.z / normal.y, 0.0f, e2.x / normal.y};
			valRow1 = cross(p3, p1).y / normal.y;


			row2 = {e1.z / normal.y, 0.0f, -e1.x / normal.y};
			valRow2 = -cross(p2, p1).y / normal.y;

			row3 = {normal.x / normal.y, 1.0f, normal.z / normal.y};
			valRow3 = -dot(p1, normal) / normal.y;



		}
		else if (fabs(normal.z) > 0.0f) {
			row1 = {e2.y / normal.z, -e2.x / normal.z, 0.0f};
			valRow1 = cross(p3, p1).z / normal.z;


			row2 = {-e1.y / normal.z, e1.x / normal.z, 0.0f};
			valRow2 = -glm::cross(p2, p1).z / normal.z;

			row3 = {normal.x / normal.z, normal.y / normal.z, 1.0f};
			valRow3 = -dot(p1, normal) / normal.z;




		}
		else {
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
	

	const PlaneEq& getPlaneEq() const { return planeEq; }
	const glm::vec3& getNorm() const { return planeEq.norm; }

	float getD() const { return planeEq.d; }

	const glm::vec3& P1() const { return p1; }
	const glm::vec3& P2() const { return p2; }
	const glm::vec3& P3() const { return p3; }

	void setColor(const Color color) { this->color = color; }

	inline glm::vec3 getRowCofactorVec(int row)
	{
		if (row == 1)
			return {
				p2[1] * p3[2] - p3[1] * p2[2],
				-(p2[0] * p3[2] - p3[0] * p2[2]),
				p2[0] * p3[1] - p3[0] * p2[1]
			};
		if (row == 2)
			return {
				-(p1[1] * p3[2] - p3[1] * p1[2]),
				p1[0] * p3[2] - p3[0] * p1[2],
				-(p1[0] * p3[1] - p3[0] * p1[1])
			};
		return {
			p1[1] * p2[2] - p2[1] * p1[2],
			-(p1[0] * p2[2] - p2[0] * p1[2]),
			p1[0] * p2[1] - p2[0] * p1[1]
		};
	}
	float optimizedDet(glm::vec3 p, int row) const
	{
		return dot(p, row == 1 ? cofVec1 : row == 2 ? cofVec2 : cofVec3);
	}

};

inline std::ostream& operator<<(std::ostream& os, const Triangle& t)
{
	os << "Triangle(" << to_string(t.P1()) << ", " << to_string(t.P2()) << ", " << to_string(t.P3()) << ")";
	return os;
}
