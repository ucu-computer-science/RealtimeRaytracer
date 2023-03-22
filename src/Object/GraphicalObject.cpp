#include "GraphicalObject.h"

#include "Scene.h"

GraphicalObject::GraphicalObject(const Vec3 pos, std::vector<Triangle*> triangles) : Object(pos), triangles(std::move(triangles))
{
	Scene::graphicalObjects.emplace_back(this);
}
