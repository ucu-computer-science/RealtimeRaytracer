#include "Screen.h"

Vec3 Screen::getCenterPosition() const
{
	return camera->pos + 0.5f * size.x() * dir1 + 0.5f * size.y() * dir2;
}

Vec3 Screen::getPixelPosition(const int x, const int y) const
{
	return camera->pos + (float)x / (float)pixelSize.x() * size.x() * dir1 + (float)y / (float)pixelSize.y() * size.y() * dir2;
}

void Screen::update() const
{
	const Vec3 focalPoint = camera->getFocalPoint();

	const Vec3 dx = size.x() / (float)pixelSize.x() * dir1;
	const Vec3 dy = size.y() / (float)pixelSize.y() * dir2;
	Vec3 pos1 = camera->pos;
	for (int i = 0; i < pixelSize.y(); ++i)
	{
		Vec3 pos2 = pos1;
		for (int j = 0; j < pixelSize.x(); ++j)
		{
			auto ray = Ray(focalPoint, pos2 - focalPoint);
			pos2 += dx;
		}
		pos1 += dy;
	}
}
