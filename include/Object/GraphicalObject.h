#pragma once

#include "Color.h"
#include "Object.h"
#include "glm/vec3.hpp"
#include "Material.h"
#include <vector>

class AABB;
struct Ray;
class Triangle;

class GraphicalObject : public Object
{
public:
	Material material;
	std::vector<Triangle*> triangles{};
	std::vector<Triangle*> cameraFacingTriangles{};

	explicit GraphicalObject(glm::vec3 pos = {0, 0, 0}, glm::quat rot = {1, 0, 0, 0},
	                         Color color = {1, 1, 1}, float reflection = 0);

	void setColor(Color color);
	void setReflection(float reflection);
	void setMaterial(Material material);

	virtual bool intersect(Ray& ray, bool intersectAll = false);
	virtual bool getBoundingBox(AABB& box) const;
	virtual bool includeInBVH() { return true; }

	void updateCameraFacingTriangles();
};

class Square : public GraphicalObject
{
public:
	Square(glm::vec3 pos, glm::quat rot, float side);
	Square(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
};

class Cube final : public GraphicalObject
{
public:
	Cube(glm::vec3 pos, glm::quat rot, float side);
};

class Sphere final : public GraphicalObject
{
	float radius;
	Color color;

	float radiusSquared;

public:
	Sphere(glm::vec3 pos, float radius, Color color) : GraphicalObject(pos), radius(radius), color{color},
	                                                   radiusSquared{radius * radius} {}

	bool intersect(Ray& ray, bool intersectAll) override;
	bool getBoundingBox(AABB& box) const override;
};

class Plane final : public GraphicalObject
{
	Color color;
	glm::vec3 normal;

public:
	Plane(glm::vec3 pos, glm::vec3 normal, Color color) : GraphicalObject(pos), color{color},
	                                                      normal{normalize(normal)} {}

	bool intersect(Ray& ray, bool intersectAll) override;
	bool getBoundingBox(AABB& box) const override { return false; }
	bool includeInBVH() override { return false; }
};
