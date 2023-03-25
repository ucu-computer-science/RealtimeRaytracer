#include "SDL_runner.h"

#include <iostream>
#include "Camera.h"
#include "Matrix.h"
#include "Input.h"
#include "glm/vec2.hpp"

int frameCount = 0;
uint32_t lastFrameTime = 0;

int show(const glm::vec2 resolution)
{
	int sizeX = (int)resolution.x, sizeY = (int)resolution.y;

	SDL_Event event;
	SDL_Renderer* renderer;
	SDL_Window* window;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(sizeX, sizeY, 0, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	auto surface = SDL_GetWindowSurface(window);
	auto renderTexture = SDL_CreateTextureFromSurface(renderer, surface);
	auto pixels = new uint32_t[sizeY * sizeX];
	while (true)
	{
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			break;

		Camera::instance->updatePixelMatrix(pixels);
		Input::updateInput(event);
		SDL_SetWindowFullscreen(window, Input::isFullscreen ? 1 : 0);

		uint32_t currTime = SDL_GetTicks();
		if (currTime >= lastFrameTime + 1000)
		{
			std::cout << "fps: " << frameCount / (float)(currTime - lastFrameTime) * 1000 << '\n';
			frameCount = 0;
			lastFrameTime = currTime;
		}
		frameCount++;
		SDL_UpdateTexture(renderTexture, nullptr, pixels, sizeX * sizeof(Uint32));
		SDL_RenderCopy(renderer, renderTexture, nullptr, nullptr);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}
