#pragma once

#include "Vec3.h"
using Vector::Vec3;

class Object
{
public:
	Vec3 pos;

	explicit Object(Vec3 pos);

	void translate(const Vec3& v);

	Vec3 localToGlobalPos(const Vec3& localPos) const;
	Vec3 globalToLocalPos(const Vec3& globalPos) const;
};
