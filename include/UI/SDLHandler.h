#pragma once

#include <SDL2/include/SDL.h>

#include "Action.h"

struct PixelMatrix
{
	uint32_t* pixels;
	int width, height;
	PixelMatrix(uint32_t* pixels, int w, int h) : pixels(pixels), width(w), height(h) { }

	void setPixelSafe(int x, int y, uint32_t color32) const
	{
		if (y < 0 || y >= height || x < 0 || x >= width) return;
		pixels[y * width + x] = color32;
	}
	uint32_t getPixelSafe(int x, int y) const
	{
		if (y < 0 || y >= height || x < 0 || x >= width) return 0;
		return pixels[y * width + x];
	}

	~PixelMatrix()
	{
		delete[] pixels;
	}
};


class SDLHandler
{
public:
	inline static SDL_Renderer* renderer;
	inline static SDL_Window* window;
	inline static SDL_Event event;
	inline static SDL_GLContext context;

	inline static bool windowFocused = true;
	inline static bool isFullscreen = false;

	static void initialize(int width, int height);
	//static void loop();
	static bool update();
	static void quit();
};
