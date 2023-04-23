#pragma once

#include "Action.h"
#include <SDL.h>

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
	inline static uint32_t lastFrameTime = 0;

public:
	inline static uint32_t fps = 0;
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
