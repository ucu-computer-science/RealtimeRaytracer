#include "SDL_runner.h"

#include <SDL.h>

#include "Camera.h"
#include "Matrix.h"
#include "Input.h"

int show(const Vec2Int& resolution)
{
	SDL_Event event;
	SDL_Renderer* renderer;
	SDL_Window* window;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(resolution.x(), resolution.y(), 0, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	const auto surface = SDL_GetWindowSurface(window);
	const auto renderTexture = SDL_CreateTextureFromSurface(renderer, surface);
	 auto pixels = new Uint32[resolution.y() * resolution.x()];
	 const int  pitch = resolution.x() * sizeof(Uint32);
	//Camera::instance->setSkip(2);
	while (true)
	{

		if (SDL_PollEvent(&event)==0)
			continue;
		if (event.type == SDL_QUIT)
			break;

		Camera::instance->updatePixelMatrix(pixels);
		Input::updateInput(std::ref(event));

		SDL_UpdateTexture(renderTexture, nullptr, pixels, pitch);
		SDL_RenderCopy(renderer, renderTexture, nullptr, nullptr);
		SDL_RenderPresent(renderer);
	}
	delete[] pixels;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}
