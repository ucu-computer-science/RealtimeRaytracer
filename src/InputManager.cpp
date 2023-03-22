#include "Camera.h"
#include "Input.h"

float speed = 0.3f;
void Input::updateInput(const SDL_Event event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_w)
		{
			Camera::instance->translate(-Screen::instance->norm * speed);
		}
		else if (event.key.keysym.sym == SDLK_s)
		{
			Camera::instance->translate(Screen::instance->norm * speed);
		}
		else if (event.key.keysym.sym == SDLK_a)
		{
			Camera::instance->translate(-Screen::instance->dir1 * speed);
		}
		else if (event.key.keysym.sym == SDLK_d)
		{
			Camera::instance->translate(Screen::instance->dir1 * speed);
		}
	}
}
