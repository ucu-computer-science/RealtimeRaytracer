#include "Light.h"

#include "Raycast.h"

Light::Light(glm::vec3 pos, Color color) : Object(pos, {{0, 0, 0}})
{
	this->color = color;
	lights.emplace_back(this);
}

Color Light::getLightAtPoint(glm::vec3 p, glm::vec3 norm)
{
	Color v{1, 1, 1};
	bool hit = false;
	for (auto light : lights)
	{
		auto dir = normalize(light->getPos() - p);
		auto dirInv = p - light->getPos();
		if (Raycast::intersectsObj({light->getPos(), dirInv, length(dirInv) - 0.001f}))
			continue;

		hit = true;
		auto v_ = light->color * glm::clamp(dot(dir, norm), 0.0f, 1.0f);
		v *= v_;
	}
	return hit ? v : Color::black();
}