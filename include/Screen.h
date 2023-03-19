#ifndef SCREEN_H
#define SCREEN_H

#include "Camera.h"
#include "Vec3.h"
#include "Vec2.h"
#include "Vec2Int.h"
#include "Ray.h"

class Screen
{
	class Camera* camera;
public:
	Vec2Int pixelSize;
	Vec2 size;
	Vec3 dir1, dir2;

	Screen(const Vec2 size, const Vec2Int pixelSize, const Vec3& dir1, const Vec3& dir2)
		: camera(nullptr), pixelSize(pixelSize), size(size), dir1(dir1), dir2(dir2)
	{
	}
	void setCamera(Camera& camera)
	{
		this->camera = &camera;
	}

	Vec3 getCenterPosition() const;
	Vec3 getPixelPosition(int x, int y) const;

	void update() const;
};
#endif // SCREEN_H
