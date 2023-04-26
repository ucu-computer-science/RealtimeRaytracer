#include "SDLDisplayer.h"
#include "Camera.h"
#include "Input.h"
#include "Matrix.h"
#include <iostream>

#include "BoundingBoxes.h"
#include "GraphicalObject.h"
#include "Scene.h"
#include "Canvas.h"

int SDLDisplayer::display(int width, int height)
{
	SDLDisplayer::width = width;
	SDLDisplayer::height = height;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	auto surface = SDL_GetWindowSurface(window);
	renderTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_BGRA32, SDL_TEXTUREACCESS_TARGET, width, height);
	//	renderTexture = SDL_CreateTextureFromSurface(renderer, surface);

	// Init BVH
	auto intersectables = std::vector<IBoundable*>(Scene::graphicalObjects.size());
	std::ranges::transform(Scene::graphicalObjects, intersectables.begin(), [](const GraphicalObject* obj) { return (IBoundable*)obj; });
	BVHNode::root = BVHNode::buildTree(intersectables, BVHNode::maxObjectsPerBox);

	loop();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}

void SDLDisplayer::loop()
{
	auto pixels = new uint32_t[height * width];
	memset(pixels, 0, height * width * sizeof(uint32_t));
	PixelMatrix pixelMatrix(pixels, width, height);

	bool quit = false;
	while (true)
	{
		while (SDL_PollEvent(&event))
		{
			Input::handleSDLEvent(event);

			if (event.type == SDL_QUIT)
			{
				quit = true;
				break;
			}
		}
		if (quit) break;

		Time::updateTime();
		Input::updateInput();
		onUpdate();

		Camera::instance->updatePixelMatrix(pixelMatrix);
		Canvas::mainCanvas->drawUI(&pixelMatrix);
		// Stats
		FPSCounter::updateFPSCounter();
		TriangleCounter::updateTriangleCounter();
		if (Input::isFocused)
			std::cout
				<< "FPS: " << FPSCounter::fps
				<< " Triangles: " << TriangleCounter::triangleCount
				<< " Graphical Objects: " << Scene::graphicalObjects.size()
				<< " Bounding Boxes: " << BVHNode::boxCount << '\n';

		SDL_UpdateTexture(renderTexture, nullptr, pixels, width * sizeof(uint32_t));
		SDL_RenderCopy(renderer, renderTexture, nullptr, nullptr);
		SDL_RenderPresent(renderer);
	}
}

void FPSCounter::updateFPSCounter()
{
	uint32_t currTime = SDL_GetTicks();
	if (currTime >= lastFrameTime + 200)
	{
		fps = (int)((float)frameCount / (float)(currTime - lastFrameTime) * 1000.0f);
		frameCount = 0;
		lastFrameTime = currTime;
	}
	frameCount++;
}

void TriangleCounter::updateTriangleCounter()
{
	triangleCount = 0;
	for (const auto& obj : Scene::graphicalObjects)
		triangleCount += (int)obj->cameraFacingTriangles.size();
}

void Time::updateTime()
{
	auto new_time = (float)SDL_GetTicks() / 1000.0f;
	deltaTime = new_time - time;
	time = new_time;
}
