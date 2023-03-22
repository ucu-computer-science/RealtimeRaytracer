#include "Camera.h"

Vec3 Camera::getFocalPoint() const
{
	const auto center = screen.getCenterPosition();
	return center + screen.norm * fov;
}

Camera* Camera::instance = nullptr;
