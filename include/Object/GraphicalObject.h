#pragma once

#include "Object.h"
#include "glm/vec3.hpp"
#include "Material.h"
#include <vector>

class AABB;
struct Ray;
class Triangle;

class GraphicalObject : public Object
{
protected:
	std::vector<std::shared_ptr<Triangle>> triangles{};

public:
	std::vector<std::shared_ptr<Triangle>> cameraFacingTriangles{};
	Material material;

	explicit GraphicalObject(glm::vec3 pos = {0, 0, 0}, glm::quat rot = {1, 0, 0, 0}, Material material = {});

	void setMaterial(Material material);
	void addTriangles(std::vector<std::shared_ptr<Triangle>>& triangles);

	virtual bool intersect(Ray& ray, bool intersectAll = false);
	virtual bool getBoundingBox(AABB& box) const;
	virtual bool includeInBVH() { return true; }

	void updateCameraFacingTriangles();
};

class ImportedGraphicalObject : GraphicalObject
{
public:
	std::string importPath;

	ImportedGraphicalObject(const std::string& path);
};

class Square : public GraphicalObject
{
public:
	Square(glm::vec3 pos, glm::quat rot, float side, Material mat = Material());

	bool includeInBVH() override { return false; }
};

class Cube final : public GraphicalObject
{
public:
	Cube(glm::vec3 pos, glm::quat rot, float side);
};

class Sphere final : public GraphicalObject
{
	float radius;
	float radiusSquared;

public:
	Sphere(glm::vec3 pos, float radius, Color color) : GraphicalObject(pos), radius(radius), radiusSquared{radius * radius}
	{
		material.color = color;
	}

	bool intersect(Ray& ray, bool intersectAll) override;
	bool getBoundingBox(AABB& box) const override;
};

class Plane final : public GraphicalObject
{
	glm::vec3 normal;

public:
	Plane(glm::vec3 pos, glm::vec3 normal, Color color) : GraphicalObject(pos), normal{normalize(normal)}
	{
		material.color = color;
	}

	bool intersect(Ray& ray, bool intersectAll) override;
	bool getBoundingBox(AABB& box) const override { return false; }
	bool includeInBVH() override { return false; }
};
