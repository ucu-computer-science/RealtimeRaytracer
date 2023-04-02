#include "Light.h"

#include <iostream>

#include "Raycast.h"

Light::Light(glm::vec3 pos, Color color, float distance, float intensity, glm::vec3 size,
             glm::vec3 pointSize) : Object(pos, {{0, 0, 0}}), color(color), distance(distance),
                                    intensity(intensity), size(size), pointSize(pointSize)
{
	lights.emplace_back(this);

	float dx = size.x / pointSize.x;
	float dy = size.y / pointSize.y;
	float dz = size.z / pointSize.z;
	for (int x = 0; x < pointSize.x; ++x)
	{
		for (int y = 0; y < pointSize.y; ++y)
		{
			for (int z = 0; z < pointSize.z; ++z)
			{
				auto point = pos - size / 2.0f + glm::vec3(x * dx, y * dy, z * dz);
				points.emplace_back(point);
			}
		}
	}
}

Color Light::getLightAtPoint(glm::vec3 p, glm::vec3 norm)
{
	Color v{0, 0, 0};
	int lightCount = 0;
	for (auto light : lights)
	{
		bool hit = false;
		for (glm::vec3 point : light->points)
		{
			auto dir = normalize(point - p);
			auto dirInv = p - point;
			auto dist = length(dirInv);
			if (Raycast::intersectsObj({/*light->getPos()*/ point, dirInv, dist - 0.01f}))
				continue;
			hit = true;

			auto distanceImpact = 1 - glm::clamp(dist / light->distance, 0.0f, 1.0f);
			auto lightFacing = glm::clamp(dot(dir, norm), 0.0f, 1.0f);
			v += distanceImpact * (light->intensity / (float)light->points.size()) * light->color * lightFacing;
		}
		if (hit)
			lightCount++;
	}
	return lightCount != 0 ? v * (1 / (float)lightCount) : Color::black();
}
