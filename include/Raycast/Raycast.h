#pragma once

#include "Ray.h"

class Triangle;
struct Ray;

class Raycast {
public:
  static Color castRay(Ray ray, int bounce = 1);
  static bool castShadowRays(Ray ray);
};
