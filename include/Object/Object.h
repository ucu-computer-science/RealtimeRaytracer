#pragma once

#include "Vec3.h"
using Vector::Vec3;

class Object
{
public:
	Vec3 pos;
	Vec3 rotation;

	explicit Object(Vec3 pos);

	void translate(const Vec3& v);
	void rotateBy(const Vec3& degrees);

	Vec3 localToGlobalPos(const Vec3& localPos) const;
	Vec3 globalToLocalPos(const Vec3& globalPos) const;
};
