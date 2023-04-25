#pragma once

#include <SDL_events.h>

class Input
{
public:
	static bool isFullscreen;
	static bool isFocused;
	static float defaultMoveSpeed;
	static float keyRotationSpeed;
	static float mouseRotationSpeed;
	inline static const Uint8* keyboardState;

	static void updateInput();
	static void handleSDLEvent(SDL_Event event);
};
