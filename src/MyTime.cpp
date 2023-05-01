#include "MyTime.h"

#include "SDL_timer.h"
#include "glm/common.hpp"

void Time::updateTime()
{
	auto new_time = (float)SDL_GetTicks() / 1000.0f;
	deltaTime = new_time - time;
	clampedDeltaTime = glm::clamp(deltaTime, 0.0f, 1.0f);
	time = new_time;
}
