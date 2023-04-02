#pragma once

#include <vector>

#include "Color.h"
#include "Object.h"

class Light : Object
{
	inline static std::vector<Light*> lights{};

public:
	Color color;

	explicit Light(glm::vec3 pos, Color color);

	static Color getLightAtPoint(glm::vec3 p, glm::vec3 norm);
};
