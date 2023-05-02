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
#include "SDLHandler.h"
#include "Triangle.h"
#include "RaytracerShader.h"
#include "SceneParser.h"


int main(int argv, char* args[])
{
	Raytracer::initialize(640 * 2, 360 * 2);

	Raytracer::loop();

	Raytracer::quit();
	return 0;
}

void Raytracer::initialize(int width, int height)
{
	Raytracer::width = width;
	Raytracer::height = height;

	SDLHandler::initialize(width, height);
	mainShader = new RaytracerShader("../../shaders/raytracer.vert", "../../shaders/raytracer.frag");
	mainShader->use();
	mainShader->setFloat2("pixelSize", {width, height});

	onUpdate += Time::updateTime;
	onUpdate += Input::updateInput;
	onUpdate += Logger::updateFPSCounter;
	onUpdate += Logger::logStats;

	initializeScene();

	initializeScreenVertexBuffer();
	BVHBuilder::initializeBVH();
	BufferController::initializeUniformBuffers();
}

void Raytracer::initializeScene()
{
	auto camera = new Camera({0.0f, -30.0f, 0.5f}, 1, 0, {(float)width / (float)height, 1});
	camera->setBackgroundColor(Color::black());
	auto tex = std::make_shared<Texture>();

	//auto obj = new ImportedGraphicalObject("../../models/man.obj");
	//obj->material.lit = false;


	//auto light = new PointLight({1, 0, 5}, Color::white(), 1, FLT_MAX);

	//auto obj = new Cube({0, 0, 0}, {{0, 0, 0}}, 2);
	//obj->setMaterial(Material(Color::blue(), tex, true, 1, 0, 2000, 0));

	//auto obj1 = new Cube({5, 10, 0}, {{0, 0, 0}}, 2);
	//obj1->setMaterial(Material(Color::blue(), tex, true, 1, 0, 2000, 0));

	//auto obj2 = new Cube({0, 10, 5}, {{0, 0, 0}}, 2);
	//obj2->setMaterial(Material(Color::blue(), tex, true, 1, 0, 2000, 0));

	//auto obj3 = new Cube({5, 10, 5}, {{0, 0, 0}}, 2);
	//obj3->setMaterial(Material(Color::blue(), tex, true, 1, 0, 2000, 0));

	//auto obj4 = new Sphere({-2, 3, 0}, 2);
	//obj4->setMaterial(Material(Color::red(), tex, true, 1, 0, 2000, 0));

	//auto obj5 = new Sphere({4, 10, 0}, 2);
	//obj5->setMaterial(Material(Color::red(), tex, true, 1, 0, 2000, 0));

	//auto obj6 = new Plane({0, 0, -2}, {0, 0, 1});
	//obj6->setMaterial(Material(Color::green(), tex, true, 1, 0, 2000, 0));


	auto light = new AreaLight{{0, 0, 8}, {255 / 255.0f, 236 / 255.0f, 156 / 255.0f}, 1, 25, {0, 0, 0}, {1, 1, 1}};
	auto square = new Square{{0, 0, 9.995f}, 5, {{-90 * DEG_TO_RAD, 0, 0}}};
	square->material.color = {30.f, 30.f, 30.f};
	auto plane1 = new Square{{-10, 0, 0}, 20, {{0, 0, -90 * DEG_TO_RAD}}, {Color::red()}};
	auto plane2 = new Square{{10, 0, 0}, 20, {{0, 0, 90 * DEG_TO_RAD}}, Color::green()};
	auto plane3 = new Square{{0, 10, 0}, 20, {{0, 0, 180 * DEG_TO_RAD}}, Color::white()};
	auto plane4 = new Square{{0, 0, -10}, 20, {{90 * DEG_TO_RAD, 0, 0}}, Color::white()};
	auto plane5 = new Square{{0, 0, 10}, 20, {{-90 * DEG_TO_RAD, 0, 0}}, Color::white()};
	auto cube1 = new Cube{glm::vec3{4, -4, -6.7}, 6.6f, {{0 * DEG_TO_RAD, 0 * DEG_TO_RAD, -28 * DEG_TO_RAD}}};
	auto sphere1 = new Sphere{{-4, 2, -5}, 5, Color{100.f / 100.f, 49.8f / 100.f, 31.4f / 100.f}};
	sphere1->material.color = Color::skyblue();
	sphere1->material.reflection = 0.3f;
	cube1->material.color = Color::skyblue();
	cube1->material.reflection = 0.3f;
}

void Raytracer::initializeScreenVertexBuffer()
{
	float vertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
	};
	unsigned int indices[] = {
		0, 1, 2,
		2, 1, 3,
	};

	glGenVertexArrays(1, &screenVertexArray);
	glBindVertexArray(screenVertexArray);

	unsigned int vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int elementBuffer;
	glGenBuffers(1, &elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
	glEnableVertexAttribArray(0);
}



void Raytracer::loop()
{
	while (true)
	{
		onUpdate();

		mainShader->use();
		glBindVertexArray(screenVertexArray);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		if (!SDLHandler::update())
			break;
	}
}



void Raytracer::quit()
{
	SDLHandler::quit();
	delete mainShader;
}
