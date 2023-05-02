#include "GraphicalObject.h"

#include <memory>
#include <utility>

#include "Camera.h"
#include "Scene.h"
#include "Triangle.h"
#include "ObjectParser.h"
#include "Ray.h"


GraphicalObject::GraphicalObject(glm::vec3 pos, glm::quat rot, Material material) : Object(pos, rot), material(std::move(material))

{
	this->indexID = Scene::graphicalObjects.size();
	Scene::graphicalObjects.emplace_back(this);
}


Mesh::Mesh(glm::vec3 pos, std::vector<Triangle*> triangles, glm::quat rot, Material material) : GraphicalObject(pos, rot, std::move(material)),
                                                                                                triangles(std::move(triangles))
{
	for (auto& t : this->triangles)
	{
		t->attachTo(this);
		Scene::triangles.push_back(t);
	}
}


Square::Square(glm::vec3 pos, float side, glm::quat rot, Material material) : Mesh(pos, generateTriangles(side), rot, std::move(material)) {}

std::vector<Triangle*> Square::generateTriangles(float side)
{
	auto p1 = glm::vec3(-side / 2, 0, -side / 2);
	auto p2 = glm::vec3(-side / 2, 0, side / 2);
	auto p3 = glm::vec3(side / 2, 0, side / 2);
	auto p4 = glm::vec3(side / 2, 0, -side / 2);

	Vertex vertex1{p1, {0, 0}};
	Vertex vertex2{p2, {1, 0}};
	Vertex vertex3{p3, {1, 1}};
	Vertex vertex4{p4, {0, 1}};

	std::vector<Triangle*> triangles;
	triangles.push_back(new Triangle(this, vertex1, vertex2, vertex3));
	triangles.push_back(new Triangle(this, vertex1, vertex3, vertex4));
	return triangles;
}


Cube::Cube(glm::vec3 pos, float side, glm::quat rot) : Mesh(pos, generateTriangles(side), rot), side(side) {}

std::vector<Triangle*> Cube::generateTriangles(float side)
{
	auto p1 = glm::vec3(-side / 2, -side / 2, -side / 2);
	auto p2 = glm::vec3(-side / 2, -side / 2, side / 2);
	auto p3 = glm::vec3(side / 2, -side / 2, side / 2);
	auto p4 = glm::vec3(side / 2, -side / 2, -side / 2);

	auto p5 = glm::vec3(-side / 2, side / 2, -side / 2);
	auto p6 = glm::vec3(-side / 2, side / 2, side / 2);
	auto p7 = glm::vec3(side / 2, side / 2, side / 2);
	auto p8 = glm::vec3(side / 2, side / 2, -side / 2);

	std::vector<Triangle*> triangles;
	triangles.push_back(new Triangle(this, p1, p3, p2));
	triangles.push_back(new Triangle(this, p1, p4, p3));
	triangles.push_back(new Triangle(this, p5, p6, p7));
	triangles.push_back(new Triangle(this, p5, p7, p8));

	triangles.push_back(new Triangle(this, p1, p2, p6));
	triangles.push_back(new Triangle(this, p1, p6, p5));
	triangles.push_back(new Triangle(this, p4, p7, p3));
	triangles.push_back(new Triangle(this, p4, p8, p7));

	triangles.push_back(new Triangle(this, p2, p3, p7));
	triangles.push_back(new Triangle(this, p2, p7, p6));
	triangles.push_back(new Triangle(this, p1, p8, p4));
	triangles.push_back(new Triangle(this, p1, p5, p8));
	return triangles;
}


Sphere::Sphere(glm::vec3 pos, float radius, Material material) : GraphicalObject(pos, {}, std::move(material)), radius(radius) { }


Plane::Plane(glm::vec3 pos, glm::vec3 normal, Material material) : GraphicalObject({}, pos, std::move(material)), normal{normalize(normal)} { }


nlohmann::basic_json<> GraphicalObject::toJson()
{
	auto j = Object::toJson();
	j["material"]["color"][0] = material.color[0];
	j["material"]["color"][1] = material.color[1];
	j["material"]["color"][2] = material.color[2];
	j["material"]["texturePath"] = material.texture->getPath();
	j["material"]["lit"] = material.lit;
	j["material"]["diffuseCoeff"] = material.diffuseCoeff;
	j["material"]["specularCoeff"] = material.specularCoeff;
	j["material"]["specularDegree"] = material.specularDegree;
	j["material"]["reflection"] = material.reflection;
	return j;
}

nlohmann::basic_json<> Cube::toJson()
{
	auto j = GraphicalObject::toJson();
	j["type"] = "Cube";
	j["side"] = side;
	return j;
}

nlohmann::basic_json<> Sphere::toJson()
{
	auto j = GraphicalObject::toJson();
	j["type"] = "Sphere";
	j["radius"] = radius;
	return j;
}

nlohmann::basic_json<> Plane::toJson()
{
	auto j = GraphicalObject::toJson();
	j["type"] = "Plane";
	j["normal"][0] = normal[0];
	j["normal"][1] = normal[1];
	j["normal"][2] = normal[2];
	return j;
}
