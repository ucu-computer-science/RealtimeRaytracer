#include "Camera.h"

#include "Benchmark.h"
#include "GraphicalObject.h"
#include "SDL_runner.h"
#include "Triangle.h"
#include "glm/vec2.hpp"
//#define BENCHMARK
int main(int argv, char* args[])
{
#ifdef BENCHMARK
	Benchmark::benchmark(200);
	//Benchmark::benchmarkVectors(100);
#else

	constexpr float fov = 1;

	glm::vec2 screenResolution{ 1280 / 2, 720 / 2 };
	glm::vec2 cameraSize{ 2, 1 };

	Camera camera{ { 0.5, 0, 0.5 }, fov, screenResolution, cameraSize };
	camera.setBackgroundColor(Color::gray());

	//GraphicalObject obj1{ glm::vec3{ 1, 1, 1 } };
	//Triangle t1{ glm::vec3(0.2, 1, 0.2), glm::vec3(0.2, 1, 0.8), glm::vec3(0.8, 1, 0.5), Color::cyan() };
	//Triangle t2{ glm::vec3(0.4, 1, 0.2), glm::vec3(0.4, 2, 0.8), glm::vec3(1, 1, 0.8), Color::magenta() };
	//obj1.triangles.emplace_back(&t1);
	//obj1.triangles.emplace_back(&t2);

	Cube obj2{ glm::vec3{ 1, 1, 1 }, 1 };
	obj2.setColor(Color::green());
	Cube obj3{ glm::vec3{ 0.5, 1.5, 1.5 }, 1 };
	obj3.setColor(Color::magenta());
	//Cube obj4{ glm::vec3{ 1.5, 0.5, 0.5 }, 1 };
	//obj4.setColor(Color::yellow());

	show(screenResolution);

#endif //BENCHMARK

	return 0;
}
