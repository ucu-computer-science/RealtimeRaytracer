#include "Raycast.h"
#include "Scene.h"
#include "Ray.h"
#include "GraphicalObject.h"

Raycast Raycast::castRay(const Ray ray)
{
	Vector::Vec3 interPoint;
	for (const auto obj : Scene::graphicalObjects)
	{
		for (const auto triangle : obj->triangles)
		{
			if (ray.intersects(*triangle, interPoint))
				return Raycast(true, triangle, interPoint);
		}
	}
	return Raycast(false);
}
