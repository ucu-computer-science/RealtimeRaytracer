#include "Vec3.h"
#include "Camera.h"
#include "GraphicalObject.h"
#include "SDL_runner.h"
#include "Triangle.h"

#include "Square.h"

using Vector::Vec3;

int main(int argv, char* args[]) {
	const auto A = Vec3(0, 0, 0);
	const auto B = Vec3(0, 0, 1);
	const auto C = Vec3(1, 0, 1);

	const auto dir1 = (A - B).normalized();
	const auto dir2 = (C - B).normalized();
	constexpr double fov = 1;

	Vec2Int screenResolution{ 800, 400 };

	Screen screen{ {2,1},screenResolution, dir1, dir2 };
	Camera camera{ {0,0,0}, fov, screen };

	Triangle t{ Vec3(0.2,1,0.2), Vec3(0.2,1,0.8), Vec3(0.8,1,0.5) };
	GraphicalObject obj{ Vec3{1,1,1} };
	obj.triangles.emplace_back(&t);

	show(screenResolution);

	return 0;
}
