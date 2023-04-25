#include "Camera.h"

#include "Benchmark.h"
#include "GraphicalObject.h"
#include "Light.h"
#include "SDLDisplayer.h"
#include "Triangle.h"
#include "mathExtensions.h"
#include "ObjectParser.h"
#include "BoundingBoxes.h"


void createBlueBallScene(float fov, int width, int height)
{
	Camera camera{{0, -28, -5}, fov, glm::vec2((float)width / (float)height, 1)};
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
void createRedGreenRoom(float fov, int width, int height)
{
	PointLight light3{{0, 0, 8}, {255 / 255.0f, 236 / 255.0f, 156 / 255.0f}, FLT_MAX, 1};
	Square sq{{0, 0, 9.999f}, {{-90 * DEG_TO_RAD, 0, 0}}, 5};
	sq.material.color = {3.f, 3.f, 3.f};
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
	Sphere obj5{{-2, 1, 0}, sqrt(3.f), Color::blue()};
	Sphere obj6{{-5, 3, 3}, sqrt(2.f), Color::yellow()};
	obj5.material.reflection = 0;
	obj6.material.reflection = 0.5;
	Plane obj8{{0, 0, 0}, {0, 0, 1}, Color::darkGreen()};
}


int main(int argv, char* args[])
{
	constexpr float fov = 1;
	int width = 640 * 2, height = 360 * 2;
	Camera camera{{0, -35, 0}, fov, glm::vec2((float)width / (float)height, 1)};

	//PointLight light3{{0, 0, 8}, {255 / 255.0f, 236 / 255.0f, 156 / 255.0f}, FLT_MAX, 1};
	//Cube cube1{glm::vec3{0, 0, 0}, {{0 * DEG_TO_RAD, 0 * DEG_TO_RAD, -28 * DEG_TO_RAD}}, 10.0f};
	//Cube cube2{glm::vec3{34, 26, -6.7}, {{0 * DEG_TO_RAD, 0 * DEG_TO_RAD, -28 * DEG_TO_RAD}}, 6.6f};
	//Sphere sphere1{{-4, 2, -5}, 5, Color::skyBlue()};
	//Sphere sphere2{{26, 32, -5}, 5, Color::skyBlue()};

	//cube1.material.lit = false;
	//cube2.material.lit = false;
	//sphere1.material.lit = false;
	//sphere2.material.lit = false;
    GlobalLight light8{{0, -1, 0}, Color::white(), 1};

	Model model("./models/Man.obj");
	GraphicalObject obj(model.triangles,{0, 0, 1}, {{90, 0, 0}}, {Color::white()});
//	obj.material.lit = false;
    obj.setMaterial({{}, 1, 1, 0, 4000, .1});
    obj.setTexture("./earth.png");
	//auto t1 = std::shared_ptr<Triangle>(new Triangle(nullptr, {0, 0, 0}, {10, 10, 0}, {10, 10, 10}));
	////auto t2 = std::shared_ptr<Triangle>(new Triangle(nullptr, {0, 5, 0}, {10, 15, 10}, {15, 10, 0}));
	//GraphicalObject obj{{t1}};
	//obj.material.color = Color::white();
	//obj.material.lit = false;
	//t1->attachToObject(&obj);

//    Sphere sphere3{{-6, -30, -4}, 6, Color::white()};
//    sphere3.setTexture("./beer.png");
//    sphere3.setMaterial({{}, 1, 1, 0.4, 4000, .1});
	SDLDisplayer::display(width, height);
	return 0;
}