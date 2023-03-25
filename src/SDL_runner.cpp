#include "SDL_runner.h"

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

	auto surface = SDL_GetWindowSurface(window);
	auto renderTexture = SDL_CreateTextureFromSurface(renderer, surface);
	auto pixels = new Uint32[resolution.y() * resolution.x()];
	while (true)
	{
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			break;

		Camera::instance->updatePixelMatrix(pixels);
		Input::updateInput(event);
		SDL_SetWindowFullscreen(window, Input::isFullscreen ? 1 : 0);

		SDL_UpdateTexture(renderTexture, nullptr, pixels, resolution.x() * sizeof(Uint32));
		SDL_Rect rect;
		rect.x = 0;
		rect.y = 0;
		rect.w = resolution.x();
		rect.h = resolution.y();
		SDL_Rect bounds = rect;
		SDL_RenderCopy(renderer, renderTexture, &rect, &bounds);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}
