#include "Raycast.h"
#include "Scene.h"
#include "Ray.h"
#include "GraphicalObject.h"

Raycast Raycast::castRay(Ray& ray)
{
	for (const auto obj : Scene::graphicalObjects)
	{
		obj->intersect(ray);
	}

	return Raycast(ray);
}
