#include "Screen.h"
#include "Ray.h"
#include "Raycast.h"
#include "Camera.h"
#include "Color.h"
#include "ScreenMatrix.h"
#include "Vec3.h"

using Vector::Color;

Screen* Screen::instance = nullptr;

Vec3 Screen::getCenterPosition() const
{
	return Camera::instance->pos + 0.5f * size.x() * dir1 + 0.5f * size.y() * dir2;
}

void Screen::updatePixelMatrix(ScreenMatrix& matrix) const
{
	Vec3 focalPoint = Camera::instance->getFocalPoint();
	Vec3 dx = size.x() / (float)pixelSize.x() * dir1;
	Vec3 dy = size.y() / (float)pixelSize.y() * dir2;
	Vec3 pos1 = Camera::instance->pos;
	for (int y = 0; y < pixelSize.y(); ++y)
	{
		Vec3 pos2 = pos1;
		for (int x = 0; x < pixelSize.x(); ++x)
		{
			auto ray = Ray(focalPoint, pos2 - focalPoint);
			Raycast raycast = Raycast::castRay(ray);
			matrix[y][x] = raycast.hit ? Color::black() : Color::white();
			pos2 += dx;
		}
		pos1 += dy;
	}
}
