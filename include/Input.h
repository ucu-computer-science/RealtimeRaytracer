#pragma once
#include <SDL_events.h>

class Input
{
public:
	inline static bool isFullscreen = false;
	inline static double moveSpeed = 0.4;
	inline static double rotationSpeed = 15;

	static void updateInput(SDL_Event event);
};
