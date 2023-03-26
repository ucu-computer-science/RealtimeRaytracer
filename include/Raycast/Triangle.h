#pragma once

#include "Color.h"
#include "glmExtension.h"
#include "glm/vec3.hpp"
#include "glm/geometric.hpp"
#include "glm/gtx/string_cast.hpp"
#include <iostream>

//enum DeterminantState {  };
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
		float d = det(p1, p2, p3);
		if (d > 0)
		{
			return 1;
		}
		if (d < 0)
		{
			return -1;
		}
		return 0;
	}
public:
	Color color;

	int detSign;


	Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, Color color = Color::white()) : p1{ p1 }, p2{ p2 }, p3{ p3 },
		planeEq{ calcPlaneEq() }, cofVec1(getRowCofactorVec(1)), cofVec2(getRowCofactorVec(2)),
		cofVec3(getRowCofactorVec(3)), color{ color }, detSign(setDetSign()) { }

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
