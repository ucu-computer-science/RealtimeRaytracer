#include "Raytracer.h"

#include <iostream>
#include <SDL.h>

#include "BufferController.h"
#include "BoundingBoxes.h"
#include "Camera.h"
#include "GraphicalObject.h"
#include "Input.h"
#include "Light.h"
#include "Logger.h"
#include "MathExtensions.h"
#include "MyTime.h"
#include "ObjectParser.h"
#include "SDLHandler.h"
#include "Triangle.h"
#include "RaytracerShader.h"
#include "SceneParser.h"
#include "stb_image.h"


int main(int argv, char* args[])
{
	Raytracer::initialize(640 * 3, 360 * 3);

	Raytracer::loop();

	Raytracer::quit();
	return 0;
}

void Raytracer::initialize(int width, int height)
{
	Raytracer::width = width;
	Raytracer::height = height;

	SDLHandler::initialize(width, height);
	shader = new RaytracerShader("shaders/raytracer.vert", "shaders/raytracer.frag");
	shader->use();

	// SETTINGS
	shader->setInt("maxRayBounce", 5);
	shader->setFloat2("pixelSize", {width, height});

	onUpdate += Time::updateTime;
	onUpdate += Input::updateInput;
	onUpdate += Logger::updateFPSCounter;
	onUpdate += Logger::logStats;

	//initializeSkybox();
	initializeScene();
	BVHBuilder::initializeBVH();
	BufferController::initializeUniformBuffers();
}
//void Raytracer::initializeSkybox()
//{
//	std::string cubemapPaths[6] =
//	{
//		"textures/skybox/right.jpg",
//		"textures/skybox/left.jpg",
//		"textures/skybox/top.jpg",
//		"textures/skybox/bottom.jpg",
//		"textures/skybox/front.jpg",
//		"textures/skybox/back.jpg"
//	};
//
//	int width, height, nrChannels;
//	for (unsigned int i = 0; i < 6; i++)
//	{
//		unsigned char* data = stbi_load(cubemapPaths[i].c_str(), &width, &height, &nrChannels, 0);
//		mainShader->skybox->setFaceTexture(data, i, width, height);
//	}
//}
void Raytracer::initializeScene()
{
	auto camera = new Camera({0.305388, -9.574623, 3.030889}, 1, 0, {(float)width / (float)height, 1});
	camera->setRot({0.992115, 0.125332, 0.000000, 0.000004});
	//auto camera = new Camera({ 0, -50, 0 }, 1, 0, { (float)width / (float)height, 1 });
	camera->setBackgroundColor(Color::black());
	auto tex = Texture::defaultTex;

	//auto model = Model("models/skull.obj");
	//auto obj = new Mesh({0, 0, -9}, model.triangles);

	//new GlobalLight({0, -1, 0}, Color::white(), 1);

	auto model = Model("models/west.obj");
	auto obj = new Mesh({0, 0, 0}, model.triangles);
	obj->material = new Material(Color::white(), true, tex, 1, 0.3, 2000, 0);
	auto light = new AreaLight{{0.334557, 2, 14.720142}, {255 / 255.0f, 236 / 255.0f, 156 / 255.0f}, 1, FLT_MAX, {3, 3, 2}, {6, 6, 1}};

	//auto obj = new Cube({0, 0, 0}, 2, {{0, 0, 0}});
	//obj->material = new Material(Color::blue(), true, tex, 1, 0, 2000, 0);

	//auto obj1 = new Cube({5, 10, 0}, 2, {{0, 0, 0}});
	//obj1->material = new Material(Color::blue(), true, tex, 1, 0, 2000, 0);

	//auto obj2 = new Cube({0, 10, 5}, 2, {{0, 0, 0}});
	//obj2->material = new Material(Color::blue(), true, tex, 1, 0, 2000, 0);

	//auto obj3 = new Cube({5, 10, 5}, 2, {{0, 0, 0}});
	//obj3->material = new Material(Color::blue(), true, tex, 1, 0, 2000, 0);

	//auto obj4 = new Sphere({-2, 3, 0}, 2);
	//obj4->material = new Material(Color::skyblue(), true, tex, 1, 0, 2000, 0);

	//auto obj5 = new Sphere({4, 10, 0}, 2);
	//obj5->material = new Material(Color::skyblue(), true, tex, 1, 0, 2000, 0);

	//auto obj6 = new Plane({0, 0, -2}, {0, 0, 1});
	//obj6->material = new Material(Color::green(), true, tex, 1, 0, 2000, 0);


	//auto light = new AreaLight{{0, 0, 8}, {255 / 255.0f, 236 / 255.0f, 156 / 255.0f}, 1, 25, {0, 0, 0}, {1, 1, 1}};
	//auto square = new Square{{0, 0, 9.995f}, 5, {{-90 * DEG_TO_RAD, 0, 0}}};
	//square->material->color = {30.f, 30.f, 30.f};
	//auto plane1 = new Square{{-10, 0, 0}, 20, {{0, 0, -90 * DEG_TO_RAD}}};
	//auto plane2 = new Square{{10, 0, 0}, 20, {{0, 0, 90 * DEG_TO_RAD}}};
	//auto plane3 = new Square{{0, 10, 0}, 20, {{0, 0, 180 * DEG_TO_RAD}}};
	//auto plane4 = new Square{{0, 0, -10}, 20, {{90 * DEG_TO_RAD, 0, 0}}};
	//auto plane5 = new Square{{0, 0, 10}, 20, {{-90 * DEG_TO_RAD, 0, 0}}};
	//auto cube1 = new Cube{glm::vec3{4, -4, -6.7}, 6.6f, {{0 * DEG_TO_RAD, 0 * DEG_TO_RAD, -28 * DEG_TO_RAD}}};
	//auto sphere1 = new Sphere{{-4, 2, -5}, 5};

	//auto whiteWallMat = new Material(Color::white(), true, tex, 1, 0, 2000, 0);
	//plane1->material = new Material(Color::red(), true, tex, 1, 0, 2000, 0);
	//plane2->material = new Material(Color::green(), true, tex, 1, 0, 2000, 0);
	//plane3->material = whiteWallMat;
	//plane4->material = whiteWallMat;
	//plane5->material = whiteWallMat;

	//sphere1->material = new Material(Color::skyblue(), true, tex, 1, 0, 2000, 0.3f);
	//cube1->material = new Material(Color::skyblue(), true, tex, 1, 0, 2000, 0.3f);
}

void Raytracer::loop()
{
	while (true)
	{
		onUpdate();

		shader->use();
		glBindVertexArray(shader->vaoScreen->id);
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_CUBE_MAP, shader->skybox->id);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		SDL_GL_SwapWindow(SDLHandler::window);
		if (!SDLHandler::update())
			break;
	}
}



void Raytracer::quit()
{
	SDLHandler::quit();
	delete shader;
}
