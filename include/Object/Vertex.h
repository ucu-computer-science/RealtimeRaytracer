#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

struct Vertex
{
    glm::vec3 pos;
    glm::vec2 uvPos;
    glm::vec3 normal;

    Vertex(glm::vec3 pos, glm::vec2 uvPos = glm::vec2{}, glm::vec3 normal = glm::vec3{}) : pos(pos), uvPos(uvPos), normal(normal) { }
};