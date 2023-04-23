#pragma once

// #include <SDL_stdinc.h>
#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "Color.h"
#include "Object.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "thread_pool_light.hpp"
#include <stdexcept>

struct Ray;

class Camera : public Object {
public:
  inline static Camera *instance = nullptr;

  float fov;
  glm::vec2 size;
  Color bgColor;
  float skip;
  BS::thread_pool_light pool;

  Camera(glm::vec3 pos, float fov, glm::vec2 size);

  glm::vec3 getScreenCenter() const;
  glm::vec3 getLeftBotCorner() const;
  glm::vec3 getLeftTopCorner() const;
  glm::vec3 getRightTopCorner() const;
  glm::vec3 getRightBotCorner() const;

  void updatePixelMatrix(uint32_t *pixels, int width, int height);

  void setBackgroundColor(Color color) { bgColor = color; }
};
#endif // RAYTRACER_CAMERA_H