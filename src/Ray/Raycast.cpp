#include "Raycast.h"

#include "Camera.h"
#include "GraphicalObject.h"
#include "Light.h"
#include "Ray.h"
#include "BoundingBox.h"
#include "Scene.h"


Color Raycast::castRay(Ray ray, int bounce)
{
	Color color{0, 0, 0};
	Color specular{};

	bool hit = false;
	float colorImpact = 1;
	for (int i = 0; i < bounce; ++i)
	{
		for (const auto& obj : Scene::graphicalObjects)
		{
			if (obj->includeInBVH()) continue;
			obj->intersect(ray);
		}
		BVHNode::root->intersect(ray);
		if (!ray.hit())
			break;
		hit = true;

		ray.interPoint += ray.surfaceNormal * .001f;
		auto hitInfo = getIlluminationAtPoint(ray);
		color += colorImpact * (1 - ray.material->reflection) * ray.color * (hitInfo.first) * ray.material->
			diffuse_coeff;
		color += hitInfo.second * ray.material->specular_coeff;
		colorImpact *= ray.material->reflection;
		if (colorImpact <= 1e-6f)
			break;

		auto dir = ray.dir - (2 * dot(ray.dir, ray.surfaceNormal) * ray.surfaceNormal);
		ray = Ray(ray.interPoint, dir);
	}
	color += colorImpact * Camera::instance->bgColor + specular;
	return hit ? color : Camera::instance->bgColor;
}

bool Raycast::castShadowRays(Ray ray)
{
	for (const auto& obj : Scene::graphicalObjects)
	{
		if (obj->includeInBVH())continue;
		if (obj->intersect(ray))
			return true;
	}

	BVHNode::root->intersect(ray);
	return ray.hit();
}
