#pragma once

#include <SDL.h>

#include "Action.h"

struct PixelMatrix
{
	uint32_t* pixels;
    bool recorded;
	int width, height;
    PixelMatrix(uint32_t* pixels, int w, int h) : pixels(pixels), recorded(false), width(w), height(h)
    {
    }

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


class SDLDisplayer
{
public:
	inline static SDL_Renderer* renderer;
	inline static SDL_Window* window;
	inline static SDL_Event event;
	inline static SDL_Texture* renderTexture;

	inline static int width, height;

	inline static Action onUpdate{};

	static int display(int width, int height);
	static void loop();
};

class FPSCounter
{
	inline static int frameCount = 0;
	inline static int lastFrameTime = 0;

public:
	inline static int fps = 0;
	static void updateFPSCounter();
};

class TriangleCounter
{
public:
	inline static int triangleCount = 0;

	static void updateTriangleCounter();
};

class Time
{
public:
	inline static float time = 0;
	inline static float deltaTime = 0;

	static void updateTime();
};
