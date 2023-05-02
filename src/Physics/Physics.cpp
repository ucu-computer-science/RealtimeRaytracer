#include "Physics.h"

#include "BoundingBoxes.h"
#include "Ray.h"


bool Physics::castRay(Ray& ray)
{
	//for (const auto& obj : Scene::graphicalObjects)
	//{
	//	if (obj->includeInBVH()) continue;
	//	obj->intersect(ray);
	//}
	BVHBuilder::nodes[0]->intersect(ray);

	return ray.hit();
}
