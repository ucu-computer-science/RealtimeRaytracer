#include "SDLHandler.h"

#include "glad.h"
#include "Input.h"

void SDLHandler::initialize(int width, int height)
{
	SDL_GL_LoadLibrary(nullptr);

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	window = SDL_CreateWindow("Raytracer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
	context = SDL_GL_CreateContext(window);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	gladLoadGLLoader(SDL_GL_GetProcAddress);
	//SDL_GL_SetSwapInterval(1);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	glViewport(0, 0, w, h);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

}
bool SDLHandler::update()
{
	while (SDL_PollEvent(&event))
	{
		Input::handleSDLEvent(event);

		if (event.type == SDL_QUIT)
			return false;
	}
	return true;
}

//void SDLDisplayer::loop()
//{
//	auto pixels = new uint32_t[height * width];
//	memset(pixels, 0, height * width * sizeof(uint32_t));
//	PixelMatrix pixelMatrix(pixels, width, height);
//
//	bool quit = false;
//	while (true)
//	{
//		while (SDL_PollEvent(&event))
//		{
//			Input::handleSDLEvent(event);
//
//			if (event.type == SDL_QUIT)
//			{
//				quit = true;
//				break;
//			}
//		}
//		if (quit) break;
//
//		Time::updateTime();
//		Input::updateInput();
//		onUpdate();
//
//		Camera::instance->updatePixelMatrix(pixelMatrix);
//		Canvas::mainCanvas->drawUI(&pixelMatrix);
//		 //Stats
//		FPSCounter::updateFPSCounter();
//		TriangleCounter::updateTriangleCounter();
//		if (Input::isFocused)
//			std::cout
//				<< "FPS: " << FPSCounter::fps
//				<< " Triangles: " << TriangleCounter::triangleCount
//				<< " Graphical Objects: " << Scene::graphicalObjects.size()
//				<< " Bounding Boxes: " << BVHNode::boxCount << '\n';
//
//		SDL_UpdateTexture(renderTexture, nullptr, pixels, width * sizeof(uint32_t));
//		SDL_RenderCopy(renderer, renderTexture, nullptr, nullptr);
//		SDL_RenderPresent(renderer);
//	}
//}

void SDLHandler::quit()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
