#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

struct Vertex
{
	glm::vec3 pos;
	glm::vec2 uvPos;

	Vertex(glm::vec3 pos, glm::vec2 uvPos): pos(pos), uvPos(uvPos) { }
};
