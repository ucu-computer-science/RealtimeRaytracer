#pragma once

#include "glm/vec3.hpp"

struct Ray;

class AABB
{
	glm::vec3 min, max;

public:
	AABB(): min(), max() { }
	AABB(glm::vec3 min, glm::vec3 max): min(min), max(max) { }

	bool overlaps(const Ray* ray, float tMin, float tMax) const
	{
		for (int i = 0; i < 3; i++)
		{
			auto invD = 1.0f / ray->dir[i];
			auto t0 = (min[i] - ray->pos[i]) * invD;
			auto t1 = (max[i] - ray->pos[i]) * invD;
			if (invD < 0.0f)
				std::swap(t0, t1);

			tMin = t0 > tMin ? t0 : tMin;
			tMax = t1 < tMax ? t1 : tMax;
			if (tMax <= tMin)
				return false;
		}
		return true;
	}
};
