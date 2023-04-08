#include "Light.h"

#include <iostream>

#include "Raycast.h"

Light::Light(glm::vec3 pos, Color wholeColor, float distance, float wholeIntensity, glm::vec3 size,
             glm::vec3 pointSize) : Object(pos, {{0, 0, 0}}), distance(distance),
                                    size(size), pointSize(pointSize)
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
        intensity = wholeIntensity/points.size();
        color = (intensity*wholeColor);
}

Color Light::getLightAtPoint(glm::vec3 p, glm::vec3 norm)
{
	Color v{0, 0, 0};
	for (const auto light : lights)
	{
		for (const auto &lightPoint : light->points)
		{
			auto dist = length(lightPoint - p);
                        // why should we reduce distance to avoid intersection with itself
                        //
                        if (dist > light->distance) {
                          continue ;
                        }
                        auto dir = normalize(lightPoint - p);
			if (Raycast::castShadowRays({/*light->getPos()*/ lightPoint, -dir,dist }))
				continue;
                        //clamp is not needed for the lower bound
			auto distanceImpact = std::min(1 - (dist / light->distance), 1.f);
			auto lightFacingAtPoint = std::max(dot(dir, norm), 0.f);
                        // moved intensity calculations into constructor
			v += distanceImpact * light->color * lightFacingAtPoint;
		}
	}
        //for some reason to have non-negative shadows i have to add 1 to lightCount
        // is fixed only for two lightsourcess
        // and still i get peaches
	return v;
}