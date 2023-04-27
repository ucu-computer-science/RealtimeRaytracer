//#pragma once

#include <vector>

#include "Triangle.h"

class Model
{
	void parseObject();

public:
	std::vector<std::shared_ptr<Triangle>> triangles;
	std::vector<glm::vec3> vertices;
	std::filesystem::path path;

	explicit Model(const std::filesystem::path& path);

};