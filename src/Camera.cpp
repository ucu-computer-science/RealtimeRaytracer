#include "Camera.h"
#include "Ray.h"
#include "Raycast.h"
#include "Triangle.h"

Camera* Camera::instance = nullptr;

glm::vec3 Camera::getBotLeftCorner() const
{
	return pos - 0.5f * size.y * up() - 0.5f * size.x * right();
}
glm::vec3 Camera::getFocalPoint() const
{
	return pos + backward() * fov;
}

uint32_t Camera::castRayAndGetColor32(Ray ray) const
{
	Raycast raycast = Raycast::castRay(ray);
	return raycast.ray.hit() ? raycast.ray.closestTriangle->color.toColor32() : bgColor32;
}


void Camera::updatePixelMatrix(uint32_t* pixels)
{
	glm::vec3 focalPoint = getFocalPoint();
	int sizeX = (int)resolution.x;
	int sizeY = (int)resolution.y;
	glm::vec3 dx = skip * size.x / (float)sizeX * right();
	glm::vec3 dy = skip * size.y / (float)sizeY * up();
	glm::vec3 dir1 = getBotLeftCorner() - focalPoint;

	for (int y = 0; y < sizeY; y += skip, dir1 += dy)
	{
		pool.push_task([this, focalPoint, pixels, sizeX, dir1, dx, y]
		{
			auto dir2 = dir1;
			for (int x = 0; x < sizeX; x += skip, dir2 += dx)
			{
				pixels[y * sizeX + x] = castRayAndGetColor32(Ray(focalPoint, dir2));
			}
		});
	}
	pool.wait_for_tasks();
	/*for (int y = 0; y < sizeY; y += skip, dir1 += dy)
	{
		auto dir2 = dir1;
		for (int x = 0; x < sizeX; x += skip, dir2 += dx)
		{
			pixels[y * sizeX + x] = castRayAndGetColor32(Ray(focalPoint, dir2));
		}
	}*/
}
