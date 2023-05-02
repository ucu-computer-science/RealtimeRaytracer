#pragma once

#include "glm/gtx/string_cast.hpp"
#include "glm/vec3.hpp"
#include <cfloat>
#include <ostream>

class Triangle;
class GraphicalObject;
class Material;

struct Ray
{
	glm::vec3 pos, dir;
	float closestT;
	Material* closestMat;
	glm::vec3 surfaceNormal;
	glm::vec3 interPoint;
	float maxDist;
    Color color;

	Ray(glm::vec3 pos, glm::vec3 dir, float maxDist = FLT_MAX) : pos{pos}, dir{normalize(dir)}, closestT(FLT_MAX),
	                                                             closestMat(nullptr),
	                                                             surfaceNormal(), interPoint(), maxDist(maxDist){}


	bool hit() const { return surfaceNormal != glm::vec3(); }
};

inline std::ostream& operator<<(std::ostream& os, const Ray& r)
{
	os << "Ray(pos: " << to_string(r.pos) << ", dir: " << to_string(r.dir) << ")";
	return os;
}