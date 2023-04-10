#pragma once
#ifndef RAYTRACER_RAYCAST_H
#define RAYTRACER_RAYCAST_H
#include <vector>

#include "Ray.h"

class Triangle;
struct Ray;

class Raycast
{
public:
	static Color castRay(Ray ray, int bounce = 1);
	static bool castShadowRays(Ray ray);
};
#endif // RAYTRACER_RAYCAST_H