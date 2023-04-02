#include "Light.h"

#include "Raycast.h"

Light::Light(glm::vec3 pos, Color color, float distance, float intensity) : Object(pos, {{0, 0, 0}}), color(color),
                                                                            distance(distance), intensity(intensity)
{
	lights.emplace_back(this);
}

Color Light::getLightAtPoint(glm::vec3 p, glm::vec3 norm)
{
	Color v{0, 0, 0};
	bool hit = false;
	for (auto light : lights)
	{
		auto dir = normalize(light->getPos() - p);
		auto dirInv = p - light->getPos();
		auto dist = length(dirInv);
		if (Raycast::intersectsObj({light->getPos(), dirInv, dist - 0.01f}))
			continue;
		hit = true;

		auto distanceImpact = 1 - glm::clamp(dist / light->distance, 0.0f, 1.0f);
		auto lightFacing = glm::clamp(dot(dir, norm), 0.0f, 1.0f);
		v += distanceImpact * light->intensity * light->color * lightFacing;
	}
	return hit ? v : Color::black();
}
