#include "Logger.h"

#include <iostream>

#include "BoundingBoxes.h"
#include "Scene.h"
#include "SDLHandler.h"

void Logger::updateFPSCounter()
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

void Logger::logStats()
{
	if (!SDLHandler::windowFocused) return;

	std::cout
		<< "FPS: " << fps
		<< " Triangles: " << Scene::triangles.size()
		<< " Graphical Objects: " << Scene::graphicalObjects.size()
		<< " Bounding Boxes: " << BVHBuilder::nodes.size()<< '\n';
}
