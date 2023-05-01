#include "Raytracer.h"

#include <iostream>
#include <glm/glm.hpp>
#include <SDL.h>

#include "Camera.h"
#include "Canvas.h"
#include "GraphicalObject.h"
#include "Input.h"
#include "Light.h"
#include "Logger.h"
#include "MathExtensions.h"
#include "MyTime.h"
#include "Scene.h"
#include "SDLHandler.h"
#include "Triangle.h"
#include "RaytracerShader.h"


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

	initializeScreenVertexBuffer();
	initializeScene();
	initializeUniformBuffers();
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
void Raytracer::initializeScene()
{
	auto camera = new Camera({0.0f, -30.0f, 0.5f}, 1, 0, {(float)width / (float)height, 1});
	camera->setBackgroundColor(Color::black());
	auto defaultTexture = std::make_shared<Texture>();
	/*auto light = new PointLight({1, 0, 5}, Color::white(), 1, FLT_MAX);

	auto obj = new Cube({0, 10, 0}, {{0, 0, 0}}, 2);
	obj->setMaterial(Material(Color::blue(), tex, true, 1, 0, 2000, 0.5));

	auto obj1 = new Cube({5, 10, 0}, {{0, 0, 0}}, 2);
	obj1->setMaterial(Material(Color::blue(), tex, true, 1, 0, 2000, 0.5));

	auto obj2 = new Cube({0, 10, 5}, {{0, 0, 0}}, 2);
	obj2->setMaterial(Material(Color::blue(), tex, true, 1, 0, 2000, 0.5));

	auto obj3 = new Cube({5, 10, 5}, {{0, 0, 0}}, 2);
	obj3->setMaterial(Material(Color::blue(), tex, true, 1, 0, 2000, 0.5));

	auto obj4 = new Sphere({-2, 3, 0}, 2);
	obj4->setMaterial(Material(Color::red(), tex, true, 1, 0, 2000, 0.5));

	auto obj5 = new Sphere({4, 10, 0}, 2);
	obj5->setMaterial(Material(Color::red(), tex, true, 1, 0, 2000, 0.5));

	auto obj6 = new Plane({0, 0, 0}, {0, 0, 1});
	obj6->setMaterial(Material(Color::green(), tex, true, 1, 0, 2000, 0.5));*/


	auto light = new AreaLight{{0, 0, 8}, {255 / 255.0f, 236 / 255.0f, 156 / 255.0f}, 1, 25, {4, 4, 0}, {15, 15, 1}};
	auto square = new Square{{0, 0, 9.995f}, {{-90 * DEG_TO_RAD, 0, 0}}, 5};
	square->material.color = {3.f, 3.f, 3.f};
	auto plane1 = new Square{{-10, 0, 0}, {{0, 0, -90 * DEG_TO_RAD}}, 20, Color::red()};
	auto plane2 = new Square{{10, 0, 0}, {{0, 0, 90 * DEG_TO_RAD}}, 20, Color::green()};
	auto plane3 = new Square{{0, 10, 0}, {{0, 0, 180 * DEG_TO_RAD}}, 20, Color::white()};
	auto plane4 = new Square{{0, 0, -10}, {{90 * DEG_TO_RAD, 0, 0}}, 20, Color::white()};
	auto plane5 = new Square{{0, 0, 10}, {{-90 * DEG_TO_RAD, 0, 0}}, 20, Color::white()};
	auto cube1 = new Cube{glm::vec3{4, -4, -6.7}, {{0 * DEG_TO_RAD, 0 * DEG_TO_RAD, -28 * DEG_TO_RAD}}, 6.6f};
	auto sphere1 = new Sphere{{-4, 2, -5}, 5, Color{100.f / 100.f, 49.8f / 100.f, 31.4f / 100.f}};
	sphere1->material.color = Color::skyblue();
	sphere1->material.reflection = 0.3f;
	cube1->material.color = Color::skyblue();
	cube1->material.reflection = 0.3f;
}
void Raytracer::initializeUniformBuffers()
{
	const auto& lights = Scene::lights;
	int ALIGN = RaytracerShader::lightAlign;
	auto lightData = new float[lights.size() * ALIGN];
	for (int i = 0; i < lights.size(); ++i)
	{
		lightData[i * ALIGN + 4] = lights[i]->getPos().x;
		lightData[i * ALIGN + 5] = lights[i]->getPos().y;
		lightData[i * ALIGN + 6] = lights[i]->getPos().z;
		lightData[i * ALIGN + 8] = lights[i]->getColor().r();
		lightData[i * ALIGN + 9] = lights[i]->getColor().g();
		lightData[i * ALIGN + 10] = lights[i]->getColor().b();
		lightData[i * ALIGN + 12] = lights[i]->getIntensity();

		if (dynamic_cast<GlobalLight*>(lights[i]) != nullptr)
		{
			auto globalLight = (GlobalLight*)lights[i];
			lightData[i * ALIGN + 0] = 0;
			lightData[i * ALIGN + 13] = globalLight->direction.x;
			lightData[i * ALIGN + 14] = globalLight->direction.y;
			lightData[i * ALIGN + 15] = globalLight->direction.z;
		}
		else if (dynamic_cast<PointLight*>(lights[i]))
		{
			auto pointLight = (PointLight*)lights[i];
			lightData[i * ALIGN + 0] = 1;
			lightData[i * ALIGN + 13] = pointLight->distance;
		}
		else if (dynamic_cast<AreaLight*>(lights[i]))
		{
			auto pointLight = (AreaLight*)lights[i];
			lightData[i * ALIGN + 0] = 2;
			lightData[i * ALIGN + 13] = pointLight->size.x;
			lightData[i * ALIGN + 14] = pointLight->size.y;
			lightData[i * ALIGN + 15] = pointLight->size.z;
			lightData[i * ALIGN + 16] = pointLight->distance;
			lightData[i * ALIGN + 17] = pointLight->pointSize.x;
			lightData[i * ALIGN + 18] = pointLight->pointSize.y;
			lightData[i * ALIGN + 19] = pointLight->pointSize.z;
		}
	}
	mainShader->setLightsUBO(lightData, lights.size());
	delete[] lightData;

	ALIGN = RaytracerShader::objectAlign;
	const auto& objects = Scene::graphicalObjects;
	auto objectData = new float[objects.size() * ALIGN];
	auto triangleCount = 0;
	for (int i = 0; i < objects.size(); ++i)
	{
		objectData[i * ALIGN + 4] = objects[i]->getPos().x;
		objectData[i * ALIGN + 5] = objects[i]->getPos().y;
		objectData[i * ALIGN + 6] = objects[i]->getPos().z;

		const auto& mat = objects[i]->material;
		objectData[i * ALIGN + 8] = mat.color.r();
		objectData[i * ALIGN + 9] = mat.color.g();
		objectData[i * ALIGN + 10] = mat.color.b();
		objectData[i * ALIGN + 12] = mat.lit;
		objectData[i * ALIGN + 16] = mat.diffuseCoeff;
		objectData[i * ALIGN + 17] = mat.specularCoeff;
		objectData[i * ALIGN + 18] = mat.specularDegree;
		objectData[i * ALIGN + 19] = mat.reflection;

		if (dynamic_cast<Sphere*>(objects[i]) != nullptr)
		{
			auto sphere = (Sphere*)objects[i];
			objectData[i * ALIGN + 0] = 1;
			objectData[i * ALIGN + 20] = sphere->radius * sphere->radius;
		}
		else if (dynamic_cast<Plane*>(objects[i]) != nullptr)
		{
			auto plane = (Plane*)objects[i];
			objectData[i * ALIGN + 0] = 2;
			objectData[i * ALIGN + 20] = plane->normal.x;
			objectData[i * ALIGN + 21] = plane->normal.y;
			objectData[i * ALIGN + 22] = plane->normal.z;
		}
		else
		{
			objectData[i * ALIGN + 0] = 0;
			objectData[i * ALIGN + 20] = (float)triangleCount;
			objectData[i * ALIGN + 21] = (float)triangleCount + (float)objects[i]->triangles.size();
			triangleCount += objects[i]->triangles.size();
		}
	}
	mainShader->setObjectsUBO(objectData, objects.size());
	delete[] objectData;

	ALIGN = RaytracerShader::triangleAlign;
	auto triangleVertexData = new float[triangleCount * ALIGN];
	int filledTriangleCount = 0;
	for (int i = 0; i < objects.size(); i++)
	{
		for (const auto& triangle : objects[i]->triangles)
		{
			for (int k = 0; k < 3; ++k)
			{
				auto globalPos = triangle->globalVertexPositions[k];
				triangleVertexData[filledTriangleCount * ALIGN + k * 12 + 0] = globalPos.x;
				triangleVertexData[filledTriangleCount * ALIGN + k * 12 + 1] = globalPos.y;
				triangleVertexData[filledTriangleCount * ALIGN + k * 12 + 2] = globalPos.z;

				const auto& v = triangle->vertices[k];
				triangleVertexData[filledTriangleCount * ALIGN + k * 12 + 4] = v.uvPos.x;
				triangleVertexData[filledTriangleCount * ALIGN + k * 12 + 5] = v.uvPos.y;

				auto normal = triangle->globalVertexNormals[k];
				triangleVertexData[filledTriangleCount * ALIGN + k * 12 + 8] = normal.x;
				triangleVertexData[filledTriangleCount * ALIGN + k * 12 + 9] = normal.y;
				triangleVertexData[filledTriangleCount * ALIGN + k * 12 + 10] = normal.z;
			}
			triangleVertexData[filledTriangleCount * ALIGN + 36] = i;
			triangleVertexData[filledTriangleCount * ALIGN + 40] = triangle->row1.x;
			triangleVertexData[filledTriangleCount * ALIGN + 41] = triangle->row1.y;
			triangleVertexData[filledTriangleCount * ALIGN + 42] = triangle->row1.z;
			triangleVertexData[filledTriangleCount * ALIGN + 43] = triangle->row1Val;
			triangleVertexData[filledTriangleCount * ALIGN + 44] = triangle->row2.x;
			triangleVertexData[filledTriangleCount * ALIGN + 45] = triangle->row2.y;
			triangleVertexData[filledTriangleCount * ALIGN + 46] = triangle->row2.z;
			triangleVertexData[filledTriangleCount * ALIGN + 47] = triangle->row2Val;
			triangleVertexData[filledTriangleCount * ALIGN + 48] = triangle->row3.x;
			triangleVertexData[filledTriangleCount * ALIGN + 49] = triangle->row3.y;
			triangleVertexData[filledTriangleCount * ALIGN + 50] = triangle->row3.z;
			triangleVertexData[filledTriangleCount * ALIGN + 51] = triangle->row3Val;
			filledTriangleCount++;
		}
	}
	mainShader->setTrianglesUBO(triangleVertexData, filledTriangleCount);
	delete[] triangleVertexData;
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
