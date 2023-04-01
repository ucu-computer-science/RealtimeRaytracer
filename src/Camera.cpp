#include "Camera.h"
#include "Ray.h"
#include "Raycast.h"
#include "SDLDisplayer.h"
#include "Triangle.h"

Camera* Camera::instance = nullptr;

glm::vec3 Camera::getLeftBotCorner() const
{
	return getScreenCenter() - 0.5f * size.y * up() - 0.5f * size.x * right();
}
glm::vec3 Camera::getLeftTopCorner() const
{
	return getScreenCenter() + 0.5f * size.y * up() - 0.5f * size.x * right();
}
glm::vec3 Camera::getRightTopCorner() const
{
	return getScreenCenter() + 0.5f * size.y * up() + 0.5f * size.x * right();
}
glm::vec3 Camera::getRightBotCorner() const
{
	return getScreenCenter() - 0.5f * size.y * up() + 0.5f * size.x * right();
}
glm::vec3 Camera::getScreenCenter() const
{
	return pos + forward() * fov;
}

void Camera::updatePixelMatrix(uint32_t* pixels, int width, int height)
{
	glm::vec3 dx = skip * size.x / (float)width * right();
	glm::vec3 dy = skip * size.y / (float)height * up();
	glm::vec3 lbDir = getLeftBotCorner() - pos;

	for (int y = 0; y < height; y += skip)
	{
		pool.push_task([this, pixels, width, lbDir, dx, y, dy, height]
		{
			for (int x = 0; x < width; x += skip)
			{
				auto ray = Ray(pos, lbDir + (float)x * dx / skip + (float)y * dy / skip);
				pixels[(height - y - 1) * width + x] = Raycast::castRay(ray).ray.color.toColor32();
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
