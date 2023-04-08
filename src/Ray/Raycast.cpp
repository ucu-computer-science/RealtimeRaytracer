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
	for (int i = 0; i < 5; ++i)
	{
		for (const auto obj : Scene::graphicalObjects)
		{
			obj->intersect(ray, hit);
		}
		if (!ray.hit())
			break;

		hit = true;
                // this is important. if we dont add this vector ,the ray from the point will sometimes hit the object it just hit
                // by adding this we get our point slightly above the surface, thus there are slightly more directions to hit
                ray.interPoint+=ray.surfaceNormal*.001f;
		v += colorImpact * (1 - ray.reflection) * ray.color * Light::getLightAtPoint(ray.interPoint, ray.surfaceNormal);
		colorImpact *= ray.reflection;
		if (colorImpact <= 1e-6)
			break;
//TODO specular diffuse random rays
		auto dir = ray.dir - (2 * dot(ray.dir, ray.surfaceNormal) * ray.surfaceNormal);//*/*360.f/360.f);*/// ((float)(rand()%1)/1));
		ray = Ray(ray.interPoint, dir);
	}
	v += colorImpact * Camera::instance->bgColor;
	return hit ? v : Camera::instance->bgColor;
}

bool Raycast::castShadowRays(Ray ray)
{
	for (const auto obj : Scene::graphicalObjects)
	{
		obj->intersect(ray, true);
		if (ray.hit())
			return true;
	}
	return false;
}