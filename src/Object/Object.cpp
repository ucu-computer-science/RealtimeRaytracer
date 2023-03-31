#include "Object.h"
#include "Matrix.h"
#include "Scene.h"


Object::Object(const glm::vec3 pos) : pos(pos), rotation(1.0, 0.0, 0.0, 0.0)
{
	Scene::objects.emplace_back(this);
}

glm::vec3 Object::forward() const
{
	return rotation * glm::vec3(0, 1, 0);
}
glm::vec3 Object::backward() const
{
	return rotation * glm::vec3(0, -1, 0);
}
glm::vec3 Object::up() const
{
	return rotation * glm::vec3(0, 0, 1);
}
glm::vec3 Object::down() const
{
	return rotation * glm::vec3(0, 0, -1);
}
glm::vec3 Object::left() const
{
	return rotation * glm::vec3(-1, 0, 0);
}
glm::vec3 Object::right() const
{
	return rotation * glm::vec3(1, 0, 0);
}

void Object::translate(const glm::vec3& v)
{
	pos += v;
}
void Object::rotateBy(const glm::vec3& degrees)
{
	rotation = normalize(rotation * glm::quat(degrees / 180.0f * PI));
}

glm::vec3 Object::localToGlobalPos(const glm::vec3& localPos) const
{
	return rotation * localPos + pos;
}
glm::vec3 Object::globalToLocalPos(const glm::vec3& globalPos) const
{
	return -rotation * globalPos - pos;
}
