#pragma once

#include <glm/gtx/string_cast.hpp>

#include "GraphicalObject.h"
#include "Vertex.h"

class Triangle
{
	glm::vec3 localNormal;

public:
	Mesh* mesh = nullptr;

	std::vector<Vertex> vertices;
	std::vector<glm::vec3> globalVertexPositions;
	std::vector<glm::vec3> globalVertexNormals;
	glm::vec3 globalNormal = {};

	void updateGeometry();

	// precalculated
	glm::vec3 row1{};
	glm::vec3 row2{};
	glm::vec3 row3{};
	float row1Val{};
	float row2Val{};
	float row3Val{};

	glm::vec2 texVecU{};
	glm::vec2 texVecV{};


	Triangle(Mesh* mesh, Vertex v1, Vertex v2, Vertex v3);
	void attachTo(Mesh* obj);
	void recalculateCoefficients();

	bool intersect(Ray& ray, bool intersectAll = false) const;
	Color getColorAt(float u, float v) const;
	glm::vec3 getNormalAt(float u, float v, bool invert) const;

	AABB getBoundingBox() const;
	glm::vec3 getCenter() const;
};
