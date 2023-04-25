#pragma once

#include "Object.h"
#include "glm/vec3.hpp"
#include "Material.h"
#include "ColorTexture.h"
#include <vector>
#include "IIntersectable.h"

class BVHNode;

class AABB;

struct Ray;

class Triangle;

class GraphicalObject : public Object, public IIntersectable {
public:
    Material material;
    ColorTexture texture;

    const std::vector<std::shared_ptr<Triangle>> triangles{};
    std::vector<std::shared_ptr<Triangle>> cameraFacingTriangles{};
    std::shared_ptr<BVHNode> rootBVH = nullptr;

    explicit GraphicalObject(const std::vector<std::shared_ptr<Triangle>> &triangles = {},
                             glm::vec3 pos = {0, 0, 0},
                             glm::quat rot = {1, 0, 0, 0},
                             Material material = {},
                             std::string texturePath = {"./textures/default.png"});

    bool intersect(Ray &ray, bool intersectAll = false) override;

    AABB getBoundingBox() const override;

    glm::vec3 getCenter() const override { return pos; }

    void updateBVH();

    void updateCameraFacingTriangles();

    void setColor(Color color);

    void setReflection(float reflection);

    void setMaterial(Material material);
    void setTexture(const std::string &texturePath);
};

class ImportedGraphicalObject : GraphicalObject {
public:
    std::string importPath;

    ImportedGraphicalObject(const std::string &path);
};

class Square : public GraphicalObject {
public:
    Square(glm::vec3 pos, glm::quat rot, float side, Material mat = Material());

    std::vector<std::shared_ptr<Triangle>> generateTriangles(float side);

    bool includeInBVH() override { return false; }
};

class Cube final : public GraphicalObject {
public:
    std::vector<std::shared_ptr<Triangle>> generateTriangles(float side);

    Cube(glm::vec3 pos, glm::quat rot, float side);
};

class Sphere final : public GraphicalObject {
    float radius;
    float radiusSquared;

public:
    Sphere(glm::vec3 pos, float radius, Color color) : GraphicalObject({}, pos), radius(radius), radiusSquared{radius * radius} {
        material.color = color;
    }

    bool intersect(Ray &ray, bool intersectAll) override;

    AABB getBoundingBox() const override;
};

class Plane final : public GraphicalObject
{
	glm::vec3 normal;

public:
	Plane(glm::vec3 pos, glm::vec3 normal, Color color) : GraphicalObject({}, pos), normal{normalize(normal)}
	{
		material.color = color;
	}

	bool intersect(Ray& ray, bool intersectAll) override;
	bool includeInBVH() override { return false; }
};