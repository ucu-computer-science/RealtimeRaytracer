#include "Input.h"

#include "Camera.h"
#include "SDLHandler.h"
#include "glm/gtx/string_cast.hpp"
#include "MathExtensions.h"
#include "MyTime.h"

float defaultMoveSpeed = 15.0f;
float keyRotationSpeed = 90.0f;
float mouseRotationSpeed = 0.4f;

void Input::updateInput()
{
	if (!SDLHandler::windowFocused) return;

	auto moveSpeed = defaultMoveSpeed;
	auto& camera = Camera::instance;
	auto keyboardState = SDL_GetKeyboardState(nullptr);

	// Movement
	if (keyboardState[SDL_SCANCODE_LSHIFT])
		moveSpeed *= 4;
	else if (keyboardState[SDL_SCANCODE_LCTRL])
		moveSpeed /= 4;

	if (keyboardState[SDL_SCANCODE_W])
	{
		camera->translate(camera->forward() * moveSpeed * Time::clampedDeltaTime);
	}
	if (keyboardState[SDL_SCANCODE_S])
	{
		camera->translate(camera->backward() * moveSpeed * Time::clampedDeltaTime);
	}
	if (keyboardState[SDL_SCANCODE_A])
	{
		camera->translate(camera->left() * moveSpeed * Time::clampedDeltaTime);
	}
	if (keyboardState[SDL_SCANCODE_D])
	{
		camera->translate(camera->right() * moveSpeed * Time::clampedDeltaTime);
	}
	if (keyboardState[SDL_SCANCODE_Q])
	{
		camera->translate(camera->up() * moveSpeed * Time::clampedDeltaTime);
	}
	if (keyboardState[SDL_SCANCODE_E])
	{
		camera->translate(camera->down() * moveSpeed * Time::clampedDeltaTime);
	}

	// Rotation
	if (keyboardState[SDL_SCANCODE_UP])
	{
		auto rot = eulerAngles(camera->getRot()) * RAD_TO_DEG;
		auto newRot = glm::vec3(glm::clamp(rot.x + keyRotationSpeed * Time::deltaTime, -90.0f, 90.0f), rot.y, rot.z);
		camera->setRot({newRot * DEG_TO_RAD});
	}
	if (keyboardState[SDL_SCANCODE_DOWN])
	{
		auto rot = eulerAngles(camera->getRot()) * RAD_TO_DEG;
		auto newRot = glm::vec3(glm::clamp(rot.x - keyRotationSpeed * Time::deltaTime, -90.0f, 90.0f), rot.y, rot.z);
		camera->setRot({newRot * DEG_TO_RAD});
	}
	if (keyboardState[SDL_SCANCODE_LEFT])
	{
		camera->rotate({0, 0, keyRotationSpeed * Time::clampedDeltaTime});
	}
	if (keyboardState[SDL_SCANCODE_RIGHT])
	{
		camera->rotate({0, 0, -keyRotationSpeed * Time::clampedDeltaTime});
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
			SDLHandler::isFullscreen = !SDLHandler::isFullscreen;
			SDL_SetWindowFullscreen(SDLHandler::window, SDLHandler::isFullscreen ? 1 : 0);
		}
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			SDLHandler::windowFocused = !SDLHandler::windowFocused;
			if (SDLHandler::windowFocused)
				SDL_SetRelativeMouseMode(SDL_TRUE);
			else
				SDL_SetRelativeMouseMode(SDL_FALSE);
		}

		/*if (event.key.keysym.sym == SDLK_SPACE)
		{
			auto dir = Camera::instance->getScreenCenter() - Camera::instance->getPos();
			auto ray = Ray(Camera::instance->getPos(), dir);
			if (Physics::castRay(ray))
			{
				auto interPoint = ray.interPoint;
				interPoint.x = (int)(interPoint.x / 2) * 2;
				interPoint.y = (int)(interPoint.y / 2) * 2;
				interPoint.z = (int)(interPoint.z / 2) * 2;
				auto obj1 = new ImportedGraphicalObject("../../models/cube.obj", interPoint, {{0, 0, 0}});
				auto tex = std::make_shared<Texture>();
				obj1->setMaterial(Material(Color::white(), tex, true, 1, 0.5f, 2000, 0));

				auto intersectables = std::vector<IBoundable*>(Scene::graphicalObjects.size());
				std::ranges::transform(Scene::graphicalObjects, intersectables.begin(), [](const GraphicalObject* obj) { return (IBoundable*)obj; });
				BVHNode::root = BVHNode::buildTree(intersectables, BVHNode::maxObjectsPerBox);
			}
		}*/
	}

	if (event.type == SDL_MOUSEMOTION && SDLHandler::windowFocused)
	{
		auto dx = (float)event.motion.xrel;
		auto dy = (float)event.motion.yrel;

		auto& camera = Camera::instance;
		auto rot = eulerAngles(camera->getRot()) * RAD_TO_DEG;

		auto newX = glm::clamp(rot.x - dy * mouseRotationSpeed, -90.0f, 90.0f);
		auto newY = rot.y;
		auto newZ = rot.z - dx * mouseRotationSpeed;

		auto newRot = glm::vec3(newX, newY, newZ);
		camera->setRot({newRot * DEG_TO_RAD});
	}
}
