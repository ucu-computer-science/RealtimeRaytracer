#include "Light.h"

#include "Raycast.h"

Light::Light(glm::vec3 pos) : Object(pos, {{0, 0, 0}})
{
	lights.emplace_back(this);
}

float Light::getLightAtPoint(glm::vec3 p, glm::vec3 norm)
{
	float v = 0;
	for (auto light : lights)
	{
		auto dir = normalize(light->getPos() - p);
		auto dirInv = p - light->getPos();
		if (Raycast::intersectsObj({light->getPos(), normalize(dirInv), length(dirInv) - 0.001f}))
			continue;

		auto v_ = glm::clamp(dot(dir, norm), 0.0f, 1.0f);
		v = std::max(v, v_);
	}
	return v;
}
