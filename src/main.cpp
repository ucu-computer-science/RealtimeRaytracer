#include "Vec3.h"
#include "Camera.h"
#include "GraphicalObject.h"
#include "SDL_runner.h"
#include "Triangle.h"
#include "Square.h"


int main(int argv, char* args[]) {
	const auto A = Vec3(0, 0, 0);
	const auto B = Vec3(0, 0, 1);
	const auto C = Vec3(1, 0, 1);

	const auto dir1 = (A - B).normalized();
	const auto dir2 = (C - B).normalized();
	constexpr double fov = 1;

	Vec2Int screenResolution{ 800, 400 };
	Vec2 cameraSize{ 2, 1 };

	Camera camera{ { 0.5, 0, 0.5 }, fov, screenResolution, cameraSize };
	std::cout << camera.forward();

	GraphicalObject obj{ Vec3{ 1, 1, 1 } };
	Triangle t1{ Vec3(0.2, 1, 0.2), Vec3(0.2, 1, 0.8), Vec3(0.8, 1, 0.5), Color::cyan() };
	Triangle t2{ Vec3(0.4, 1, 0.2), Vec3(0.4, 2, 0.8), Vec3(1, 1, 0.8), Color::magenta() };
	obj.triangles.emplace_back(&t1);
	obj.triangles.emplace_back(&t2);

	show(screenResolution);

	return 0;
}
