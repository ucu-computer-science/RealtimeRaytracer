#include "Camera.h"
#include "Input.h"

#include "SDLDisplayer.h"

bool Input::isFullscreen = false;
float Input::moveSpeed = 0.4f;
float Input::rotationSpeed = 15.0f;

void Input::updateInput(const SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		// Movement
		if (event.key.keysym.sym == SDLK_w)
		{
			Camera::instance->translate(Camera::instance->forward() * moveSpeed);
		}
		if (event.key.keysym.sym == SDLK_s)
		{
			Camera::instance->translate(Camera::instance->backward() * moveSpeed);
		}
		if (event.key.keysym.sym == SDLK_a)
		{
			Camera::instance->translate(Camera::instance->left() * moveSpeed);
		}
		if (event.key.keysym.sym == SDLK_d)
		{
			Camera::instance->translate(Camera::instance->right() * moveSpeed);
		}
		if (event.key.keysym.sym == SDLK_q)
		{
			Camera::instance->translate(Camera::instance->up() * moveSpeed);
		}
		if (event.key.keysym.sym == SDLK_e)
		{
			Camera::instance->translate(Camera::instance->down() * moveSpeed);
		}

		// Rotation
		if (event.key.keysym.sym == SDLK_UP)
		{
			Camera::instance->rotate(glm::vec3(rotationSpeed, 0, 0));
		}
		if (event.key.keysym.sym == SDLK_DOWN)
		{
			Camera::instance->rotate(glm::vec3(-rotationSpeed, 0, 0));
		}
		if (event.key.keysym.sym == SDLK_LEFT)
		{
			Camera::instance->rotate(glm::vec3(0, 0, rotationSpeed));
		}
		if (event.key.keysym.sym == SDLK_RIGHT)
		{
			Camera::instance->rotate(glm::vec3(0, 0, -rotationSpeed));
		}

		// Toggle Fullscreen
		if (event.key.keysym.sym == SDLK_F11)
		{
			isFullscreen = !isFullscreen;
			SDL_SetWindowFullscreen(SDLDisplayer::window, Input::isFullscreen ? 1 : 0);
		}

		// Reset camera position and rotation
		if (event.key.keysym.sym == SDLK_y)
		{
			Camera::instance->getPos() = {0.5, 0, 0.5};
			Camera::instance->getRot() = {1, 0, 0, 0};
		}
	}
}
