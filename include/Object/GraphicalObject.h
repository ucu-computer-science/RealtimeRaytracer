#pragma once

#include <vector>
#include "Color.h"
#include "Object.h"
#include "glm/vec3.hpp"

class Ray;
class Triangle;



class GraphicalObject : public Object
{
public:
	std::vector<Triangle*> triangles{};
	std::vector<Triangle*> cameraFacingTriangles{};

	explicit GraphicalObject(glm::vec3 pos);

	void setColor(Color color) const;
	virtual void intersect(Ray& ray);

	void updateCameraFacingTriangles();
};


class Square final : public GraphicalObject
{
public:
	Square(glm::vec3 pos, float side);
};


class Cube final : public GraphicalObject
{
public:
	Cube(glm::vec3 pos, float side);

	void intersect(Ray& ray) override;
};

class Sphere final : public GraphicalObject
{
	float radiusSquared;
	Color color;

public:
	Sphere(glm::vec3 pos, float radiusSquared, Color color) : GraphicalObject(pos), radiusSquared{ radiusSquared },
	                                                          color{ color } {}
	void intersect(Ray& ray) override;
};

class Plane final : public GraphicalObject
{
	Color color;
	glm::vec3 normal;

public:
	Plane(glm::vec3 pos, glm::vec3 normal, Color color) : GraphicalObject(pos), color{ color }, normal{ normal } {}
	void intersect(Ray& ray) override;
};
