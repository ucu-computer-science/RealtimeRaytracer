#pragma once
#ifndef RAYTRACER_GRAPHICALOBJECT_H
#define RAYTRACER_GRAPHICALOBJECT_H

#include "Color.h"
#include "Object.h"
#include "glm/vec3.hpp"
#include "Material.h"
#include "ColorTexture.h"
#include <vector>

struct Ray;

class Triangle;

class GraphicalObject : public Object {
public:

    Material material;
    ColorTexture texture;

    std::vector<Triangle *> triangles{};
    std::vector<Triangle *> cameraFacingTriangles{};

    explicit GraphicalObject(glm::vec3 pos, glm::quat rot = {1, 0, 0, 0}, Material material = {}, std::string texturePath = {
            "./default.png"});

    void setColor(Color color);

    void setReflection(float reflection);

    void setMaterial(Material material);
    void setTexture(const std::string &texturePath);


    virtual void findIntersectionWith(Ray &ray, bool intersectAll = false);

    void updateCameraFacingTriangles();
};

class Square : public GraphicalObject {
public:
    Square(glm::vec3 pos, glm::quat rot, float side);

    Square(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
};

class Cube final : public GraphicalObject {
public:
    Cube(glm::vec3 pos, glm::quat rot, float side);
};

class Sphere final : public GraphicalObject {
    float radiusSquared;
public:
    Sphere(glm::vec3 pos, float radius, Color color)
            : GraphicalObject(pos), radiusSquared{radius * radius} {}

    void findIntersectionWith(Ray &ray, bool intersectAll) override;
};

class Plane final : public GraphicalObject {
    glm::vec3 normal;

public:
    Plane(glm::vec3 pos, glm::vec3 normal, Color color)
            : GraphicalObject(pos), normal{normalize(normal)} {}

    void findIntersectionWith(Ray &ray, bool intersectAll) override;
};

class SquarePyramid : public GraphicalObject {
public:
    SquarePyramid(glm::vec3 pos, glm::quat rot, float side, float height);
};

#endif // RAYTRACER_GRAPHICALOBJECT_H