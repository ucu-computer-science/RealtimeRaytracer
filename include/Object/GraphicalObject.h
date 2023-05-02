#pragma once

#include <glm/vec3.hpp>
#include <vector>

#include "Object.h"
#include "Material.h"
#include "Texture.h"

class BVHNode;
class AABB;
struct Ray;
class Triangle;

class GraphicalObject : public Object
{
public:
	int indexID = -1;

	std::vector<std::shared_ptr<Triangle>> triangles{};
	//std::vector<std::shared_ptr<Triangle>> cameraFacingTriangles{};
	Material material;
	std::shared_ptr<BVHNode> root;

	GraphicalObject(const std::vector<std::shared_ptr<Triangle>>& triangles = {}, glm::vec3 pos = {0, 0, 0}, glm::quat rot = {1, 0, 0, 0}, Material material = {});

	virtual bool intersect(Ray& ray, bool intersectAll = false);
	//void updateCameraFacingTriangles();

	void setMaterial(const Material& material);

	nlohmann::basic_json<> toJson() override;
};

class ImportedGraphicalObject : public GraphicalObject
{
public:
	std::filesystem::path path;

	ImportedGraphicalObject(const std::filesystem::path& path, glm::vec3 pos = {0, 0, 0}, glm::quat rot = {{0, 0, 0}});

	nlohmann::basic_json<> toJson() override;
};

class Square : public GraphicalObject
{
public:
	Square(glm::vec3 pos, glm::quat rot, float side, Material mat = Material());
	std::vector<std::shared_ptr<Triangle>> generateTriangles(float side);
};

class Cube final : public GraphicalObject
{
public:
	float side;

	Cube(glm::vec3 pos, glm::quat rot, float side);
	std::vector<std::shared_ptr<Triangle>> generateTriangles(float side);

	nlohmann::basic_json<> toJson() override;
};

class Sphere final : public GraphicalObject
{
	float radiusSquared;

public:
	float radius;

	Sphere(glm::vec3 pos, float radius, Color color = Color::white()) : GraphicalObject({}, pos), radius(radius), radiusSquared{radius * radius}
	{
		material.color = color;
	}

	bool intersect(Ray& ray, bool intersectAll) override;

	nlohmann::basic_json<> toJson() override;
};

class Plane final : public GraphicalObject
{
public:
	glm::vec3 normal;

	Plane(glm::vec3 pos, glm::vec3 normal, Color color = Color::white()) : GraphicalObject({}, pos), normal{normalize(normal)}
	{
		material.color = color;
	}

	bool intersect(Ray& ray, bool intersectAll) override;

	nlohmann::basic_json<> toJson() override;
};
