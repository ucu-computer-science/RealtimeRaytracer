#pragma once

#include <glm/vec3.hpp>
#include <vector>

#include "Object.h"
#include "Material.h"
#include "Texture.h"
#include "IBoundable.h"

class BVHNode;
class AABB;
struct Ray;
class Triangle;

class GraphicalObject : public Object, public IBoundable
{
public:
	std::vector<std::shared_ptr<Triangle>> triangles{};
	std::vector<std::shared_ptr<Triangle>> cameraFacingTriangles{};
	Material material;
	std::shared_ptr<BVHNode> root;

	GraphicalObject(const std::vector<std::shared_ptr<Triangle>>& triangles = {}, glm::vec3 pos = {0, 0, 0}, glm::quat rot = {1, 0, 0, 0}, Material material = {});

	bool intersect(Ray& ray, bool intersectAll = false) override;
	AABB getBoundingBox() const override;
	glm::vec3 getCenter() const override { return pos; }

	void updateBVH();
	void updateCameraFacingTriangles();

	void setMaterial(Material material);

	nlohmann::basic_json<> toJson() override;
};

class ImportedGraphicalObject : public GraphicalObject {
public:
	std::filesystem::path path;

    ImportedGraphicalObject(const std::filesystem::path& path);

    nlohmann::basic_json<> toJson() override;
};

class Square : public GraphicalObject
{
public:
	Square(glm::vec3 pos, glm::quat rot, float side, Material mat = Material());

	std::vector<std::shared_ptr<Triangle>> generateTriangles(float side);

//	bool includeInBVH() override { return false; }
};

class Cube final : public GraphicalObject
{
public:
    float side;
    std::vector<std::shared_ptr<Triangle>> generateTriangles(float side);

    Cube(glm::vec3 pos, glm::quat rot, float side);

    nlohmann::basic_json<> toJson() override;
};

class Sphere final : public GraphicalObject
{
	float radius;
	float radiusSquared;

public:
	Sphere(glm::vec3 pos, float radius, Color color) : GraphicalObject({}, pos), radius(radius), radiusSquared{radius * radius}
	{
		material.color = color;
	}

	bool intersect(Ray& ray, bool intersectAll) override;
    AABB getBoundingBox() const override;

    nlohmann::basic_json<> toJson() override;
};

class Plane final : public GraphicalObject
{

public:
	Plane(glm::vec3 pos, glm::vec3 normal, Color color) : GraphicalObject({}, pos), normal{normalize(normal)}
	{
		material.color = color;
	}

	bool intersect(Ray& ray, bool intersectAll) override;
	bool includeInBVH() override { return false; }

    glm::vec3 normal;

    nlohmann::basic_json<> toJson() override;
};