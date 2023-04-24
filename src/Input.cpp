#include "Input.h"

#include "Camera.h"
#include "SDLDisplayer.h"
#include "glm/gtx/string_cast.hpp"
#include "mathExtensions.h"

bool Input::isFullscreen = false;
bool Input::isFocused = true;
float Input::defaultMoveSpeed = 40.0f;
float Input::rotationSpeed = 10.0f;

void Input::updateInput()
{
	if (!isFocused) return;

	auto moveSpeed = defaultMoveSpeed;
	auto& camera = Camera::instance;
	keyboardState = SDL_GetKeyboardState(nullptr);

	// Movement
	if (keyboardState[SDL_SCANCODE_LSHIFT])
		moveSpeed *= 4;
	else if (keyboardState[SDL_SCANCODE_LCTRL])
		moveSpeed /= 4;

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
		auto newRot = glm::vec3(glm::clamp(rot.x + 9 * rotationSpeed * Time::deltaTime, -90.0f, 90.0f), rot.y, rot.z);
		camera->setRot({newRot * DEG_TO_RAD});
	}
	if (keyboardState[SDL_SCANCODE_DOWN])
	{
		auto rot = eulerAngles(camera->getRot()) * RAD_TO_DEG;
		auto newRot = glm::vec3(glm::clamp(rot.x - 9 * rotationSpeed * Time::deltaTime, -90.0f, 90.0f), rot.y, rot.z);
		camera->setRot({newRot * DEG_TO_RAD});
	}
	if (keyboardState[SDL_SCANCODE_LEFT])
	{
		camera->rotate({0, 0, 9 * rotationSpeed * Time::deltaTime});
	}
	if (keyboardState[SDL_SCANCODE_RIGHT])
	{
		camera->rotate({0, 0, 9 * -rotationSpeed * Time::deltaTime});
	}

	// Reset camera position and rotation
	if (keyboardState[SDL_SCANCODE_Y])
	{
		camera->getPos() = {0.5, 0, 0.5};
		camera->getRot() = {1, 0, 0, 0};
	}
}
void Input::handleSDLEvent(SDL_Event event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_F11)
		{
			isFullscreen = !isFullscreen;
			SDL_SetWindowFullscreen(SDLDisplayer::window, isFullscreen ? 1 : 0);
		}
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			isFocused = !isFocused;
			if (isFocused)
				SDL_SetRelativeMouseMode(SDL_TRUE);
			else
				SDL_SetRelativeMouseMode(SDL_FALSE);
		}
	}

	if (event.type == SDL_MOUSEMOTION && isFocused)
	{
		auto dx = (float)event.motion.xrel;
		auto dy = (float)event.motion.yrel;

		auto& camera = Camera::instance;
		auto rot = glm::eulerAngles(camera->getRot()) * RAD_TO_DEG;

		auto newX = glm::clamp(rot.x - dy * rotationSpeed * Time::deltaTime, -90.0f, 90.0f);
		auto newY = rot.y;
		auto newZ = rot.z - dx * rotationSpeed * Time::deltaTime;

		auto newRot = glm::vec3(newX, newY, newZ);
		camera->setRot({newRot * DEG_TO_RAD});
	}
}
