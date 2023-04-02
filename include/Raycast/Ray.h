#pragma once

#include "Color.h"
#include "cmath"
#include "glm/gtx/string_cast.hpp"
#include "glm/vec3.hpp"
#include <cfloat>
#include <ostream>

class Triangle;

class Ray
{
public:
	glm::vec3 pos, dir;
	float closestT;
	glm::vec3 normal;
	Color color;
	glm::vec3 interPoint;
	float maxDist;


	Ray(glm::vec3 pos, glm::vec3 dir, float maxDist = FLT_MAX) : pos{pos}, dir{normalize(dir)}, closestT(FLT_MAX),
	                                                             normal(), color(Color::gray()), interPoint(),
	                                                             maxDist(maxDist) {}
	Ray() = default;
	~Ray() = default;
	float getT(const Triangle* triangle) const;
	bool intersect(const Triangle* triangle);

	//	bool hit() const
	//	{
	//		return closestTriangle != nullptr;
	//	}
};

inline std::ostream& operator<<(std::ostream& os, const Ray& r)
{
	os << "Ray(pos: " << to_string(r.pos) << ", dir: " << to_string(r.dir) << ")";
	return os;
}
