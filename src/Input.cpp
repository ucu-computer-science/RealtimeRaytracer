#include "Camera.h"
#include "Input.h"

double moveSpeed = 0.4;
double rotationSpeed = 5;
void Input::updateInput(const SDL_Event event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_w)
		{
			Camera::instance->translate(Camera::instance->forward() * moveSpeed);
		}
		else if (event.key.keysym.sym == SDLK_s)
		{
			Camera::instance->translate(Camera::instance->backward() * moveSpeed);
		}
		else if (event.key.keysym.sym == SDLK_a)
		{
			Camera::instance->translate(Camera::instance->left() * moveSpeed);
		}
		else if (event.key.keysym.sym == SDLK_d)
		{
			Camera::instance->translate(Camera::instance->right() * moveSpeed);
		}

		if (event.key.keysym.sym == SDLK_UP)
		{
			Camera::instance->rotateBy(Vec3(rotationSpeed, 0, 0));
		}
		else if (event.key.keysym.sym == SDLK_DOWN)
		{
			Camera::instance->rotateBy(Vec3(-rotationSpeed, 0, 0));
		}
		else if (event.key.keysym.sym == SDLK_LEFT)
		{
			Camera::instance->rotateBy(Vec3(0, 0, rotationSpeed));
		}
		else if (event.key.keysym.sym == SDLK_RIGHT)
		{
			Camera::instance->rotateBy(Vec3(0, 0, -rotationSpeed));
		}
	}
}
