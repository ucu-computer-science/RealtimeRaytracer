#include "Raycast.h"

#include "Camera.h"
#include "Scene.h"
#include "Ray.h"
#include "GraphicalObject.h"
#include "Light.h"

Color Raycast::castRay(Ray ray, int bounce)
{
	Color v{0, 0, 0};

	bool hit = false;
	float colorImpact = 1;
	for (int i = 0; i < 3; ++i)
	{
		for (const auto obj : Scene::graphicalObjects)
		{
			obj->intersect(ray, hit);
		}
		if (!ray.hit())
			break;

		hit = true;
		v += colorImpact * (1 - ray.reflection) * ray.color * Light::getLightAtPoint(ray.interPoint, ray.surfaceNormal);
		colorImpact *= ray.reflection;
		if (colorImpact == 0.0f)
			break;

		auto dir = ray.dir - (2 * dot(ray.dir, ray.surfaceNormal) * ray.surfaceNormal);
		ray = Ray(ray.interPoint, dir);
	}
	v += colorImpact * Camera::instance->bgColor;
	return hit ? v : Camera::instance->bgColor;
}

bool Raycast::intersectsObj(Ray ray)
{
	for (const auto obj : Scene::graphicalObjects)
	{
		obj->intersect(ray, true);
		if (ray.hit())
			return true;
	}
	return false;
}
