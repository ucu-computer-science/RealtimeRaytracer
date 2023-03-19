#ifndef CAMERA_H
#define CAMERA_H

#include "Screen.h"
#include "Object.h"
#include <iostream>

class Camera : public Object
{
public:
	float fov;
	const class Screen* const screen;

	Camera(const float fov, const Screen* screen) : fov(fov), screen(screen) {}

	Vec3 getFocalPoint() const;
};
#endif // CAMERA_H
