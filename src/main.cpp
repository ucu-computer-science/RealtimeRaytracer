#include "Camera.h"

#include "Benchmark.h"
#include "GraphicalObject.h"
#include "mathExtensions.h"
#include "SDLDisplayer.h"
#include "Triangle.h"
#include "Light.h"

int main(int argv, char* args[])
{
	constexpr float fov = 1;
	int width = 640 * 2, height = 360 * 2;
        srand(time(NULL));
	Camera camera{{0, -38, 3}, fov, glm::vec2((float)width / (float)height, 1)};
        Light light3{{0, 0, 8}, {255 / 255.0f, 236 / 255.0f, 156 / 255.0f}, 50, 1, {0, 0, 0}, {1, 1, 1}};
//        Light light3{{0, 0, 8}, {1,1,1}, 50, 0.4, {5, 5, 0}, {10, 10, 1}};
//        Light light4{{0, -15, 8}, {1,1,1}, 50, 0.4, {5, 5, 0}, {10, 10, 1}};


	Square sq{{0, -15, 9.999f}, {{-90 * DEG_TO_RAD, 0, 0}}, 5};
        Square sq2{{0, 0, 9.999f}, {{-90 * DEG_TO_RAD, 0, 0}}, 5};

	sq.setColor({3, 3, 3});
        sq2.setColor({3, 3, 3});
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
//	Plane plane6{{0, -10, 0}, {0, 1, 0}, Color::white()};
	Cube cube1{glm::vec3{4, -4, -6.7}, {{0 * DEG_TO_RAD, 0 * DEG_TO_RAD, -28 * DEG_TO_RAD}}, 6.6f};
//        Cube cube2{glm::vec3{4, -4, 0}, {{0 * DEG_TO_RAD, 0 * DEG_TO_RAD, -28 * DEG_TO_RAD}}, 6.6f};
//        Cube cube3{glm::vec3{4, -4, 6.6}, {{0 * DEG_TO_RAD, 0 * DEG_TO_RAD, -28 * DEG_TO_RAD}}, 6.6f};

	Sphere sphere1{{-4, 2, -5}, 5, Color{        100./100, 49.8/100, 31.4/100}};
//        sphere1.setReflection(.5f);

//        Plane planeWhite1{{0, 0, -10}, {0, 0, 1}, Color::white()};;
//        Plane planeWhite2{{0, 200, 200}, {0, -0.5, -1}, Color::skyBlue()};;
	cube1.setColor(Color::skyBlue());
	cube1.setReflection(0.3f);
//        cube2.setReflection(0.3f);
//        cube3.setReflection(0.3f);

//        Sphere sphere2{{5, 5, -5}, 5, Color::gold()};
//	plane1.setReflection(0);
//	plane2.setReflection(0);
//	plane3.setReflection(0);
//	plane4.setReflection(0);
//	plane5.setReflection(0);
//	plane6.setReflection(0);

	/*
	 Cube obj3{glm::vec3{0.5, 1.5, 1.5}, {{45 * DEG_TO_RAD, 45 * DEG_TO_RAD, 45 * DEG_TO_RAD}}, 1};
	obj3.setColor(Color::magenta());
	Sphere obj5{{-2, 1, 0}, 3, Color::blue()};
	Sphere obj6{{-5, 3, 3}, 2, Color::yellow()};
	obj5.setReflection(0);
	obj6.setReflection(0.5);
	Plane obj8{{0, 0, 0}, {0, 0, 1}, Color::darkGreen()};
	SquarePyramid obj11{{2, 2, 2}, {{45 * DEG_TO_RAD, 45 * DEG_TO_RAD, 45 * DEG_TO_RAD}}, 1, 2};
	obj11.setColor(Color::cyan());
	 */

	SDLDisplayer::display(width, height);
	return 0;
}