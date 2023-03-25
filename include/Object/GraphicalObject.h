#pragma once

#include <vector>

#include "Color.h"
#include "Object.h"

class Ray;
class Triangle;


class GraphicalObject : public Object
{
public:
	std::vector<Triangle*> triangles{};

	explicit GraphicalObject(Vec3 pos);

	void setColor(Color color) const;

	virtual void intersect(Ray& ray);
};


class Square final : public GraphicalObject
{
public:
	Square(Vec3 pos, double side);
};


class Cube final : public GraphicalObject
{
public:
	Cube(Vec3 pos, double side);

	void intersect(Ray& ray) override;
};
