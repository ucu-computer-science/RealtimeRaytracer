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


//#define ROW_BY_ROW


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
void museumScene()
{
	auto camera = new Camera({9.092605, -4.376354, 2.479673}, 1, 0, glm::vec2((float)Raytracer::width / (float)Raytracer::height, 1));
	camera->setRot({0.836809, 0.055576, 0.036094, 0.543469});
	camera->setBackgroundColor(Color::black());
	auto tex = Texture::defaultTex;

	auto model = Model("models/museum1.obj");
	auto obj = new Mesh({0, 0, 0}, model.triangles);
	obj->material = new Material(Color::white(), true, tex, 1, 0.2, 2000, 0);
	auto light = new AreaLight{{-5.566183, -0.194355, 14.792341}, {255 / 255.0f, 255 / 255.0f, 255.0 / 255.0f}, 1.3f, FLT_MAX, {3, 3, 2}, {6, 6, 1}};
}
void churchScene()
{
	auto camera = new Camera({0.305388, -9.574623, 3.030889}, 1, 0, glm::vec2((float)Raytracer::width / (float)Raytracer::height, 1));
	camera->setRot({0.992115, 0.125332, 0.000000, 0.000004});
	camera->setBackgroundColor(Color::black());
	auto tex = Texture::defaultTex;

	auto model = Model("models/west.obj");
	auto obj = new Mesh({0, 0, 0}, model.triangles);
	obj->material = new Material(Color::white(), true, tex, 1, 0.2, 2000, 0);
	auto light = new AreaLight{{0.334557, 2, 14.720142}, {1.0f, 1.0f, 1.0f}, 1, FLT_MAX, {3, 3, 2}, {7, 7, 1}};
}
void redGreenRoom()
{
	auto camera = new Camera({0, -30, 0}, 1, 0, glm::vec2((float)Raytracer::width / (float)Raytracer::height, 1));

	auto tex = Texture::defaultTex;

	auto light = new AreaLight{{0, 0, 8}, {255 / 255.0f, 236 / 255.0f, 156 / 255.0f}, 1, 25, {0, 0, 0}, {1, 1, 1}};
	auto square = new Square{{0, 0, 9.995f}, 5, {{-90 * DEG_TO_RAD, 0, 0}}};
	square->material->color = {300.f, 300.f, 300.f};
	auto plane1 = new Square{{-10, 0, 0}, 20, {{0, 0, -90 * DEG_TO_RAD}}};
	auto plane2 = new Square{{10, 0, 0}, 20, {{0, 0, 90 * DEG_TO_RAD}}};
	auto plane3 = new Square{{0, 10, 0}, 20, {{0, 0, 180 * DEG_TO_RAD}}};
	auto plane4 = new Square{{0, 0, -10}, 20, {{90 * DEG_TO_RAD, 0, 0}}};
	auto plane5 = new Square{{0, 0, 10}, 20, {{-90 * DEG_TO_RAD, 0, 0}}};
	auto cube1 = new Cube{glm::vec3{4, -4, -6.7}, 6.6f, {{0 * DEG_TO_RAD, 0 * DEG_TO_RAD, -28 * DEG_TO_RAD}}};
	auto sphere1 = new Sphere{{-4, 2, -5}, 5};

	auto whiteWallMat = new Material(Color::white(), true, tex, 1, 0, 2000, 0);
	plane1->material = new Material(Color::red(), true, tex, 1, 0, 2000, 0);
	plane2->material = new Material(Color::green(), true, tex, 1, 0, 2000, 0);
	plane3->material = whiteWallMat;
	plane4->material = whiteWallMat;
	plane5->material = whiteWallMat;

	sphere1->material = new Material(Color::skyblue(), true, tex, 1, 0, 2000, 0.3f);
	cube1->material = new Material(Color::skyblue(), true, tex, 1, 0, 2000, 0.3f);
}
void minecraftHouseScene()
{
	auto camera = new Camera({38.405102, 35.592041, 7.974061}, 1, 0, glm::vec2((float)Raytracer::width / (float)Raytracer::height, 1));
	camera->setRot({0.387786, {-0.047615, -0.112185, 0.913657}});
	camera->setBackgroundColor({0.1f, 0.1f, 0.1f});
	auto tex = Texture::defaultTex;

	auto model = Model("models/minecraft.obj");
	auto obj = new Mesh({0, 0, 0}, model.triangles, {{90 * DEG_TO_RAD, 0, 0}});
	obj->material = new Material(Color::white(), true, tex, 1, 0.2, 2000, 0);
	auto light = new AreaLight{{25, 25, 15}, {1.0f, 1.0f, 1.0f}, 1, FLT_MAX, {5, 5, 5}, {6, 6, 6}};
}
void kokuraScene()
{
	auto camera = new Camera({177.245255, 173.638443, 35.038555}, 1, 0, glm::vec2((float)Raytracer::width / (float)Raytracer::height, 1));
	camera->setRot({0.380992, {0.006647, 0.016129, 0.924414}});
	camera->setBackgroundColor({0.1f, 0.1f, 0.1f});
	auto tex = Texture::defaultTex;

	auto model = Model("models/kokura.obj");
	auto obj = new Mesh({0, 0, 0}, model.triangles, {{0, 0, 0}});
	obj->material = new Material(Color::white(), false, tex, 1, 0.2, 2000, 0);
	auto light = new AreaLight{{177.245255, 173.638443, 100.038555}, {1.0f, 1.0f, 1.0f}, 1, FLT_MAX, {5, 5, 5}, {6, 6, 1}};
}

void Raytracer::initializeScene()
{
	redGreenRoom();
}

void Raytracer::initializeFBO(Shader*& screenShader, unsigned& fbo, unsigned& renderTexture)
{
	screenShader = new Shader("shaders/screen.vert", "shaders/screen.frag");
	screenShader->use();
	screenShader->setInt("width", width);
	screenShader->setInt("height", height);

	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glGenTextures(1, &renderTexture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, renderTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderTexture, 0);

	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	screenShader->use();
	glUniform1i(glGetUniformLocation(screenShader->id, "screenTexture"), 1);
}


void Raytracer::loop()
{
#ifdef ROW_BY_ROW
	Shader* screenShader;
	unsigned fbo;
	unsigned renderTexture;
	initializeFBO(screenShader, fbo, renderTexture);
#endif

	auto currRow = 0;
	while (true)
	{
#ifdef ROW_BY_ROW
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
#else
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
#endif

		// Draw scene
		onUpdate();
		shader->use();
		glBindVertexArray(shader->vaoScreen->id);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		shader->setInt("currRow", currRow++);


#ifdef ROW_BY_ROW
		// second pass
		glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default

		screenShader->use();
		glBindVertexArray(shader->vaoScreen->id);
		glBindTexture(GL_TEXTURE_2D, renderTexture);
		glDrawArrays(GL_TRIANGLES, 0, 6);
#endif

		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_CUBE_MAP, shader->skybox->id);

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
