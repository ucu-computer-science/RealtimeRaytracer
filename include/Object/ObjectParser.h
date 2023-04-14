//
// Created by Віталій Петричко on 14.04.2023.
//
#include "iostream"
#include <fstream>
#include "GraphicalObject.h"
#include <string>
#include <sstream>
#include "Triangle.h"
#ifndef RAYTRACER_OBJECT_PARSER_H
#define RAYTRACER_OBJECT_PARSER_H

class Model{
public:
    explicit Model(std::string path);
    std::vector<Triangle*> triangles;
    std::vector<glm::vec3> vertices;
    std::string path;

    void ParseObject();
};

#endif //RAYTRACER_OBJECT_PARSER_H
