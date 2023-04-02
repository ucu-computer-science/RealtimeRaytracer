#include "Camera.h"
#include "Input.h"

#include <iostream>

#include "mathExtensions.h"
#include "SDLDisplayer.h"
#include "glm/gtx/string_cast.hpp"

bool Input::isFullscreen = false;
float Input::moveSpeed = 0.4f;
float Input::rotationSpeed = 15.0f;

void Input::updateInput(const SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		auto camera = Camera::instance;

		// Movement
		if (event.key.keysym.sym == SDLK_w)
		{
			camera->translate(camera->forward() * moveSpeed);
		}
		if (event.key.keysym.sym == SDLK_s)
		{
			camera->translate(camera->backward() * moveSpeed);
		}
		if (event.key.keysym.sym == SDLK_a)
		{
			camera->translate(camera->left() * moveSpeed);
		}
		if (event.key.keysym.sym == SDLK_d)
		{
			camera->translate(camera->right() * moveSpeed);
		}
		if (event.key.keysym.sym == SDLK_q)
		{
			camera->translate(camera->up() * moveSpeed);
		}
		if (event.key.keysym.sym == SDLK_e)
		{
			camera->translate(camera->down() * moveSpeed);
		}

		// Rotation
		if (event.key.keysym.sym == SDLK_UP)
		{
			auto rot = eulerAngles(camera->getRot()) * RAD_TO_DEG;
			auto newRot = glm::vec3(glm::clamp(rot.x + rotationSpeed, -90.0f, 90.0f), rot.y, rot.z);
			camera->setRot({newRot * DEG_TO_RAD});
		}
		if (event.key.keysym.sym == SDLK_DOWN)
		{
			auto rot = eulerAngles(camera->getRot()) * RAD_TO_DEG;
			auto newRot = glm::vec3(glm::clamp(rot.x - rotationSpeed, -90.0f, 90.0f), rot.y, rot.z);
			camera->setRot({newRot * DEG_TO_RAD});
		}
		if (event.key.keysym.sym == SDLK_LEFT)
		{
			camera->rotate({0, 0, rotationSpeed});
		}
		if (event.key.keysym.sym == SDLK_RIGHT)
		{
			camera->rotate({0, 0, -rotationSpeed});
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
			camera->getPos() = {0.5, 0, 0.5};
			camera->getRot() = {1, 0, 0, 0};
		}
	}
}
