#pragma once
#include <SDL_events.h>

class Input
{
public:
	static void updateInput(const SDL_Event& event);
};
