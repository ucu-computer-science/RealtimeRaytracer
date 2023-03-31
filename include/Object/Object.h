#pragma once

#include "glm/vec3.hpp"
#include "glm/gtc/quaternion.hpp"

class Object
{
public:
	glm::vec3 pos;
	glm::quat rotation;

	explicit Object(glm::vec3 pos);
	virtual ~Object() = default;

	glm::vec3 forward() const;
	glm::vec3 backward() const;
	glm::vec3 up() const;
	glm::vec3 down() const;
	glm::vec3 left() const;
	glm::vec3 right() const;

	void translate(const glm::vec3& v);
	void rotateBy(const glm::vec3& degrees);

	glm::vec3 localToGlobalPos(const glm::vec3& localPos) const;
	glm::vec3 globalToLocalPos(const glm::vec3& globalPos) const;
};
