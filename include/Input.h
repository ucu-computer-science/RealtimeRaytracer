#pragma once
#include <SDL_events.h>

class Input
{
public:
	inline static bool isFullscreen = false;
	inline static float moveSpeed = 0.4f;
	inline static float rotationSpeed = 15.0f;

	static void updateInput(const SDL_Event& event);
};
