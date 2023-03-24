#include "GraphicalObject.h"

#include "Scene.h"

GraphicalObject::GraphicalObject(const Vec3 pos) : Object(pos)
{
	Scene::graphicalObjects.emplace_back(this);
}
