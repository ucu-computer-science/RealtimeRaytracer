#include "Raycast.h"
#include "Scene.h"
#include "Ray.h"
#include "GraphicalObject.h"

Raycast Raycast::castRay(Ray& ray)
{
	for (const auto obj : Scene::graphicalObjects)
	{
		for (const auto triangle : obj->triangles)
		{
			ray.intersect(*triangle);
		}
	}
	return Raycast(ray);
}
