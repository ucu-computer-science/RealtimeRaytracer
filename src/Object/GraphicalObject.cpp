#include "GraphicalObject.h"
#include "Raycast.h"
#include "Scene.h"
#include "Triangle.h"


GraphicalObject::GraphicalObject(const glm::vec3 pos) : Object(pos)
{
	Scene::graphicalObjects.emplace_back(this);
}
void GraphicalObject::setColor(Color color) const
{
	for (auto triangle : triangles)
	{
		triangle->color = color;
	}
}

void GraphicalObject::intersect(Ray& ray)
{
	for (auto triangle : triangles)
	{
		ray.intersect(*triangle);
	}
}


Square::Square(glm::vec3 pos, float side) : GraphicalObject(pos)
{
	glm::vec3 p1 = pos + glm::vec3(-side / 2, 0, -side / 2);
	glm::vec3 p2 = pos + glm::vec3(-side / 2, 0, side / 2);
	glm::vec3 p3 = pos + glm::vec3(side / 2, 0, side / 2);
	glm::vec3 p4 = pos + glm::vec3(side / 2, 0, -side / 2);
	triangles.emplace_back(new Triangle(p1, p3, p2));
	triangles.emplace_back(new Triangle(p1, p3, p4));
}


Cube::Cube(glm::vec3 pos, float side) : GraphicalObject(pos)
{
	glm::vec3 p1 = pos + glm::vec3(-side / 2, -side / 2, -side / 2);
	glm::vec3 p2 = pos + glm::vec3(-side / 2, -side / 2, side / 2);
	glm::vec3 p3 = pos + glm::vec3(side / 2, -side / 2, side / 2);
	glm::vec3 p4 = pos + glm::vec3(side / 2, -side / 2, -side / 2);

	glm::vec3 p5 = pos + glm::vec3(-side / 2, side / 2, -side / 2);
	glm::vec3 p6 = pos + glm::vec3(-side / 2, side / 2, side / 2);
	glm::vec3 p7 = pos + glm::vec3(side / 2, side / 2, side / 2);
	glm::vec3 p8 = pos + glm::vec3(side / 2, side / 2, -side / 2);

	triangles.emplace_back(new Triangle(p1, p3, p2));
	triangles.emplace_back(new Triangle(p1, p3, p4));
	triangles.emplace_back(new Triangle(p5, p7, p6));
	triangles.emplace_back(new Triangle(p5, p7, p8));

	triangles.emplace_back(new Triangle(p1, p6, p2));
	triangles.emplace_back(new Triangle(p1, p6, p5));
	triangles.emplace_back(new Triangle(p4, p7, p3));
	triangles.emplace_back(new Triangle(p4, p7, p8));

	triangles.emplace_back(new Triangle(p2, p7, p3));
	triangles.emplace_back(new Triangle(p2, p7, p6));
	triangles.emplace_back(new Triangle(p1, p8, p4));
	triangles.emplace_back(new Triangle(p1, p8, p5));
}


void Cube::intersect(Ray& ray)
{
	int interCount = 0;
	for (auto triangle : triangles)
	{
		if (ray.intersect(*triangle))
			interCount++;

		if (interCount == 2)
			break;
	}
}
