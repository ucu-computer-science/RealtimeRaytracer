#include "Object.h"

#include "Matrix.h"
#include "Scene.h"

Object::Object(const Vec3 pos) : pos(pos)
{
	Scene::objects.emplace_back(this);
}

Vec3 Object::forward() const
{
	return Matrix<double>::getRotationMatrix(rotation) * Vec3(0, 1, 0);
}
Vec3 Object::backward() const
{
	return Matrix<double>::getRotationMatrix(rotation) * Vec3(0, -1, 0);
}
Vec3 Object::up() const
{
	return Matrix<double>::getRotationMatrix(rotation) * Vec3(0, 0, 1);
}
Vec3 Object::down() const
{
	return Matrix<double>::getRotationMatrix(rotation) * Vec3(0, 0, -1);
}
Vec3 Object::left() const
{
	return Matrix<double>::getRotationMatrix(rotation) * Vec3(-1, 0, 0);
}
Vec3 Object::right() const
{
	return Matrix<double>::getRotationMatrix(rotation) * Vec3(1, 0, 0);
}

void Object::translate(const Vec3& v)
{
	pos += v;
}
void Object::rotateBy(const Vec3& degrees)
{
	rotation += degrees;
}

Vec3 Object::localToGlobalPos(const Vec3& localPos) const
{
	return Matrix<double>::getRotationMatrix(rotation) * localPos + pos;
}
Vec3 Object::globalToLocalPos(const Vec3& globalPos) const
{
	return Matrix<double>::getRotationMatrix(-rotation) * globalPos - pos;
}
