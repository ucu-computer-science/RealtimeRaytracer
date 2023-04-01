#include "GraphicalObject.h"

#include "Camera.h"
#include "Raycast.h"
#include "Scene.h"
#include "SDLDisplayer.h"
#include "Triangle.h"
#include "mathExtensions.h"

GraphicalObject::GraphicalObject(const glm::vec3 pos, glm::quat rot) : Object(pos, rot)
{
	Scene::graphicalObjects.emplace_back(this);
	SDLDisplayer::onUpdate += [this] { updateCameraFacingTriangles(); };
}
void GraphicalObject::setColor(Color color) const
{
	for (const auto triangle : triangles)
	{
		triangle->color = color;
	}
}

void GraphicalObject::intersect(Ray& ray)
{
	for (const auto triangle : cameraFacingTriangles)
	{
		ray.intersect(triangle);
	}
}
void GraphicalObject::updateCameraFacingTriangles()
{
	cameraFacingTriangles.clear();
	for (auto triangle : triangles)
	{
		auto dir = triangle->p1 - Camera::instance->getPos();
		if (!triangle->isTwoSided &&
			dot(triangle->planeEq.norm, dir) >= 0)
			continue;
		cameraFacingTriangles.emplace_back(triangle);
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
Square::Square(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) : GraphicalObject(p1)
{
	triangles.emplace_back(new Triangle{p1, p2, p3});
	triangles.emplace_back(new Triangle{p2, p3, p2 + p3 - p1});
}

Cube::Cube(glm::vec3 pos, glm::quat rot, float side) : GraphicalObject(pos, rot)
{
	glm::vec3 p1 = pos + rot * glm::vec3(-side / 2, -side / 2, -side / 2);
	glm::vec3 p2 = pos + rot * glm::vec3(-side / 2, -side / 2, side / 2);
	glm::vec3 p3 = pos + rot * glm::vec3(side / 2, -side / 2, side / 2);
	glm::vec3 p4 = pos + rot * glm::vec3(side / 2, -side / 2, -side / 2);

	glm::vec3 p5 = pos + rot * glm::vec3(-side / 2, side / 2, -side / 2);
	glm::vec3 p6 = pos + rot * glm::vec3(-side / 2, side / 2, side / 2);
	glm::vec3 p7 = pos + rot * glm::vec3(side / 2, side / 2, side / 2);
	glm::vec3 p8 = pos + rot * glm::vec3(side / 2, side / 2, -side / 2);

	triangles.emplace_back(new Triangle(p1, p3, p2));
	triangles.emplace_back(new Triangle(p1, p4, p3));
	triangles.emplace_back(new Triangle(p5, p6, p7));
	triangles.emplace_back(new Triangle(p5, p7, p8));

	triangles.emplace_back(new Triangle(p1, p2, p6));
	triangles.emplace_back(new Triangle(p1, p6, p5));
	triangles.emplace_back(new Triangle(p4, p7, p3));
	triangles.emplace_back(new Triangle(p4, p8, p7));

	triangles.emplace_back(new Triangle(p2, p3, p7));
	triangles.emplace_back(new Triangle(p2, p7, p6));
	triangles.emplace_back(new Triangle(p1, p8, p4));
	triangles.emplace_back(new Triangle(p1, p5, p8));
}


void Cube::intersect(Ray& ray)
{
	int interCount = 0;
	for (const auto triangle : cameraFacingTriangles)
	{
		if (ray.intersect(triangle))
		{
			if (++interCount == 2)
				return;
		}
	}
}


void Sphere::intersect(Ray& ray)
{
	float x0, x1;
	auto inter = (ray.pos - pos);
	float a = dot(ray.dir, ray.dir);
	float b = dot(ray.dir + ray.dir, inter);
	float c = fabsf(dot(inter, inter)) - radiusSquared;
	if (solveQuadratic(a, b, c, x0, x1))
	{
		if (x0 > 0 && x0 < ray.closestT)
		{
			ray.closestT = x0;
			ray.color = color;
			ray.interPoint = ray.pos + x0 * ray.dir;
			ray.normal = ray.interPoint - pos;
		}
	}
}
void Plane::intersect(Ray& ray)
{
	float denom = dot(normal, ray.dir);
	if (denom > 1e-6)
	{
		glm::vec3 p0l0 = pos - ray.pos;
		float t = dot(p0l0, normal) / denom;
		if (t < ray.closestT && t >= 0)
		{
			ray.closestT = t;
			ray.color = color;
			ray.interPoint = ray.pos + t * ray.dir;
			ray.normal = normal;
		}
	}
}

SquarePyramid::SquarePyramid(glm::vec3 pos, glm::quat rot, float side, float height): GraphicalObject(pos, rot)
{
	auto p1 = pos + (left() + backward()) * side * 0.5f;
	auto p2 = pos + (left() - backward()) * side * 0.5f;
	auto p3 = pos + (-left() - backward()) * side * 0.5f;
	auto p4 = pos + (-left() + backward()) * side * 0.5f;
	auto peak = pos + up() * height;

	triangles.emplace_back(new Triangle(p1, p3, p2));
	triangles.emplace_back(new Triangle(p1, p4, p3));

	triangles.emplace_back(new Triangle(p1, p2, peak));
	triangles.emplace_back(new Triangle(p2, p3, peak));
	triangles.emplace_back(new Triangle(p3, p4, peak));
	triangles.emplace_back(new Triangle(p4, p1, peak));
}
