#include "Physics.h"

#include "BoundingBoxes.h"
#include "Ray.h"
#include "Scene.h"


bool Physics::castRay(Ray& ray)
{
	for (const auto& obj : Scene::graphicalObjects)
	{
		if (obj->includeInBVH()) continue;
		obj->intersect(ray);
	}
	BVHNode::root->intersect(ray);

	return ray.hit();
}
