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

	constexpr float fov = 1;
	int width = 1280, height = 720;

	Camera camera{{0.5, 0, 0.5}, fov, glm::vec2((float)width / (float)height, 1)};
	camera.setBackgroundColor(Color::gray());

	//{0.749, 0.616, 0.247}
	Light light{{0, 0, 10}, {1, 1, 1}};

	Cube obj3{glm::vec3{0.5, 1.5, 1.5}, {{45 * DEG_TO_RAD, 45 * DEG_TO_RAD, 45 * DEG_TO_RAD}}, 1};
	obj3.setColor(Color::magenta());
	Sphere obj5{{-2, 1, 0}, 3, Color::blue()};
	Sphere obj6{{-5, 3, 3}, 2, Color::yellow()};
	Plane obj8{{0, 0, 0}, {0, 0, 1}, Color::darkGreen()};
	//Plane obj9{{0, 0, 256}, {0, 0, -1}, Color::skyBlue()};
	SquarePyramid obj11{{2, 2, 2}, {{45 * DEG_TO_RAD, 45 * DEG_TO_RAD, 45 * DEG_TO_RAD}}, 1, 2};
	obj11.setColor(Color::cyan());

	SDLDisplayer::display(width, height);
	//Camera::instance->skip = 2;

	return 0;
}
