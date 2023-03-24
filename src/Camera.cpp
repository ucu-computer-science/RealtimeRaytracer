#include "Camera.h"

Vec3 Camera::getFocalPoint() const
{
	return pos + screen.norm * fov;
}

Camera* Camera::instance = nullptr;
