#include "SDLDisplayer.h"

#include "Camera.h"
#include "Input.h"
#include "Matrix.h"
#include <iostream>

#include "GraphicalObject.h"
#include "Scene.h"

int SDLDisplayer::display(int width, int height) {
  SDLDisplayer::width = width;
  SDLDisplayer::height = height;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);
  auto surface = SDL_GetWindowSurface(window);
  renderTexture = SDL_CreateTextureFromSurface(renderer, surface);

  loop();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return EXIT_SUCCESS;
}
void SDLDisplayer::loop() {
  auto pixels = new uint32_t[height * width];
  const int pitch = width * sizeof(uint32_t);
  while (true) {
    while (SDL_PollEvent(&event))
      continue;
    if (event.type == SDL_QUIT)
      break;

    Time::updateTime();
    Input::updateInput();
    onUpdate();
    Camera::instance->updatePixelMatrix(pixels, width, height);

    // Stats
    FPSCounter::updateFPSCounter();
    TriangleCounter::updateTriangleCounter();
    std::cout << "FPS: " << FPSCounter::fps
              << "  Triangles:" << TriangleCounter::triangleCount << '\n';

    SDL_UpdateTexture(renderTexture, nullptr, pixels, pitch);
    SDL_RenderCopy(renderer, renderTexture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
  }
  delete[] pixels;
}

void FPSCounter::updateFPSCounter() {
  uint32_t currTime = SDL_GetTicks();
  if (currTime >= lastFrameTime + 200) {
    fps = (float)frameCount / (float)(currTime - lastFrameTime) * 1000;
    frameCount = 0;
    lastFrameTime = currTime;
  }
  frameCount++;
}

void TriangleCounter::updateTriangleCounter() {
  triangleCount = 0;
  for (auto obj : Scene::graphicalObjects)
    triangleCount += (int)obj->cameraFacingTriangles.size();
}

void Time::updateTime() {
  auto new_time = (float)SDL_GetTicks() / 1000.0f;
  deltaTime = new_time - time;
  time = new_time;
}