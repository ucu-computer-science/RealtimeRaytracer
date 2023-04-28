//#pragma once

#include <vector>

#include "Triangle.h"

class Model
{
	void parseObject(const std::filesystem::path& path);

public:
	std::vector<std::shared_ptr<Triangle>> triangles;
	std::vector<glm::vec3> vertices;

	explicit Model(const std::filesystem::path& path);

};