#pragma once
#include <SDL_events.h>

class Input
{
public:
	static bool isFullscreen;
	static float moveSpeed;
	static float rotationSpeed;

	static void updateInput(const SDL_Event& event);
};
