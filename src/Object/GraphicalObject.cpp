#include "GraphicalObject.h"
#include "Camera.h"
#include "SDLDisplayer.h"
#include "Scene.h"
#include "Triangle.h"
#include "mathExtensions.h"
#include "BoundingBoxes.h"
#include "ObjectParser.h"

GraphicalObject::GraphicalObject(const glm::vec3 pos, glm::quat rot, Material material) : Object(pos, rot), material(material)
{
	Scene::graphicalObjects.emplace_back(std::shared_ptr<GraphicalObject>(this));
	SDLDisplayer::onUpdate += [this] { updateCameraFacingTriangles(); };
}

bool GraphicalObject::intersect(Ray& ray, bool intersectAll)
{
	bool intersects = false;
	for (const auto& triangle : intersectAll ? triangles : cameraFacingTriangles)
	{
		if (triangle->findIntersectionWith(ray))
		{
			ray.closestObj = this;
			intersects = true;
		}
	}
	return intersects;
}
void GraphicalObject::updateCameraFacingTriangles()
{
	cameraFacingTriangles.clear();
	for (const auto& triangle : triangles)
	{
		auto dir = triangle->points[0] - Camera::instance->getPos();
		if (!triangle->isTwoSided && dot(triangle->normal, dir) >= 0)
			continue;
		cameraFacingTriangles.emplace_back(triangle);
	}
}
bool GraphicalObject::getBoundingBox(AABB& box) const
{
	float x_min = FLT_MAX, x_max = FLT_MIN;
	float y_min = FLT_MAX, y_max = FLT_MIN;
	float z_min = FLT_MAX, z_max = FLT_MIN;

	for (const auto& triangle : triangles)
	{
		for (auto p : triangle->points)
		{
			x_min = std::min(x_min, p.x);
			x_max = std::max(x_max, p.x);

			y_min = std::min(y_min, p.y);
			y_max = std::max(y_max, p.y);

			z_min = std::min(z_min, p.z);
			z_max = std::max(z_max, p.z);
		}
	}
	box = {{x_min, y_min, z_min}, {x_max, y_max, z_max}};
	return true;
}

void GraphicalObject::setMaterial(Material material)
{
	this->material = material;
}
void GraphicalObject::addTriangles(std::vector<std::shared_ptr<Triangle>>& triangles)
{
	for (auto& t : triangles)
	{
		t->attachToObject(this);
		this->triangles.emplace_back(t);
	}
}

ImportedGraphicalObject::ImportedGraphicalObject(const std::string& path) : importPath(path)
{
	importPath = path;

	Model model{path};
	addTriangles(model.triangles);
}

Square::Square(glm::vec3 pos, glm::quat rot, float side, Material mat) : GraphicalObject(pos, rot, mat)
{
	glm::vec3 p1 = pos + rot * glm::vec3(-side / 2, 0, -side / 2);
	glm::vec3 p2 = pos + rot * glm::vec3(-side / 2, 0, side / 2);
	glm::vec3 p3 = pos + rot * glm::vec3(side / 2, 0, side / 2);
	glm::vec3 p4 = pos + rot * glm::vec3(side / 2, 0, -side / 2);

	triangles.emplace_back(new Triangle(this, p1, p2, p3));
	triangles.emplace_back(new Triangle(this, p1, p3, p4));
}

Cube::Cube(glm::vec3 pos, glm::quat rot, float side) : GraphicalObject(pos, rot)
{
	auto p1 = glm::vec3(-side / 2, -side / 2, -side / 2);
	auto p2 = glm::vec3(-side / 2, -side / 2, side / 2);
	auto p3 = glm::vec3(side / 2, -side / 2, side / 2);
	auto p4 = glm::vec3(side / 2, -side / 2, -side / 2);

	auto p5 = glm::vec3(-side / 2, side / 2, -side / 2);
	auto p6 = glm::vec3(-side / 2, side / 2, side / 2);
	auto p7 = glm::vec3(side / 2, side / 2, side / 2);
	auto p8 = glm::vec3(side / 2, side / 2, -side / 2);

	triangles.emplace_back(new Triangle(this, p1, p3, p2));
	triangles.emplace_back(new Triangle(this, p1, p4, p3));
	triangles.emplace_back(new Triangle(this, p5, p6, p7));
	triangles.emplace_back(new Triangle(this, p5, p7, p8));

	triangles.emplace_back(new Triangle(this, p1, p2, p6));
	triangles.emplace_back(new Triangle(this, p1, p6, p5));
	triangles.emplace_back(new Triangle(this, p4, p7, p3));
	triangles.emplace_back(new Triangle(this, p4, p8, p7));

	triangles.emplace_back(new Triangle(this, p2, p3, p7));
	triangles.emplace_back(new Triangle(this, p2, p7, p6));
	triangles.emplace_back(new Triangle(this, p1, p8, p4));
	triangles.emplace_back(new Triangle(this, p1, p5, p8));
}

bool Sphere::intersect(Ray& ray, bool intersectAll)
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
			ray.closestObj = this;

			return true;
		}
	}
	return false;
}
bool Sphere::getBoundingBox(AABB& box) const
{
	glm::vec3 min = pos - glm::vec3(radius, radius, radius);
	glm::vec3 max = pos + glm::vec3(radius, radius, radius);
	box = {min, max};
	return true;
}
bool Plane::intersect(Ray& ray, bool intersectAll)
{
	float denom = -dot(normal, ray.dir);
	if (denom > 1e-6f)
	{
		glm::vec3 p0l0 = pos - ray.pos;
		float t = -dot(p0l0, normal) / denom;
		if (t < ray.closestT && t > 0 && t < ray.maxDist)
		{
			ray.closestT = t;
			ray.interPoint = ray.pos + t * ray.dir;
			ray.surfaceNormal = normal;
			ray.closestObj = this;

			return true;
		}
	}
	return false;
}
