#include "GraphicalObject.h"

#include <memory>
#include <utility>

#include "Camera.h"
#include "SDLDisplayer.h"
#include "Scene.h"
#include "Triangle.h"
#include "MathExtensions.h"
#include "BoundingBoxes.h"
#include "ObjectParser.h"
#include "Ray.h"


GraphicalObject::GraphicalObject(const std::vector<std::shared_ptr<Triangle>>& triangles, const glm::vec3 pos, glm::quat rot,
                                 Material material) : Object(pos, rot), triangles(triangles), material(std::move(material))
{
	for (auto& t : triangles)
		t->attachTo(this);

	//updateCameraFacingTriangles();
	updateBVH();
	Scene::graphicalObjects.emplace_back(this);

	//Camera::onCameraMove += [this]
	//{
	//	updateCameraFacingTriangles();
	//	updateBVH();
	//};
}


bool GraphicalObject::intersect(Ray& ray, bool intersectAll)
{
	//bool hit = false;
	//for (const auto& triangle : cameraFacingTriangles)
	//{
	//	if (!triangle->intersect(ray))continue;
	//	hit = true;
	//}
	//return hit;
	return root != nullptr ? root->intersect(ray, intersectAll) : false;
}
//void GraphicalObject::updateCameraFacingTriangles()
//{
//	cameraFacingTriangles.clear();
//	for (const auto& triangle : triangles)
//	{
//		auto dir = triangle->points[0] - Camera::instance->getPos();
//		if (!triangle->isTwoSided && dot(triangle->normal, dir) >= 0)
//			continue;
//		cameraFacingTriangles.emplace_back(triangle);
//	}
//}
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
void GraphicalObject::setMaterial(Material material)
{
	this->material = std::move(material);
}
void GraphicalObject::updateBVH()
{
	auto intersectables = std::vector<IBoundable*>(triangles.size());
	std::ranges::transform(triangles, intersectables.begin(),
	                       [](const std::shared_ptr<Triangle>& obj) { return (IBoundable*)&*obj; });

	root = intersectables.empty() ? nullptr : BVHNode::buildTree(intersectables, BVHNode::maxTrianglesPerBox);
}

ImportedGraphicalObject::ImportedGraphicalObject(const std::filesystem::path& path) : GraphicalObject(Model(path).triangles), path(path) {}

Square::Square(glm::vec3 pos, glm::quat rot, float side, Material mat) : GraphicalObject(generateTriangles(side), pos, rot, std::move(mat)) {}
std::vector<std::shared_ptr<Triangle>> Square::generateTriangles(float side)
{
	auto p1 = glm::vec3(-side / 2, 0, -side / 2);
	auto p2 = glm::vec3(-side / 2, 0, side / 2);
	auto p3 = glm::vec3(side / 2, 0, side / 2);
	auto p4 = glm::vec3(side / 2, 0, -side / 2);

	std::vector<std::shared_ptr<Triangle>> triangles;
	//    std::make_shared<Triangle>()
	//    triangles.emplace_back(std::make_shared<Triangle>(this, {p1,{0,0}}))
	//    Triangle(this, {p1,{0,0}}, {p2,{0,1}}, {p3,{1,0}});
	Vertex vertex1{p1, {0, 0}};
	Vertex vertex2{p2, {1, 0}};
	Vertex vertex3{p3, {1, 1}};
	Vertex vertex4{p4, {0, 1}};

	triangles.emplace_back(std::make_shared<Triangle>(this, vertex1, vertex2, vertex3));
	triangles.emplace_back(std::make_shared<Triangle>(this, vertex1, vertex3, vertex4));
	return triangles;
}

Cube::Cube(glm::vec3 pos, glm::quat rot, float side) : GraphicalObject(generateTriangles(), pos, rot), side(side) {}

std::vector<std::shared_ptr<Triangle>> Cube::generateTriangles()
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
	//	triangles.emplace_back(std::make_shared<Triangle>(this, p1, p3, p2));
	//	triangles.emplace_back(std::make_shared<Triangle>(this, p1, p4, p3));
	//	triangles.emplace_back(std::make_shared<Triangle>(this, p5, p6, p7));
	//	triangles.emplace_back(std::make_shared<Triangle>(this, p5, p7, p8));
	//
	//	triangles.emplace_back(std::make_shared<Triangle>(this, p1, p2, p6));
	//	triangles.emplace_back(std::make_shared<Triangle>(this, p1, p6, p5));
	//	triangles.emplace_back(std::make_shared<Triangle>(this, p4, p7, p3));
	//	triangles.emplace_back(std::make_shared<Triangle>(this, p4, p8, p7));
	//
	//	triangles.emplace_back(std::make_shared<Triangle>(this, p2, p3, p7));
	//	triangles.emplace_back(std::make_shared<Triangle>(this, p2, p7, p6));
	//	triangles.emplace_back(std::make_shared<Triangle>(this, p1, p8, p4));
	//	triangles.emplace_back(std::make_shared<Triangle>(this, p1, p5, p8));
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
			// transformation to uv coordinates. cyllindric projection.
			auto n = ray.surfaceNormal;
			float u = atan2(-n.x, n.y) / (2.0f * PI) + 0.5f;
			float v = -n.z * 0.5f + 0.5f;
			ray.color = material.getColor(u, v);
			ray.closestMat = &material;

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
			ray.color = material.color;
			ray.interPoint = ray.pos + t * ray.dir;
			ray.surfaceNormal = normal;
			ray.closestMat = &material;

			return true;
		}
	}
	return false;
}

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
	j["type"] = "GraphicalObject";
	return j;
}

nlohmann::basic_json<> Cube::toJson()
{
	auto j = GraphicalObject::toJson();
	j["side"] = side;
	j["type"] = "Cube";
	return j;
}

nlohmann::basic_json<> Sphere::toJson()
{
	auto j = GraphicalObject::toJson();
	j["radius"] = radius;
	j["type"] = "Sphere";
	return j;
}

nlohmann::basic_json<> Plane::toJson()
{
	auto j = GraphicalObject::toJson();
	j["normal"][0] = normal[0];
	j["normal"][1] = normal[1];
	j["normal"][2] = normal[2];
	j["type"] = "Plane";
	return j;
}

nlohmann::basic_json<> ImportedGraphicalObject::toJson()
{
	auto j = GraphicalObject::toJson();
	j["importPath"] = path;
	j["type"] = "ImportedGraphicalObject";
	return j;
}
