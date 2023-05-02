#include "Object.h"

#include "Matrix.h"
#include "Scene.h"


Object::Object(const glm::vec3 pos, glm::quat rot) : pos(pos), rot(rot)
{
	Scene::objects.emplace_back(this);
}

void Object::setPos(glm::vec3 pos) { this->pos = pos; }
void Object::setRot(glm::quat rot) { this->rot = rot; }
void Object::translate(const glm::vec3& v)
{
	setPos(pos + v);
}
void Object::rotate(const glm::vec3& degrees)
{
	setRot(glm::quat(eulerAngles(rot) + degrees * DEG_TO_RAD));
}

glm::vec3 Object::forward() const { return rot * glm::vec3(0, 1, 0); }
glm::vec3 Object::backward() const { return rot * glm::vec3(0, -1, 0); }
glm::vec3 Object::up() const { return rot * glm::vec3(0, 0, 1); }
glm::vec3 Object::down() const { return rot * glm::vec3(0, 0, -1); }
glm::vec3 Object::left() const { return rot * glm::vec3(-1, 0, 0); }
glm::vec3 Object::right() const { return rot * glm::vec3(1, 0, 0); }

glm::vec3 Object::localToGlobalPos(const glm::vec3& localPos) const
{
	return rot * localPos + pos;
}
glm::vec3 Object::globalToLocalPos(const glm::vec3& globalPos) const
{
	return -rot * globalPos - pos;
}

nlohmann::basic_json<> Object::toJson()
{
	nlohmann::basic_json<> j;
	j["pos"][0] = getPos()[0];
	j["pos"][1] = getPos()[1];
	j["pos"][2] = getPos()[2];
	j["rot"][0] = getRot()[0];
	j["rot"][1] = getRot()[1];
	j["rot"][2] = getRot()[2];
	j["rot"][3] = getRot()[3];
	return j;
}
