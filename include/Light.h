#pragma once

#include <vector>

#include "Color.h"
#include "Object.h"

class Light : Object
{
	inline static std::vector<Light*> lights{};

public:
	Color color;
	float distance;
	float intensity;
	glm::vec3 size;
	glm::vec3 pointSize;
	std::vector<glm::vec3> points;

	explicit Light(glm::vec3 pos, Color color, float distance, float intensity, glm::vec3 size, glm::vec3 pointSize);


	static Color getLightAtPoint(glm::vec3 p, glm::vec3 norm);
};
