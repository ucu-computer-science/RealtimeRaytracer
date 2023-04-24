#pragma once

#include "GraphicalObject.h"
#include "glm/gtx/string_cast.hpp"
#include "glm/vec3.hpp"

class Triangle
{
	GraphicalObject* obj = nullptr;
	std::vector<glm::vec3> localPoints;
	glm::vec3 localNormal;

public:
	bool isTwoSided;
	std::vector<glm::vec3> points;
	glm::vec3 normal{};

	void updateLocal();

	// precalculated
	glm::vec3 row1{};
	glm::vec3 row2{};
	glm::vec3 row3{};
	float valRow1{};
	float valRow2{};
	float valRow3{};


	Triangle(GraphicalObject* obj, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, bool isTwoSided = false);
	void attachToObject(GraphicalObject* obj);

	void recalculateValues();
	bool findIntersectionWith(Ray& ray) const;
};
