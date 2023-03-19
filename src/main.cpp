
#include <iostream>
#include "Vec2Int.h"
#include "Camera.h"

int main()
{
	const auto p1 = Vec3(-1, 1, 0);
	const auto p2 = Vec3(-1, 1, 1);
	const auto p3 = Vec3(1, 1, 1);

	const auto dir1 = (p1 - p2).normalized();
	const auto dir2 = (p3 - p2).normalized();
	std::cout << dir1 << std::endl;
	std::cout << dir2 << std::endl;

	Screen screen{ {1,2},{20,10}, dir1, dir2 };
	Camera camera{ 1, &screen };
	camera.pos = p2;
	screen.setCamera(camera);
	std::cout << camera.getFocalPoint();
	return 0;
}
