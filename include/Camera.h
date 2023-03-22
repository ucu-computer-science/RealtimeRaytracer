#pragma once

#include "Object.h"
#include "Screen.h"

class Camera : public Object
{
public:
	static Camera* instance;

	float fov;
	const Screen& screen;

	Camera(const Vec3 pos, const float fov, const Screen& screen) : Object(pos), fov(fov), screen(screen)
	{
		if (instance != nullptr)
			throw std::runtime_error("Screen object already exists.");
		instance = this;
	}

	Vec3 getFocalPoint() const;
};
