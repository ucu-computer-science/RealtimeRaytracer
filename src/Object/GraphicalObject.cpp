#include "GraphicalObject.h"

#include "Camera.h"
#include "SDLDisplayer.h"
#include "Scene.h"
#include "Triangle.h"
#include "mathExtensions.h"
#include "BoundingBoxes.h"
#include "ObjectParser.h"

GraphicalObject::GraphicalObject(const std::vector<std::shared_ptr<Triangle>>& triangles, const glm::vec3 pos, glm::quat rot,
                                 Material material) : Object(pos, rot), triangles(triangles), material(material)
{
	for (auto& t : triangles)
		t->attachToObject(this);

	if (!triangles.empty())
	{
		updateCameraFacingTriangles();
		updateBVH();
		Scene::graphicalObjects.emplace_back(std::shared_ptr<GraphicalObject>(this));

		Camera::onCameraMove += [this]
		{
			updateCameraFacingTriangles();
			updateBVH();
		};
	}
}

bool GraphicalObject::intersect(Ray& ray, bool intersectAll)
{
	return rootBVH->intersect(ray);
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
AABB GraphicalObject::getBoundingBox() const
{
	if (triangles.empty()) return {{0, 0, 0}, {0, 0, 0}};
	if (triangles.size() == 1) return triangles[0]->getBoundingBox();

	auto united = triangles[0]->getBoundingBox();
	for (size_t i = 1; i < triangles.size(); ++i)
	{
		united = AABB::getUnitedBox(united, triangles[i]->getBoundingBox());
	}
	return united;
}
void GraphicalObject::updateBVH()
{
	auto intersectables = std::vector<std::shared_ptr<IIntersectable>>(cameraFacingTriangles.size());
	std::ranges::transform(cameraFacingTriangles, intersectables.begin(), [](const std::shared_ptr<Triangle>& obj)
	{
		return std::static_pointer_cast<IIntersectable>(obj);
	});
	rootBVH = BVHNode::buildTree(intersectables);
}

ImportedGraphicalObject::ImportedGraphicalObject(const std::string& path) : GraphicalObject(Model(path).triangles), importPath(path) {}

Square::Square(glm::vec3 pos, glm::quat rot, float side, Material mat) : GraphicalObject(generateTriangles(side), pos, rot, mat) {}
std::vector<std::shared_ptr<Triangle>> Square::generateTriangles(float side)
{
	auto p1 = glm::vec3(-side / 2, 0, -side / 2);
	auto p2 = glm::vec3(-side / 2, 0, side / 2);
	auto p3 = glm::vec3(side / 2, 0, side / 2);
	auto p4 = glm::vec3(side / 2, 0, -side / 2);

	std::vector<std::shared_ptr<Triangle>> triangles;
	triangles.emplace_back(std::make_shared<Triangle>(this, p1, p2, p3));
	triangles.emplace_back(std::make_shared<Triangle>(this, p1, p3, p4));
	return triangles;
}

Cube::Cube(glm::vec3 pos, glm::quat rot, float side) : GraphicalObject(generateTriangles(side), pos, rot)
{
	generateTriangles(side);
}
std::vector<std::shared_ptr<Triangle>> Cube::generateTriangles(float side)
{
	auto p1 = glm::vec3(-side / 2, -side / 2, -side / 2);
	auto p2 = glm::vec3(-side / 2, -side / 2, side / 2);
	auto p3 = glm::vec3(side / 2, -side / 2, side / 2);
	auto p4 = glm::vec3(side / 2, -side / 2, -side / 2);

	auto p5 = glm::vec3(-side / 2, side / 2, -side / 2);
	auto p6 = glm::vec3(-side / 2, side / 2, side / 2);
	auto p7 = glm::vec3(side / 2, side / 2, side / 2);
	auto p8 = glm::vec3(side / 2, side / 2, -side / 2);

	std::vector<std::shared_ptr<Triangle>> triangles;
	triangles.emplace_back(std::make_shared<Triangle>(this, p1, p3, p2));
	triangles.emplace_back(std::make_shared<Triangle>(this, p1, p4, p3));
	triangles.emplace_back(std::make_shared<Triangle>(this, p5, p6, p7));
	triangles.emplace_back(std::make_shared<Triangle>(this, p5, p7, p8));

	triangles.emplace_back(std::make_shared<Triangle>(this, p1, p2, p6));
	triangles.emplace_back(std::make_shared<Triangle>(this, p1, p6, p5));
	triangles.emplace_back(std::make_shared<Triangle>(this, p4, p7, p3));
	triangles.emplace_back(std::make_shared<Triangle>(this, p4, p8, p7));

	triangles.emplace_back(std::make_shared<Triangle>(this, p2, p3, p7));
	triangles.emplace_back(std::make_shared<Triangle>(this, p2, p7, p6));
	triangles.emplace_back(std::make_shared<Triangle>(this, p1, p8, p4));
	triangles.emplace_back(std::make_shared<Triangle>(this, p1, p5, p8));
	return triangles;
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
AABB Sphere::getBoundingBox() const
{
	glm::vec3 min = pos - glm::vec3(radius, radius, radius);
	glm::vec3 max = pos + glm::vec3(radius, radius, radius);
	return {min, max};
}
bool Plane::intersect(Ray& ray, bool intersectAll)
{
	float denom = -dot(normal, ray.dir);
	if (denom > 1e-6f)
	{
		glm::vec3 dir = pos - ray.pos;
		float t = -dot(dir, normal) / denom;
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
