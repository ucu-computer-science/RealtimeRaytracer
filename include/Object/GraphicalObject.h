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

	virtual void setColor(Color color) const;

	virtual void intersect(Ray& ray);
};





class Cube final : public GraphicalObject
{
public:
	Cube(glm::vec3 pos, float side);

	void intersect(Ray& ray) override;
};

class Sphere final: public GraphicalObject {
  float radiusSquared;
  Color color;
public:
  Sphere(glm::vec3 pos, float radiusSquared, Color color): GraphicalObject(pos),
                                               radiusSquared{radiusSquared},
                                                            color{color}{};
  void intersect(Ray& ray) override;
};

class Plane: public GraphicalObject {
  // note: the position is now the normal of the plane
  Color color;
  glm::vec3 normal;
public:
  Plane(glm::vec3 pos, glm::vec3 normal, Color color): GraphicalObject(pos),
                                                       normal{normal},
                                                        color{color}
                                                        {};
  void intersect(Ray& ray) override;
};

class Square: public GraphicalObject
{

public:
  Square(glm::vec3 pos, float side);
//  Square(glm::vec3 P1, glm::vec3 P2);
  Square(glm::vec3 P1, glm::vec3 P2, glm::vec3 P3);
};

class SquarePyramid: public Square{
public:
  SquarePyramid(glm::vec3 P1,
                glm::vec3 P2,
                glm::vec3 P3,
                glm::vec3 peak);;
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