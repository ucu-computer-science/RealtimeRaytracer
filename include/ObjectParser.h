#pragma once

#include <string>
#include <vector>

#include "Triangle.h"

class Model
{
public:
	explicit Model(std::string path);
	std::vector<Triangle*> triangles;
	std::vector<glm::vec3> vertices;
	std::string path;

	void parseObject();
};
