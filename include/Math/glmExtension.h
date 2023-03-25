#pragma once

#include "glm/vec3.hpp"

inline float det(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3)
{
	const float x = v2[1] * v3[2] - v3[1] * v2[2];
	const float y = v2[0] * v3[2] - v3[0] * v2[2];
	const float z = v2[0] * v3[1] - v3[0] * v2[1];

	return v1[0] * x - v1[1] * y + v1[2] * z;
}
