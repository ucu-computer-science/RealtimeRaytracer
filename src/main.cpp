#include "Camera.h"

#include "Benchmark.h"
#include "GraphicalObject.h"
#include "SDLDisplayer.h"
#include "Triangle.h"
#include "glm/vec2.hpp"

void f(int a)
{
	std::cout << "yay: " << a << '\n';
}

int main(int argv, char* args[])
{
	//Benchmark::benchmark(200);
	//Benchmark::benchmarkVectors(100);

	constexpr float fov = 1;
	int width = 1280, height = 720;

	Camera camera{{0.5, 0, 0.5}, fov, glm::vec2(width / (float)height, 1)};
	camera.setBackgroundColor(Color::gray());

	//GraphicalObject obj1{ glm::vec3{ 1, 1, 1 } };
	//Triangle t1{ glm::vec3(0.2, 1, 0.2), glm::vec3(0.2, 1, 0.8), glm::vec3(0.8, 1, 0.5), Color::cyan() };
	//Triangle t2{ glm::vec3(0.4, 1, 0.2), glm::vec3(0.4, 2, 0.8), glm::vec3(1, 1, 0.8), Color::magenta() };
	//obj1.triangles.emplace_back(&t1);
	//obj1.triangles.emplace_back(&t2);

	Cube obj2{glm::vec3{1, 1, 0.5}, 1};
	obj2.setColor(Color::green());
	Cube obj3{ glm::vec3{ 0.5, 1.5, 1.5 }, 1 };
	obj3.setColor(Color::magenta());
	Cube obj4{ glm::vec3{ 1.5, 0.5, 0.5 }, 1 };
	obj4.setColor(Color::yellow());
        Sphere obj5{{-2,0,6}, 10, Color::blue()};
        Sphere obj6{{-6,4,-5}, 2, Color::yellow()};
        Sphere obj7{{0,0,0}, 0.0625, Color::red()};
        Plane obj8{{0, 0, 6}, {0,0,1}, Color::darkgreen()};
        Plane obj9{{0, 0, -6}, {0,0,-1}, Color::skyblue()};
//        Square obj10 {{0,0,0}, {1,1,1}, {1,1,-1}};
        SquarePyramid obj11{{-8,2,6}, {-8,6,6}, {-4,2,6}, {-6,4,-5}};
        obj11.setColor(Color::black());
//        Box obj10{};
	show(screenResolution);
	//Cube obj3{ glm::vec3{ 0.5, 1.5, 1.5 }, 1 };
	//obj3.setColor(Color::magenta());
	//Cube obj4{ glm::vec3{ 1.5, 0.5, 0.5 }, 1 };
	//obj4.setColor(Color::yellow());
	Sphere obj5{{-2, 1, 0}, 3, Color::blue()};
	Sphere obj6{{-5, 3, 3}, 2, Color::yellow()};
	Plane obj8{{0, 0, 0}, {0, 0, -1}, Color::darkGreen()};
	Plane obj9{{0, 0, 256}, {0, 0, 1}, Color::skyBlue()};

	SDLDisplayer::display(width, height);
	//Camera::instance->skip = 2;

	return 0;
}