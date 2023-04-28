#include "Camera.h"
#include "Canvas.h"

#include "GraphicalObject.h"
#include "Light.h"
#include "SDLDisplayer.h"
#include "Triangle.h"
#include "MathExtensions.h"
#include "SceneParser.h"
#include "PolyMesh.h"

void createBlueBallScene(float fov, int width, int height)
{
	//Camera camera{{0, -28, -5}, fov, glm::vec2((float)width / (float)height, 1)};
	GlobalLight light8{{-0.1, -0.9, 1}, Color::white(), 1};
	GlobalLight light9{{-0.3, -0.1, 1}, Color::white(), 1};
	Plane plane1{{-100, 0, 0}, {1, 0, 1}, Color::skyBlue()};
	Plane plane2{{0, -100, 0}, {0, 1, 1}, Color::skyBlue()};
	Plane plane3{{100, 0, 0}, {-1, 0, 1}, Color::skyBlue()};
	Plane plane45{{0, 100, 0}, {0, -1, 1}, Color::skyBlue()};
	Plane plane4{{0, 0, -10}, {0, 0, 1}, Color::white()};
	Sphere sphere1{{-4, 2, -5}, 5, Color{100.f / 100.f, 49.8f / 100.f, 31.4f / 100.f}};

	Sphere sphere2{{-6, -10, -9}, 1, Color::gold()};
	Sphere sphere3{{7, 7, -4}, 6, Color::hotPink()};
	Sphere sphere4{{7, -5, -7}, 3, Color::pink()};
	sphere1.material.reflection = .3f;
	sphere2.material.reflection = .3f;
	sphere3.material.reflection = .3f;
	sphere4.material.reflection = .3f;
}
void createRedGreenRoom()
{
	PointLight light3{{0, 0, 8}, {255 / 255.0f, 236 / 255.0f, 156 / 255.0f}, FLT_MAX, 1};
	//	Square sq{{0, 0, 9.999f}, {{-90 * DEG_TO_RAD, 0, 0}}, 5};
	//	sq.material.color = {3.f, 3.f, 3.f};
	Plane plane1{{-10, 0, 0}, {1, 0, 0}, Color::red()};
	Plane plane2{{10, 0, 0}, {-1, 0, 0}, Color::green()};
	Plane plane3{{0, 0, 10}, {0, 0, -1}, Color::white()};
	Plane plane4{{0, 0, -10}, {0, 0, 1}, Color::white()};
	Plane plane5{{0, 10, 0}, {0, -1, 0}, Color::white()};
	Plane plane6{{0, -10, 0}, {0, 1, 0}, Color::white()};
	Cube cube1{glm::vec3{4, -4, -6.7}, {{0 * DEG_TO_RAD, 0 * DEG_TO_RAD, -28 * DEG_TO_RAD}}, 6.6f};
	Sphere sphere1{{-4, 2, -5}, 5, Color{100.f / 100.f, 49.8f / 100.f, 31.4f / 100.f}};
	sphere1.material.reflection = 0.7f;
	cube1.material.color = Color::gold();
	cube1.material.reflection = 0.3f;
}
inline void createFirstScene(float fov, int width, int height)
{
	PointLight light3{{0, 0, 8}, {255 / 255.0f, 236 / 255.0f, 156 / 255.0f}, 20, 1};
	Cube obj3{glm::vec3{0.5, 1.5, 1.5}, {{45 * DEG_TO_RAD, 45 * DEG_TO_RAD, 45 * DEG_TO_RAD}}, 1};
	obj3.material.color = Color::magenta();
	Sphere obj5{{-2, 1, 0}, (float)sqrt(3.0), Color::blue()};
	Sphere obj6{{-5, 3, 3}, (float)sqrt(2.0), Color::yellow()};
	obj5.material.reflection = 0;
	obj6.material.reflection = 0.5;
	Plane obj8{{0, 0, 0}, {0, 0, 1}, Color::darkGreen()};
}


int main(int argv, char* args[])
{
	constexpr float focusDistance = 30, lensRadius = 0.05f;
	int width = 640 * 2, height = 360 * 2;

	Camera camera{{0, -30, 0}, focusDistance, lensRadius, glm::vec2((float)width / (float)height * focusDistance, focusDistance)};

	GlobalLight light9{{0, 1, 0}, Color::white(), 1};
	GlobalLight ligh10{{0, -1, 0}, Color::white(), 1};
	//PointLight light3{{0, 0, 8}, {255 / 255.0f, 236 / 255.0f, 156 / 255.0f}, 1, FLT_MAX};
	ImportedGraphicalObject obj("../../models/skull.obj");
	auto tex = std::make_shared<Texture>();
	obj.setMaterial(Material(Color::white(), tex, true, 1, 0, 2000, .1f));


	//Cube cube1{glm::vec3{4, -4, -6.7}, {{0 * DEG_TO_RAD, 0 * DEG_TO_RAD, -28 * DEG_TO_RAD}}, 6.6f};
	//cube1.material.lit = false;

	Canvas::mainCanvas = std::make_unique<Canvas>();

	Texture crosshair{"./sprites/crosshair.png"};
	Canvas::mainCanvas->addElement(std::make_shared<Image>(glm::vec2(100, 100), &crosshair));

	//SceneParser::recordScene(Scene::objects,"../../scenes/scene1.json");
	//SceneParser::parseScene("../../scenes/scene1.json");
	SDLDisplayer::display(width, height);
	return 0;
}
