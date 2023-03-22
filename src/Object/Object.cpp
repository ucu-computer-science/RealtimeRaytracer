#include "Object.h"
#include "Scene.h"

Object::Object(const Vec3 pos) : pos(pos)
{
	Scene::objects.emplace_back(this);
}

void Object::translate(const Vec3& v)
{
	pos += v;
}

Vec3 Object::localToGlobalPos(const Vec3& localPos) const
{
	return localPos + pos;
}

Vec3 Object::globalToLocalPos(const Vec3& globalPos) const
{
	return globalPos - pos;
}
