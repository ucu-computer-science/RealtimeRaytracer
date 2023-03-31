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

	explicit GraphicalObject(glm::vec3 pos);

	void setColor(Color color) const;

	virtual void intersect(Ray& ray);
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

class Sphere final: public GraphicalObject {
  float radiusSquared;
public:
  Sphere(glm::vec3 pos, float radiusSquared): GraphicalObject(pos),
                                               radiusSquared{radiusSquared}{};
  void intersect(Ray& ray) override;
};