#pragma once

#include "glm/vec3.hpp"

constexpr float PI = 3.14159265358979323846f;
constexpr float DEG_TO_RAD = (1 / (180 / PI));
constexpr float RAD_TO_DEG = (180 / PI);

inline float det(const glm::vec3& v1, const glm::vec3& v2,
                 const glm::vec3& v3)
{
	const float x = v2[1] * v3[2] - v3[1] * v2[2];
	const float y = v2[0] * v3[2] - v3[0] * v2[2];
	const float z = v2[0] * v3[1] - v3[0] * v2[1];

	return v1[0] * x - v1[1] * y + v1[2] * z;
}

namespace vec3
{
	static glm::vec3 one() { return {1, 1, 1}; }
	static glm::vec3 forward() { return {0, 1, 0}; }
	static glm::vec3 backward() { return {0, -1, 0}; }
	static glm::vec3 up() { return {0, 0, 1}; }
	static glm::vec3 down() { return {0, 0, -1}; }
	static glm::vec3 left() { return {-1, 0, 0}; }
	static glm::vec3 right() { return {1, 0, 0}; }
} // namespace vec3

static bool solveQuadratic(float a, float b, float c, float& x0, float& x1)
{
	float discr = b * b - 4 * a * c;
	if (discr < 0)
		return false;
	if (discr == 0)
		x0 = x1 = -0.5f * b / a;
	else
	{
		float q = (b > 0) ? -0.5f * (b + sqrt(discr)) : -0.5f * (b - sqrt(discr));
		x0 = q / a;
		x1 = c / q;
	}
	if (x0 > x1)
		std::swap(x0, x1);
	return true;
}

inline float random(float min, float max)
{
	return min + static_cast<float>(rand()) / (RAND_MAX / (max - min));
}

inline float getLengthSquared(glm::vec3 v)
{
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

inline glm::vec3 randomVectorInCircle(float radius)
{
	while (true)
	{
		auto p = glm::vec3(random(-radius, radius), random(-radius, radius), 0);
		if (getLengthSquared(p) >= 1) continue;
		return p;
	}
}

inline glm::vec3 randomVectorInRectangle(float sizeX, float sizeY)
{
	return {random(-sizeX, sizeX), random(-sizeY, sizeY), 0};
}

inline glm::vec3 randomVectorInSphere(float radius)
{
	while (true)
	{
		auto p = glm::vec3(random(-radius, radius), random(-radius, radius), random(-radius, radius));
		if (getLengthSquared(p) >= 1) continue;
		return p;
	}
}

inline glm::vec3 randomDirection()
{
	return normalize(randomVectorInSphere(1));
}
