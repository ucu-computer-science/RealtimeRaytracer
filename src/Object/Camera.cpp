#include "Camera.h"

#include "MathExtensions.h"
#include "Ray.h"
#include "Raycast.h"
#include "SDLDisplayer.h"
#include "Triangle.h"

Camera::Camera(glm::vec3 pos, float fov, float lensRadius, glm::vec2 size) : Object(pos), fov(fov), lensRadius(lensRadius), size{size}, bgColor(Color::black())
{
	if (instance != nullptr)
		throw std::runtime_error("Camera object already exists.");
	instance = this;
}
void Camera::translate(const glm::vec3& v)
{
	Object::translate(v);
	onCameraMove();
}
void Camera::rotate(const glm::vec3& degrees)
{
	Object::rotate(degrees);
	onCameraRotate();
}

glm::vec3 Camera::getScreenCenter() const { return pos + forward() * fov; }
glm::vec3 Camera::getLeftBotCorner() const
{
	return getScreenCenter() - 0.5f * size.y * up() - 0.5f * size.x * right();
}

constexpr int TASK_COUNT = 72;
void Camera::updatePixelMatrix(const PixelMatrix& pixelMatrix)
{
	auto width = pixelMatrix.width, height = pixelMatrix.height;
	auto pixels = pixelMatrix.pixels;
	float dx = size.x / (float)width;
	float dy = size.y / (float)height;
	glm::vec3 dxDir = dx * right();
	glm::vec3 dyDir = dy * up();
	glm::vec3 lbDir = getLeftBotCorner() - pos;

#define MT
#ifdef MT

	constexpr int samplesPerPixel = 1;
	for (int yStart = 0; yStart < TASK_COUNT; yStart += 1)
	{
		pool.push_task([this, pixels, width, lbDir, dxDir, dyDir, height, yStart, dx, dy]
		{
			for (int y = yStart; y < height; y += TASK_COUNT)
			{
				for (int x = 0; x < width; x += 1)
				{
					Color pixelColor{};
					auto rayPos = pos;
					auto rayDir = lbDir + (float)x * dxDir + (float)y * dyDir;
					for (int i = 0; i < samplesPerPixel; ++i)
					{
						auto lensOffset = lensRadius * randomVectorInCircle(1) * rot;
						//auto aaOffset = rot * randomVectorInRectangle(dx, dy) * 1.0f;
						pixelColor += Raycast::castRay(Ray(rayPos /*+ lensOffset*/, rayDir - lensOffset/*+ aaOffset*/), 5);
					}
					pixelColor /= samplesPerPixel;
					pixels[(height - y - 1) * width + x] = pixelColor.toColor32();
				}
			}
		});
	}
	pool.wait_for_tasks();

	/*    Pixel Averaging
		
	auto pixelsCopy = new Color[(size_t)width * height];
	for (int i = 0; i < width * height; ++i)
	{
		pixelsCopy[i] = Color::fromColor32(pixels[i]);
	}
	for (int y = 0; y < height; y += 1)
	{
		for (int x = 0; x < width; x += 1)
		{
			int pixelIndex = (height - y - 1) * width + x;
			Color averageColor{};
			constexpr int r = 50;
			for (int y_ = y - r; y_ <= y + r; ++y_)
			{
				if (y_ >= height || y_ < 0) continue;
				for (int x_ = x - r; x_ <= x + r; ++x_)
				{
					if (x_ >= width || x_ < 0) continue;
					averageColor += pixelsCopy[(height - y_ - 1) * width + x_];
				}
			}
			averageColor *= 1.0f / ((r * 2 + 1) * (r * 2 + 1));
			pixels[pixelIndex] = averageColor.toColor32();
		}
	}
	*/

#else
  for (int y = 0; y < height; y += skip) {
    for (int x = 0; x < width; x += skip) {
      pixels[(height - y - 1) * width + x] =
          Raycast::castRay(
              Ray(pos, lbDir + (float)x * dx / skip + (float)y * dy / skip))
              .toColor32();
    }
  }
#endif
}

nlohmann::basic_json<> Camera::toJson()
{
	auto j = Object::toJson();
	j["fov"] = fov;
	j["lensRadius"] = lensRadius;
	j["size"][0] = size[0];
	j["size"][1] = size[1];
	j["type"] = "Camera";
	return j;
}
