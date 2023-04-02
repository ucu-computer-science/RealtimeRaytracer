#include "Camera.h"

#include "Benchmark.h"
#include "GraphicalObject.h"
#include "mathExtensions.h"
#include "SDLDisplayer.h"
#include "Triangle.h"
#include "glm/vec2.hpp"
#include "Light.h"

int main(int argv, char* args[])
{
	//Benchmark::benchmark(200);
	//Benchmark::benchmarkVectors(100);

	constexpr float fov = 0.5;
	int width = 1280, height = 720;

	Camera camera{{0, -20, 0}, fov, glm::vec2((float)width / (float)height, 1)};
	camera.setBackgroundColor(Color::gray());

	Light light{{9, -9, 9}, {1, 1, 1}};
//        Light light2{{-9, 9, 9}};

	Cube obj3{glm::vec3{0.5, 1.5, 1.5}, {{45 * DEG_TO_RAD, 45 * DEG_TO_RAD, 45 * DEG_TO_RAD}}, 1};
	obj3.setColor(Color::magenta());
	Sphere obj5{{-2, 1, 0}, 3, Color::blue()};
	Sphere obj6{{-5, 3, 3}, 2, Color::yellow()};
	Plane obj8{{0, 0, 0}, {0, 0, 1}, Color::darkGreen()};
	Plane obj9{{0, 0, 256}, {0, 0, -1}, Color::skyBlue()};
	SquarePyramid obj11{{2, 2, 2}, {{45 * DEG_TO_RAD, 45 * DEG_TO_RAD, 45 * DEG_TO_RAD}}, 1, 2};
	obj11.setColor(Color::cyan());

//        Light ligh3{{0, 0, 0}};

//	Cube obj3{glm::vec3{0.5, 1.5, 1.5}, {{45 * DEG_TO_RAD, 45 * DEG_TO_RAD, 45 * DEG_TO_RAD}}, 1};
//	obj3.setColor(Color::magenta());
//	Sphere obj5{{-2, 1, 0}, 3, Color::blue()};
//	Sphere obj6{{-5, 3, 3}, 2, Color::yellow()};
//	Plane obj8{{0, 0, 0}, {0, 0, 1}, Color::darkGreen()};
//	Plane obj9{{0, 0, 256}, {0, 0, -1}, Color::skyBlue()};
//	SquarePyramid obj11{{2, 2, 2}, {{45 * DEG_TO_RAD, 45 * DEG_TO_RAD, 45 * DEG_TO_RAD}}, 1, 2};
//	obj11.setColor(Color::cyan());
        Plane plane1{{-10, 0, 0}, {1, 0, 0}, Color::red()};
        Plane plane2{{10, 0, 0}, {-1, 0, 0}, Color::green()};
        Plane plane3{{0, 0, 10}, {0, 0, -1}, Color::white()};
        Plane plane4{{0, 0, -10}, {0, 0, 1}, Color::white()};
        Plane plane5{{0, 10, 0}, {0, -1, 0}, Color::white()};
        Plane plane6{{0, -10, 0}, {0, 1, 0}, Color::white()};
        Cube cube1{glm::vec3{4, -5, -6.7}, {{0 * DEG_TO_RAD, 0 * DEG_TO_RAD, -15 * DEG_TO_RAD}}, 6.6};
        Sphere sphere1{{-4, 2, -5}, 36, Color::blue()};
//        Camera::instance->skip = 2;

	SDLDisplayer::display(width, height);

	return 0;
}