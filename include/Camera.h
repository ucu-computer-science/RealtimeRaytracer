#pragma once

#include <SDL_stdinc.h>

#include "Object.h"
#include "Vec2.h"
#include "Vec2Int.h"

class Camera : public Object
{
public:
	static Camera* instance;

	double fov;
	Vec2Int resolution;
	Vec2 size;

	Camera(Vec3 pos, double fov, Vec2Int resolution, Vec2 size) : Object(pos), fov(fov), resolution(resolution), size(size)
	{
		if (instance != nullptr)
			throw std::runtime_error("Camera object already exists.");
		instance = this;
	}

	Vec3 getBotLeftCorner() const;
	Vec3 getFocalPoint() const;

	void updatePixelMatrix(Uint32* pixels) const;
};
