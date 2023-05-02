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
protected:
	GraphicalObject(glm::vec3 pos = {}, glm::quat rot = {}, Material material = Material());

public:
	int indexID;
	Material material;

	nlohmann::basic_json<> toJson() override;
};


class Mesh : public GraphicalObject
{
public:
	std::vector<Triangle*> triangles{};

	Mesh(glm::vec3 pos, std::vector<Triangle*> triangles, glm::quat rot = {}, Material material = Material());
};


class Square : public Mesh
{
public:
	Square(glm::vec3 pos, float side, glm::quat rot = {}, Material material = Material());
	std::vector<Triangle*> generateTriangles(float side);
};


class Cube final : public Mesh
{
public:
	float side;

	Cube(glm::vec3 pos, float side, glm::quat rot);
	std::vector<Triangle*> generateTriangles(float side);

	nlohmann::basic_json<> toJson() override;
};


class Sphere final : public GraphicalObject
{
public:
	float radius;

	Sphere(glm::vec3 pos, float radius, Material material = Material());

	nlohmann::basic_json<> toJson() override;
};


class Plane final : public GraphicalObject
{
public:
	glm::vec3 normal;

	Plane(glm::vec3 pos, glm::vec3 normal, Material material = Material());

	nlohmann::basic_json<> toJson() override;
};
