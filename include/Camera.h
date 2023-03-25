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
	int skip;
	Camera(Vec3 pos, double fov, Vec2Int resolution, Vec2 size) : Object(pos), fov(fov), resolution(resolution), size(size)
	{
		if (instance != nullptr)
			throw std::runtime_error("Camera object already exists.");
		instance = this;
		skip = 1;
	}

	Vec3 getBotLeftCorner() const;
	Vec3 getFocalPoint() const;
	void setSkip(int newskip)
	{
		skip = newskip;
	}
	int getSkip() const
	{
		return skip;
	}
	void updatePixelMatrix(Uint32* pixels) const;
};
