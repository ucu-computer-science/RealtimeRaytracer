#include "Screen.h"

#include "Ray.h"
#include "Raycast.h"
#include "Camera.h"
#include "Color.h"
#include "Vec3.h"

using Vector::Color;

Screen* Screen::instance = nullptr;

Vec3 Screen::getBotLeftCorner() const
{
	auto camera = Camera::instance;
	return camera->pos - 0.5 * size.x() * camera->localToGlobalPos(dir1) - 0.5 * size.y() * camera->localToGlobalPos(dir2);
}

void Screen::updatePixelMatrix(Uint32* pixels) const
{
	Vec3 focalPoint = Camera::instance->getFocalPoint();
	auto sizeX = pixelSize.x();
	auto sizeY = pixelSize.y();
	Vec3 dx = size.x() / (double)sizeX * dir1;
	Vec3 dy = size.y() / (double)sizeY * dir2;
	Vec3 pos1 = getBotLeftCorner();
	for (int y = 0; y < sizeY; ++y)
	{
		Vec3 pos2 = pos1;
		for (int x = 0; x < sizeX; ++x)
		{
			auto ray = Ray(focalPoint, pos2 - focalPoint);
			Raycast raycast = Raycast::castRay(ray);
			pixels[y * sizeX + x] = raycast.ray.hit() ? 0x00000000 : 0xffffff00;
			pos2 += dx;
		}
		pos1 += dy;
	}
}
