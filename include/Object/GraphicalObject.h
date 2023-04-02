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
	float reflection;
	Color color;
	std::vector<Triangle*> triangles{};
	std::vector<Triangle*> cameraFacingTriangles{};

	explicit GraphicalObject(glm::vec3 pos, glm::quat rot = {1, 0, 0, 0}, Color color = {1, 1, 1},
	                         float reflection = 0);

	void setColor(Color color);
	void setReflection(float reflection);
	virtual void intersect(Ray& ray, bool intersectAll = false);

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
	float radiusSquared;
	Color color;

public:
	Sphere(glm::vec3 pos, float radiusSquared, Color color) : GraphicalObject(pos), radiusSquared{radiusSquared},
	                                                          color{color} {}
	void intersect(Ray& ray, bool intersectAll) override;
};

class Plane final : public GraphicalObject
{
	Color color;
	glm::vec3 normal;

public:
	Plane(glm::vec3 pos, glm::vec3 normal, Color color) : GraphicalObject(pos), color{color}, normal{normal} {}
	void intersect(Ray& ray, bool intersectAll) override;
};

class SquarePyramid : public GraphicalObject
{
public:
	SquarePyramid(glm::vec3 pos, glm::quat rot, float side, float height);
};


//class SquarePyramid final : public Square
//{
//public:
//  SquarePyramid(glm::vec3 pos, float side): Square(pos, side){
//
//  };
//
//  void intersect(Ray& ray) override;
//};
//class Box: public GraphicalObject
//{
//public:
//  glm::vec3 bounds[2];
//
//  Box(glm::vec3 pos, glm::vec3 vmin, glm::vec3 vmax): GraphicalObject(pos)
//  {
//    bounds[0] = vmin;
//    bounds[1] = vmax;
//  }
//  void intersect(Ray& ray) override;
//};
