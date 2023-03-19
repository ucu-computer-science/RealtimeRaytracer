#include "Camera.h"

Vec3 Camera::getFocalPoint() const
{
	const auto center = screen->getCenterPosition();
	const auto orthogonal = (screen->dir1.cross(screen->dir2)).normalized();
	return center + orthogonal * fov;
}
