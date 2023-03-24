#include "SDL_runner.h"

#include "Color.h"
#include "Screen.h"
#include "Matrix.h"
#include "Input.h"

using Vector::Color;

int show(const Vec2Int& resolution)
{
	SDL_Event event;
	SDL_Renderer* renderer;
	SDL_Window* window;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(resolution.x(), resolution.y(), 0, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	auto renderTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_TARGET, resolution.x(), resolution.y());
	auto pixels = new Uint32[resolution.y() * resolution.x()];
	while (true) {
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			break;

		Screen::instance->updatePixelMatrix(pixels);
		Input::updateInput(event);
		//std::cout << 1;
		//for (int y = 0; y < height; y++)
		//{
		//	for (int x = 0; x < width; x++)
		//	{
		//		pixels[y * width + x] = Color::white().toColor32();
		//		/*SDL_SetRenderDrawColor(renderer, color, color, color, 255);
		//		SDL_RenderDrawPoint(renderer, x, y);*/
		//	}
		//}

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
