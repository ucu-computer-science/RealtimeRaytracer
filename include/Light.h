#pragma once

#include <vector>
#include "Object.h"

class Light : Object
{
	inline static std::vector<Light*> lights{};

public:
	explicit Light(glm::vec3 pos);

	static float getLightAtPoint(glm::vec3 p, glm::vec3 norm);
};
