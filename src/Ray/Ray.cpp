#include <cmath>
#include "Ray.h"
#include "Triangle.h"
#include "glmExtension.h"

float Ray::getT(const Triangle* triangle) const
{
	return (triangle->getD() - dot(triangle->getNorm(), pos)) / dot(triangle->getNorm(), dir);
}

bool Ray::intersect(const Triangle* triangle)
{

	float t = getT(triangle);

	if (std::isnan(t) || t <= 0 || t >= closestT)
		return false;
	auto P = pos + t * dir;

	auto edge0 = triangle->P2() - triangle->P1();
	auto C0 = P - triangle->P1();
	if (dot(triangle->getNorm(), cross(edge0, C0)) <= 0) return false;


	auto edge1 = triangle->P3() - triangle->P2();
	auto C1 = P - triangle->P2();
	if(dot(triangle->getNorm(), cross(edge1, C1)) <= 0) return false;
	auto edge2 = triangle->P1() - triangle->P3();
	auto C2 = P - triangle->P3();
	if (dot(triangle->getNorm(), cross(edge2, C2)) <= 0) return false;

		closestT = t;
		closestTriangle = triangle;
		interPoint = &P;
		return true;

	
	//if (triangle->detSign > 0)
	//{
	//	if (triangle->optimizedDet(p, 1) < 0)
	//		return false;
	//	if (triangle->optimizedDet(p, 2) < 0)
	//		return false;
	//	if (triangle->optimizedDet(p, 3) < 0)
	//		return false;
	//}
	//else if (triangle->detSign < 0)
	//{
	//	if (triangle->optimizedDet(p, 1) > 0)
	//		return false;
	//	if (triangle->optimizedDet(p, 2) > 0)
	//		return false;
	//	if (triangle->optimizedDet(p, 3) > 0)
	//		return false;
	//}
	//else
	//{
	//	//return false;
	//}

	//closestT = t;
	//closestTriangle = triangle;
	//interPoint = &p;
	return true;
}
