#pragma once
#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "Color.h"
#include "cmath"
#include "glm/gtx/string_cast.hpp"
#include "glm/vec3.hpp"
#include <cfloat>
#include <ostream>

struct Ray
{
	glm::vec3 pos, dir;
	float closestT;
	float reflection;
	glm::vec3 surfaceNormal;
	Color color;
	glm::vec3 interPoint;
	float maxDist;


	Ray(glm::vec3 pos, glm::vec3 dir, float maxDist = FLT_MAX) : pos{pos}, dir{normalize(dir)}, closestT(FLT_MAX),
	                                                             surfaceNormal(), color(Color::gray()), interPoint(),
	                                                             maxDist(maxDist) {}
	Ray() = default;
	~Ray() = default;

	bool hit() const
	{
		return surfaceNormal != glm::vec3();
	}
};

inline std::ostream& operator<<(std::ostream& os, const Ray& r)
{
	os << "Ray(pos: " << to_string(r.pos) << ", dir: " << to_string(r.dir) << ")";
	return os;
}
#endif // RAYTRACER_RAY_H