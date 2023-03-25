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
	Vec3 dx = skip * size.x() / (double)sizeX * right();
	Vec3 dy = skip * size.y() / (double)sizeY * up();
	Vec3 pos1 = getBotLeftCorner() - focalPoint;



	for (int y = 0; y < sizeY; ++y)
	{
		Vec3 pos2 = pos1;
		for (int x = 0; x < sizeX; ++x)
		{
			Ray ray1 = Ray(focalPoint, pos2);
			pos2 += dx;
			//Ray ray2 = Ray(focalPoint, pos2);
			//pos2 += dx;
			//Ray ray3 = Ray(focalPoint, pos2);
			//pos2 += dx;
			//Ray ray4 = Ray(focalPoint, pos2);
			//pos2 += dx;

			Raycast raycast1 = Raycast::castRay(ray1);
			//Raycast raycast2 = Raycast::castRay(ray2);
			//Raycast raycast3 = Raycast::castRay(ray3);
			//Raycast raycast4 = Raycast::castRay(ray4);



			pixels[y * sizeX + x + 0] = raycast1.ray.hit() ? raycast1.ray.closestTriangle->color.toColor32() : Color::black().toColor32();
			//pixels[y * sizeX + x + 1] = raycast2.ray.hit() ? raycast2.ray.closestTriangle->color.toColor32() : Color::black().toColor32();
			//pixels[y * sizeX + x + 2] = raycast3.ray.hit() ? raycast3.ray.closestTriangle->color.toColor32() : Color::black().toColor32();
			//pixels[y * sizeX + x + 3] = raycast4.ray.hit() ? raycast4.ray.closestTriangle->color.toColor32() : Color::black().toColor32();

		}
		pos1 += dy;
	}
}
