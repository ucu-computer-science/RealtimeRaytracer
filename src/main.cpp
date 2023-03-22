#include <iostream>
#include <functional>
#include "Vec3.h"
#include "Camera.h"
#include "GraphicalObject.h"
#include "Ray.h"
#include "Raycast.h"
#include "ScreenMatrix.h"
#include "SDL_runner.h"
#include "Triangle.h"

using Vector::Vec3;

int main(int argv, char** args) {
	const auto A = Vec3(0, 0, 0);
	const auto B = Vec3(0, 0, 1);
	const auto C = Vec3(1, 0, 1);

	const auto dir1 = (A - B).normalized();
	const auto dir2 = (C - B).normalized();
	constexpr float fov = 1;

	Screen screen{ {1,1},{400,400}, dir1, dir2 };
	Camera camera{ B, fov, screen };

	Triangle t{ Vec3(0.2f,1,0.2f), Vec3(0.2f,1,0.8f), Vec3(0.8f,1,0.5f) };
	GraphicalObject obj{ Vec3{1,1,1}, {&t} };

	show(400, 400);

	return 0;
}
