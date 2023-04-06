#pragma once
#include <SDL_events.h>

class Input
{
public:
	static bool isFullscreen;
	static float moveSpeed;
	static float rotationSpeed;
	inline static const Uint8* keyboardState;

	static void updateInput();
};
