#include "GraphicalObject.h"

#include <memory>
#include <utility>

#include "Camera.h"
#include "MathExtensions.h"
#include "Scene.h"
#include "Triangle.h"
#include "ObjectParser.h"
#include "Ray.h"


GraphicalObject::GraphicalObject(glm::vec3 pos, glm::quat rot) : Object(pos, rot)

{
	this->indexID = Scene::graphicalObjects.size();
	Scene::graphicalObjects.emplace_back(this);
}

Mesh::Mesh(glm::vec3 pos, std::vector<Triangle*> triangles, glm::quat rot) : GraphicalObject(pos, rot), triangles(std::move(triangles))
{
	for (auto& t : this->triangles)
	{
		t->attachTo(this);
		Scene::triangles.push_back(t);
	}
}
Mesh::~Mesh()
{
	for (const auto& triangle : triangles)
		delete triangle;
}

//void Mesh::updateCameraFacingTriangles()
//{
//	cameraFacingTriangles.clear();
//	for (const auto& triangle : triangles)
//	{
//		auto dir = triangle->vertices[0].pos - Camera::instance->getPos();
//		if (dot(triangle->globalNormal, dir) >= 0)
//			continue;
//		cameraFacingTriangles.emplace_back(triangle);
//	}
//}

Square::Square(glm::vec3 pos, float side, glm::quat rot) : Mesh(pos, generateTriangles(side), rot) {}

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


Sphere::Sphere(glm::vec3 pos, float radius) : GraphicalObject(pos, {}), radius(radius), radiusSquared(radius * radius) { }

bool Sphere::intersect(Ray& ray)
{
	float x0, x1;
	auto inter = (ray.pos - pos);
	float a = dot(ray.dir, ray.dir);
	float b = dot(ray.dir + ray.dir, inter);
	float c = fabsf(dot(inter, inter)) - radiusSquared;
	if (solveQuadratic(a, b, c, x0, x1))
	{
		if (x0 > 0 && x0 < ray.closestT && x0 < ray.maxDist)
		{
			ray.closestT = x0;
			ray.interPoint = ray.pos + x0 * ray.dir;
			ray.surfaceNormal = normalize(ray.interPoint - pos);
			ray.closestMat = material;

			auto n = ray.surfaceNormal;
			float u = atan2(-n.x, n.y) / (2.0f * PI) + 0.5f;
			float v = -n.z * 0.5f + 0.5f;
			ray.color = material->getColor(u, v);

			return true;
		}
	}
	return false;
}


Plane::Plane(glm::vec3 pos, glm::vec3 normal) : GraphicalObject({}, pos), normal{normalize(normal)} { }

bool Plane::intersect(Ray& ray)
{
	float denom = -dot(normal, ray.dir);
	if (denom > 1e-6f)
	{
		glm::vec3 dir = pos - ray.pos;
		float t = -dot(dir, normal) / denom;
		if (t < ray.closestT && t > 0 && t < ray.maxDist)
		{
			ray.closestT = t;
			ray.color = material->color;
			ray.interPoint = ray.pos + t * ray.dir;
			ray.surfaceNormal = normal;
			ray.closestMat = material;

			return true;
		}
	}
	return false;
}


nlohmann::basic_json<> GraphicalObject::toJson()
{
	auto j = Object::toJson();
	j["material"]["color"][0] = material->color[0];
	j["material"]["color"][1] = material->color[1];
	j["material"]["color"][2] = material->color[2];
	j["material"]["texturePath"] = material->texture->getPath();
	j["material"]["lit"] = material->lit;
	j["material"]["diffuseCoeff"] = material->diffuseCoeff;
	j["material"]["specularCoeff"] = material->specularCoeff;
	j["material"]["specularDegree"] = material->specularDegree;
	j["material"]["reflection"] = material->reflection;
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
