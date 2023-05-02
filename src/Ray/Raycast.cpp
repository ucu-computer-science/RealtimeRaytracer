#include "Raycast.h"

#include "Camera.h"
#include "GraphicalObject.h"
#include "Light.h"
#include "Ray.h"
#include "BoundingBoxes.h"


Color Raycast::castRay(Ray ray, int bounce)
{
	Color color{};
	bool hit = false;
	float colorImpact = 1;
	for (int i = 0; i < bounce; ++i)
	{
		//for (const auto& obj : Scene::graphicalObjects)
		//{
		//	if (obj->includeInBVH()) continue;
		//	obj->intersect(ray);
		//}
		BVHBuilder::nodes[0]->intersect(ray);
		if (!ray.hit())
			break;
		hit = true;

		ray.interPoint += ray.surfaceNormal * ray.closestT / 100.f;

		auto mat = ray.closestMat;
		if (mat->lit)
		{
			auto [diffuse, specular] = getIlluminationAtPoint(ray);
			color += colorImpact * (1 - mat->reflection) * ray.color * diffuse * mat->diffuseCoeff;
			color += specular * mat->specularCoeff;
		}
		else
			color += colorImpact * (1 - mat->reflection) * ray.color;

		colorImpact *= mat->reflection;
		if (colorImpact <= 1e-6f)
			break;

		auto dir = ray.dir - 2 * dot(ray.dir, ray.surfaceNormal) * ray.surfaceNormal;
		ray = Ray(ray.interPoint, dir);
	}

	color += colorImpact * Camera::instance->bgColor;
	return hit ? color : Camera::instance->bgColor;
}

bool Raycast::castShadowRays(Ray ray)
{
	//for (const auto& obj : Scene::graphicalObjects)
	//{
	//	if (obj->includeInBVH())continue;
	//	if (obj->intersect(ray))
	//		return true;
	//}

	BVHBuilder::nodes[0]->intersect(ray);
	return ray.hit();
}
