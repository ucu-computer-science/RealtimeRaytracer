
#include "Benchmark.h"
#include "Vec3.h"
#include "Camera.h"
#include "GraphicalObject.h"
#include "SDL_runner.h"
#include "Triangle.h"
#include "Square.h"
//#define BENCHMARK
int main(int argv, char* args[])
{

#ifdef BENCHMARK
	Benchmark::benchmark(200);
	//Benchmark::benchmarkVectors(100);
#else

	constexpr double fov = 1;

	Vec2Int screenResolution{ 1280, 720 };
	Vec2 cameraSize{ 2, 1 };

	Camera camera{ { 0.5, 0, 0.5 }, fov, screenResolution, cameraSize };
    camera.setBackgroundColor(Color::gray());

    /*	GraphicalObject obj{ Vec3{ 1, 1, 1 } };
	Square t1(Vec3(1, 1, 1), Vec3(1, 1, 1),
		Vec3(-1, 1, 1),
		Vec3(0, 3, -1), Color::cyan());
	Square t2(Vec3(1, 1, 1), Vec3(1, 1, 1),
		Vec3(-1, 1, 1),
		Vec3(-1, 4, 1), Color::magenta());

	Triangle t3({ -1, 1, 1 }, { -2, 3, -1 }, { -3, 4, 1 }, Color::white());
	Triangle t4({ 1, 1, 1 }, { 0, 3, -1 }, { -1,  4, 1 }, Color::white());
	Square t5(Vec3(1, 1, 1), { -3, 4, 1 },
		{ -1, 4, 1 },
		{ -2, 3, -1 }, Color::black());
     obj.triangles.emplace_back(&t3);
    obj.triangles.emplace_back(&t4);
     */
Cube obj2{ Vec3{ 1, 1, 1 }, 1 };
	obj2.setColor(Color::green());
	show(screenResolution);
#endif //BENCHMARK

	return 0;
}
