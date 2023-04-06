#include "Camera.h"
#include "Input.h"
#include "mathExtensions.h"
#include "SDLDisplayer.h"
#include "glm/gtx/string_cast.hpp"

bool Input::isFullscreen = false;
float Input::moveSpeed = 40.0f;
float Input::rotationSpeed = 90.0f;

void Input::updateInput()
{
	auto camera = Camera::instance;
	keyboardState = SDL_GetKeyboardState(nullptr);

	// Movement
	if (keyboardState[SDL_SCANCODE_W])
	{
		camera->translate(camera->forward() * moveSpeed * Time::deltaTime);
	}
	if (keyboardState[SDL_SCANCODE_S])
	{
		camera->translate(camera->backward() * moveSpeed * Time::deltaTime);
	}
	if (keyboardState[SDL_SCANCODE_A])
	{
		camera->translate(camera->left() * moveSpeed * Time::deltaTime);
	}
	if (keyboardState[SDL_SCANCODE_D])
	{
		camera->translate(camera->right() * moveSpeed * Time::deltaTime);
	}
	if (keyboardState[SDL_SCANCODE_Q])
	{
		camera->translate(camera->up() * moveSpeed * Time::deltaTime);
	}
	if (keyboardState[SDL_SCANCODE_E])
	{
		camera->translate(camera->down() * moveSpeed * Time::deltaTime);
	}

	// Rotation
	if (keyboardState[SDL_SCANCODE_UP])
	{
		auto rot = eulerAngles(camera->getRot()) * RAD_TO_DEG;
		auto newRot = glm::vec3(glm::clamp(rot.x + rotationSpeed * Time::deltaTime, -90.0f, 90.0f), rot.y, rot.z);
		camera->setRot({newRot * DEG_TO_RAD});
	}
	if (keyboardState[SDL_SCANCODE_DOWN])
	{
		auto rot = eulerAngles(camera->getRot()) * RAD_TO_DEG;
		auto newRot = glm::vec3(glm::clamp(rot.x - rotationSpeed * Time::deltaTime, -90.0f, 90.0f), rot.y, rot.z);
		camera->setRot({newRot * DEG_TO_RAD});
	}
	if (keyboardState[SDL_SCANCODE_LEFT])
	{
		camera->rotate({0, 0, rotationSpeed * Time::deltaTime});
	}
	if (keyboardState[SDL_SCANCODE_RIGHT])
	{
		camera->rotate({0, 0, -rotationSpeed * Time::deltaTime});
	}

	// Toggle Fullscreen
	if (SDLDisplayer::event.key.keysym.sym == SDLK_F11)
	{
		isFullscreen = !isFullscreen;
		SDL_SetWindowFullscreen(SDLDisplayer::window, Input::isFullscreen ? 1 : 0);
	}

	// Reset camera position and rotation
	if (keyboardState[SDLK_y])
	{
		camera->getPos() = {0.5, 0, 0.5};
		camera->getRot() = {1, 0, 0, 0};
	}
}
