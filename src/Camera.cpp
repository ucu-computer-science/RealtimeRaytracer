#include "Camera.h"
#include "Ray.h"
#include "Raycast.h"
#include "Triangle.h"

Camera* Camera::instance = nullptr;

Vec3 Camera::getFocalPoint() const
{
	return pos + backward() * fov;
}

Vec3 Camera::getBotLeftCorner() const
{
	return pos - 0.5 * size.y() * up() - 0.5 * size.x() * right();
}

void Camera::updatePixelMatrix(Uint32* pixels) const
{
	Vec3 focalPoint = Camera::instance->getFocalPoint();
	auto sizeX = resolution.x();
	auto sizeY = resolution.y();
	Vec3 dx = size.x() / (double)sizeX * right();
	Vec3 dy = size.y() / (double)sizeY * up();
	Vec3 pos1 = getBotLeftCorner();
	for (int y = 0; y < sizeY; ++y)
	{
		Vec3 pos2 = pos1;
		for (int x = 0; x < sizeX; ++x)
		{
			auto ray = Ray(focalPoint, pos2 - focalPoint);
			Raycast raycast = Raycast::castRay(ray);
			pixels[y * sizeX + x] = raycast.ray.hit() ? raycast.ray.closestTriangle->color.toColor32() : Color::black().toColor32();
			pos2 += dx;
		}
		pos1 += dy;
	}
}
