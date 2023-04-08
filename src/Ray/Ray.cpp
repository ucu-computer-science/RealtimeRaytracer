#include "Ray.h"
#include "Triangle.h"
#include "immintrin.h"
float Ray::getT(const Triangle* triangle) const
{
	return (triangle->planeEq.d - dot(triangle->planeEq.norm, pos)) / dot(triangle->planeEq.norm, dir);
}

bool Ray::intersect(const Triangle* triangle)
{
	//#ifdef CROSS_DOT_METHOD
	//
	//	float t = getT(triangle);
	//
	//	if (std::isnan(t) || t <= 0 || t >= closestT)
	//		return false;
	//	auto P = pos + t * dir;
	//	//const auto edge0 = triangle->P2() - triangle->P1();
	//	if (const auto C0 = P - triangle->P1();
	//		dot(triangle->getNorm(), cross(triangle->edge1, C0)) <= 0)
	//		return false;
	//
	//	//const auto edge1 = triangle->P3() - triangle->P2();
	//	if (const auto C1 = P - triangle->P2();
	//		dot(triangle->getNorm(), cross(triangle->edge2, C1)) <= 0)
	//		return false;
	//
	//	//const auto edge2 = triangle->P1() - triangle->P3();
	//	if (const auto C2 = P - triangle->P3();
	//		dot(triangle->getNorm(), cross(triangle->edge3, C2)) <= 0)
	//		return false;
	//
	//	closestT = t;
	//	closestTriangle = triangle;
	//	interPoint = &P;
	//	return true;
	//#else //CROSS_DOT_METHOD
	//#ifdef DET_METHOD
	//	float t = getT(triangle);
	//
	//	if (std::isnan(t) || t <= 0 || t >= closestT)
	//		return false;
	//	auto P = pos + t * dir;
	//	if (triangle->detSign > 0)
	//	{
	//		if (triangle->optimizedDet(P, 1) < 0)
	//			return false;
	//		if (triangle->optimizedDet(P, 2) < 0)
	//			return false;
	//		if (triangle->optimizedDet(P, 3) < 0)
	//			return false;
	//	}
	//	else if (triangle->detSign < 0)
	//	{
	//		if (triangle->optimizedDet(P, 1) > 0)
	//			return false;
	//		if (triangle->optimizedDet(P, 2) > 0)
	//			return false;
	//		if (triangle->optimizedDet(P, 3) > 0)
	//			return false;
	//	}
	//	else
	//	{
	//		return false;
	//	}
	//
	//	closestT = t;
	//	closestTriangle = triangle;
	//	interPoint = P;
	//	return true;
	//
	//#else
	//#ifdef MOLLER_TRUMBORE_METHOD
	//	const float EPSILON = 0.0000001f;
	//
	//	glm::vec3 h = cross(dir, (triangle->edge2));
	//	float a = dot(triangle->edge1, h);
	//	if (a > -EPSILON && a < EPSILON)
	//		return false;    // This ray is parallel to this triangle.
	//	float f = 1.0f / a;
	//	glm::vec3 s = pos - triangle->P1();
	//	float u = f * dot(s, h);
	//	if (u < 0.0f || u > 1.0f)
	//		return false;
	//	glm::vec3 q = cross(s, triangle->edge1);
	//	float v = f * dot(dir, q);
	//	if (v < 0.0f || u + v > 1.0f)
	//		return false;
	//	// At this stage we can compute t to find out where the intersection point is on the line.
	//	float t = f * dot(triangle->edge2, q);
	//	if (t > EPSILON && closestT > t) // ray intersection
	//	{
	//		//outIntersectionPoint = pos + dir * t;
	//		closestT = t;
	//		closestTriangle = triangle;
	//		interPoint = pos + dir * t;
	//		return true;
	//	}
	//	return true;
	//	//else // This means that there is a line intersection but not a ray intersection.
	//		//return false;
	//  #else
	//   #ifdef BALDWIN_METHOD

	const float dz = dot(triangle->row3, dir);
//        const float dz = triangle->row3[0]*dir[0] + triangle->row3[1]*dir[1] + triangle->row3[2]*dir[2];
//        const auto& tr3 = reinterpret_cast<const __m128&>(triangle->row3);
//        const auto& d = reinterpret_cast<const __m128&>(dir);
//        __m128 mul =  _mm_mul_ps(tr3, d);
//        const auto dz = mul.m128_f32[1] + mul.m128_f32[2] +  mul.m128_f32[3];

	if (dz == 0.0f)
		return false;

	const float oz = dot(triangle->row3, pos) + triangle->valRow3;
//        const float oz = triangle->row3[0]*pos[0] + triangle->row3[1]*pos[1] + triangle->row3[2]*pos[2] + triangle->valRow3;
	const float t = -oz / dz;

	if (t < 0 || closestT < t || t >= maxDist)
		return false;

	const auto hit = pos + dir * t;

	const float b1 = dot(triangle->row1, hit) + triangle->valRow1;
//        const float b1 = triangle->row1[0]*hit[0] + triangle->row1[1]*hit[1] + triangle->row1[2]*hit[2] + triangle->valRow1;

	if (b1 < 0.0f || b1 > 1.0f)
		return false;
	const float b2 = dot(triangle->row2, hit) + triangle->valRow2;
//        const float b2 = triangle->row2[0]*hit[0] + triangle->row2[1]*hit[1] + triangle->row2[2]*hit[2] + triangle->valRow2;

	if (b2 < 0.0f || b1 + b2 > 1.0f)
		return false;

	closestT = t;
	color = triangle->color;
	surfaceNormal = triangle->planeEq.norm;
	interPoint = hit;
	reflection = triangle->reflection;
	return true;
}