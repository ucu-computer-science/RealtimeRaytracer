#include <cmath>
#include "Ray.h"
#include "Triangle.h"
#include "glmExtension.h"
#include "iostream"
//#define CROSS_DOT_METHOD
#define BALDWIN_METHOD
//#define DET_METHOD
//#define MOLLER_TRUMBORE_METHOD
float Ray::getT(const Triangle* triangle) const
{
	return (triangle->getD() - dot(triangle->getNorm(), pos)) / dot(triangle->getNorm(), dir);
}

bool Ray::intersect(const Triangle* triangle)
{

#ifdef CROSS_DOT_METHOD

	float t = getT(triangle);

	if (std::isnan(t) || t <= 0 || t >= closestT)
		return false;
	auto P = pos + t * dir;
	//const auto edge0 = triangle->P2() - triangle->P1();
	if (const auto C0 = P - triangle->P1();
		dot(triangle->getNorm(), cross(triangle->edge1, C0)) <= 0)
		return false;

	//const auto edge1 = triangle->P3() - triangle->P2();
	if (const auto C1 = P - triangle->P2();
		dot(triangle->getNorm(), cross(triangle->edge2, C1)) <= 0)
		return false;

	//const auto edge2 = triangle->P1() - triangle->P3();
	if (const auto C2 = P - triangle->P3();
		dot(triangle->getNorm(), cross(triangle->edge3, C2)) <= 0)
		return false;

	closestT = t;
	closestTriangle = triangle;
	interPoint = &P;
	return true;
#else //CROSS_DOT_METHOD
#ifdef DET_METHOD
	float t = getT(triangle);

	if (std::isnan(t) || t <= 0 || t >= closestT)
		return false;
	auto P = pos + t * dir;
	if (triangle->detSign > 0)
	{
		if (triangle->optimizedDet(P, 1) < 0)
			return false;
		if (triangle->optimizedDet(P, 2) < 0)
			return false;
		if (triangle->optimizedDet(P, 3) < 0)
			return false;
	}
	else if (triangle->detSign < 0)
	{
		if (triangle->optimizedDet(P, 1) > 0)
			return false;
		if (triangle->optimizedDet(P, 2) > 0)
			return false;
		if (triangle->optimizedDet(P, 3) > 0)
			return false;
	}
	else
	{
		return false;
	}

	closestT = t;
	closestTriangle = triangle;
	interPoint = P;
	return true;

#else
#ifdef MOLLER_TRUMBORE_METHOD
	const float EPSILON = 0.0000001f;

	glm::vec3 h = cross(dir, (triangle->edge2));
	float a = dot(triangle->edge1, h);
	if (a > -EPSILON && a < EPSILON)
		return false;    // This ray is parallel to this triangle.
	float f = 1.0f / a;
	glm::vec3 s = pos - triangle->P1();
	float u = f * dot(s, h);
	if (u < 0.0f || u > 1.0f)
		return false;
	glm::vec3 q = cross(s, triangle->edge1);
	float v = f * dot(dir, q);
	if (v < 0.0f || u + v > 1.0f)
		return false;
	// At this stage we can compute t to find out where the intersection point is on the line.
	float t = f * dot(triangle->edge2, q);
	if (t > EPSILON && closestT > t) // ray intersection
	{
		//outIntersectionPoint = pos + dir * t;
		closestT = t;
		closestTriangle = triangle;
		interPoint = pos + dir * t;
		return true;
	}
	return true;
	//else // This means that there is a line intersection but not a ray intersection.
		//return false;
  #else
   #ifdef BALDWIN_METHOD
	const float dz = dot(triangle->row3, dir);

	if (dz == 0.0f)
		return false;

	const float oz = dot(triangle->row3, pos) + triangle->valRow3; 


	const float t = -oz / dz;

	if (t < 0 || closestT < t|| t > 100000)
		return false;

	const glm::vec3 hit = pos + dir * t;
	// Point where ray hits triangle plane, in world coordinates

	const float b1 = dot(triangle->row1, hit) + triangle->valRow1;

	const float b2 = dot(triangle->row2, hit) + triangle->valRow2;

	if (b1 < 0.0f || b2 < 0.0f || b1 + b2 > 1.0f)
		return false;

	closestT = t;
	closestTriangle = triangle;
	interPoint = hit;
	return true;
#endif

#endif // MOLLER_TRUMBORE_METHOD

#endif // DET_METHOD
#endif // CROSS_DOT_METHOD

}
