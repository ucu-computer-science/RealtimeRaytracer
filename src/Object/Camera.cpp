#include "Camera.h"
#include "Ray.h"
#include "Raycast.h"
#include "SDLDisplayer.h"
#include "Triangle.h"

Camera::Camera(glm::vec3 pos, float fov, glm::vec2 size)
    : Object(pos), fov(fov), size{size}, bgColor(Color::black()) {
  if (instance != nullptr)
    throw std::runtime_error("Camera object already exists.");
  instance = this;
  skip = 1;
}

glm::vec3 Camera::getScreenCenter() const { return pos + forward() * fov; }
glm::vec3 Camera::getLeftBotCorner() const {
  return getScreenCenter() - 0.5f * size.y * up() - 0.5f * size.x * right();
}
glm::vec3 Camera::getLeftTopCorner() const {
  return getScreenCenter() + 0.5f * size.y * up() - 0.5f * size.x * right();
}
glm::vec3 Camera::getRightTopCorner() const {
  return getScreenCenter() + 0.5f * size.y * up() + 0.5f * size.x * right();
}
glm::vec3 Camera::getRightBotCorner() const {
  return getScreenCenter() - 0.5f * size.y * up() + 0.5f * size.x * right();
}

constexpr int TASK_COUNT = 72;
void Camera::updatePixelMatrix(uint32_t *pixels, int width, int height) {
  glm::vec3 dx = size.x / (float)width * right();
  glm::vec3 dy = size.y / (float)height * up();
  glm::vec3 lbDir = getLeftBotCorner() - pos;

#define MT
// #define ANTIALIASING
#ifdef MT

  for (int yStart = 0; yStart < TASK_COUNT; yStart += 1) {

    pool.push_task([this, pixels, width, lbDir, dx, dy, height, yStart] {
      for (int y = yStart; y < height; y += TASK_COUNT) {
//        srand(0);

        for (int x = 0; x < width; x += 1) {

#ifdef ANTIALIASING
          auto ray1 =
              Ray(pos, lbDir + ((float)x + ((float)(rand() % 100) / 100)) * dx +
                           ((float)y + ((float)(rand() % 100) / 100)) * dy);
#else
          auto ray1 = Ray(pos, lbDir + ((float)x) * dx + ((float)y) * dy);
#endif

          pixels[(height - y - 1) * width + x] =
              ((Raycast::castRay(ray1, 3)).toColor32());
        }
      }
    });
  }
  pool.wait_for_tasks();

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