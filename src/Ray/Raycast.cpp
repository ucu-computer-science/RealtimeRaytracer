#include "Raycast.h"

#include <iostream>

#include "Scene.h"
#include "Ray.h"
#include "GraphicalObject.h"
#include "Light.h"

Color Raycast::castRay(Ray ray, int bounce)
{
	for (const auto obj : Scene::graphicalObjects)
	{
		obj->intersect(ray);
	}
	ray.color *= Light::getLightAtPoint(ray.interPoint, ray.normal);

	return ray.color;
}

bool Raycast::intersectsObj(Ray ray)
{
	for (const auto obj : Scene::graphicalObjects)
	{
		obj->intersect(ray, true);
		if (ray.normal != glm::vec3())
			return true;
	}
	return false;
}
