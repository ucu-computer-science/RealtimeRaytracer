#include "Camera.h"
#include "Ray.h"
#include "Raycast.h"
#include "Triangle.h"

Camera* Camera::instance = nullptr;

glm::vec3 Camera::getFocalPoint() const
{
	return pos + backward() * fov;
}

glm::vec3 Camera::getBotLeftCorner() const
{
	return pos - 0.5f * size.y * up() - 0.5f * size.x * right();
}

void Camera::updatePixelMatrix(uint32_t* pixels) const
{
	glm::vec3 focalPoint = getFocalPoint();
	int sizeX = (int)resolution.x;
	int sizeY = (int)resolution.y;
	glm::vec3 dx = size.x / (float)sizeX * right();
	glm::vec3 dy = size.y / (float)sizeY * up();
	glm::vec3 pos1 = getBotLeftCorner() - focalPoint;
	for (int y = 0; y < sizeY; ++y, pos1 += dy)
	{
		glm::vec3 pos2 = pos1;
		for (int x = 0; x < sizeX; ++x, pos2 += dx)
		{
            auto ray = Ray(focalPoint, pos2);
			Raycast raycast = Raycast::castRay(ray);
			//std::cout << x << ":" << y << std::endl;
			pixels[y * sizeX + x] = raycast.ray.hit() ? raycast.ray.closestTriangle->color.toColor32() : bgColor32;
		}
	}
}
