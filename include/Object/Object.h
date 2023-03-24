#pragma once

#include "Vec3.h"

class Object
{
public:
	Vec3 pos;
	Vec3 rotation;

	explicit Object(Vec3 pos);

	Vec3 forward() const;
	Vec3 backward() const;
	Vec3 up() const;
	Vec3 down() const;
	Vec3 left() const;
	Vec3 right() const;

	void translate(const Vec3& v);
	void rotateBy(const Vec3& degrees);

	Vec3 localToGlobalPos(const Vec3& localPos) const;
	Vec3 globalToLocalPos(const Vec3& globalPos) const;
};
