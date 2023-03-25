#pragma once

#include <SDL_stdinc.h>

#include "Color.h"
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
	uint32_t bgColor32;

	Camera(Vec3 pos, double fov, Vec2Int resolution, Vec2 size) : Object(pos), fov(fov), resolution(resolution), size(size), bgColor32(Color::black().toColor32())
	{
		if (instance != nullptr)
			throw std::runtime_error("Camera object already exists.");
		instance = this;
	}

	void setBackgroundColor(Color color) { bgColor32 = color.toColor32(); }

	Vec3 getBotLeftCorner() const;
	Vec3 getFocalPoint() const;
	void updatePixelMatrix(Uint32* pixels) const;
};
