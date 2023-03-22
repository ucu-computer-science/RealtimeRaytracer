#include "SDL_runner.h"

#include "Screen.h"
#include "ScreenMatrix.h"
#include "Input.h"

int show(const int width, const int height)
{
	SDL_Event event;
	SDL_Renderer* renderer;
	SDL_Window* window;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	ScreenMatrix pixelMatrix{ width, height };
	while (true) {
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			break;

		Screen::instance->updatePixelMatrix(pixelMatrix);
		Input::updateInput(event);

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				Color& color = pixelMatrix[y][x];
				SDL_SetRenderDrawColor(renderer, color.r() * 255, color.g() * 255, color.b() * 255, 255);
				SDL_RenderDrawPoint(renderer, x, y);
			}
		}
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}
