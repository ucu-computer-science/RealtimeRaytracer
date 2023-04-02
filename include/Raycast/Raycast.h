#pragma once

#include <vector>

#include "Ray.h"

class Triangle;
class Ray;

class Raycast
{
public:
	static Color castRay(Ray ray, int bounce = 1);
	static bool intersectsObj(Ray ray);
};
