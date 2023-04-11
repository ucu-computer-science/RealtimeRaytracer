#pragma once
#ifndef RAYTRACER_INPUT_H
#define RAYTRACER_INPUT_H
#include <SDL_events.h>

class Input {
public:
  static bool isFullscreen;
  static float defaultMoveSpeed;
  static float rotationSpeed;
  inline static const Uint8 *keyboardState;

  static void updateInput();
};

#endif // RAYTRACER_INPUT_H