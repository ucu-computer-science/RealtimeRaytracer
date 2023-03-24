#include "Raycast.h"
#include "Scene.h"
#include "Ray.h"
#include "GraphicalObject.h"

Raycast Raycast::castRay(Ray& ray)
{
	Vector::Vec3 interPoint;
	for (const auto obj : Scene::graphicalObjects)
	{
		for (const auto triangle : obj->triangles)
		{
			ray.intersects(*triangle);
		}
	}
	return Raycast(ray);
}
