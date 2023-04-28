#pragma once

#include <glm/gtx/string_cast.hpp>
#include <glm/vec3.hpp>

#include "GraphicalObject.h"
#include "IBoundable.h"
#include "Vertex.h"

class Triangle : public IBoundable
{
	GraphicalObject* obj = nullptr;
	std::vector<Vertex> localPoints;
	glm::vec3 localNormal;

public:
    bool isTwoSided;
    std::vector<glm::vec3> points;
    glm::vec3 normal{};

    void updateGeometry();
    // precalculated
    glm::vec3 row1{};
    glm::vec3 row2{};
    glm::vec3 row3{};
    float valRow1{};
    float valRow2{};
    float valRow3{};


	Triangle(GraphicalObject* obj, Vertex p1, Vertex p2, Vertex p3, bool isTwoSided = false);
	void attachTo(GraphicalObject* obj);
	void recalculateValues();

	bool intersect(Ray& ray, bool intersectAll = false) override;
	AABB getBoundingBox() const override;
	glm::vec3 getCenter() const override;

    Color getColorAt(float u, float v) const;
    glm::vec3 getNormalAt(float u, float v, bool invert) const;
};
//class MeshTriangle: public Triangle{
//public:
//    uv1, uv2, uv3;
//    MeshTriangle(GraphicalObject* obj, ExtendedVertice &p1, ExtendedVertice &p2, ExtendedVertice &p3):
//    Triangle{obj, p1.vertice, p2.vertice, p3.vertice}{};
//};