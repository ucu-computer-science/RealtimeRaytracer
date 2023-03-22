#pragma once

#include "Vec2.h"
#include "Vec2Int.h"
#include "Vec3.h"

using Vector::Vec2;
using Vector::Vec2Int;
using Vector::Vec3;

class Camera;
class ScreenMatrix;

class Screen
{
public:
	static Screen* instance;

	Vec2Int pixelSize;
	Vec2 size;
	Vec3 dir1, dir2, norm;

	Screen(const Vec2 size, const Vec2Int pixelSize, const Vec3& dir1, const Vec3& dir2)
		: pixelSize(pixelSize), size(size), dir1(dir1), dir2(dir2), norm(dir1.cross(dir2).normalized())
	{
		if (instance != nullptr)
			throw std::runtime_error("Screen object already exists.");
		instance = this;
	}

	Vec3 getCenterPosition() const;

	void updatePixelMatrix(ScreenMatrix& matrix) const;
};
