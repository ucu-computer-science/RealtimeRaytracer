
#include <iostream>
#include <Vec3.h>
#include <Triangle.h>
#include <Color.h>
#include <Camera.h>
//#include "SDL_runner.h"
//void test(){
//	Triangle t(Vec3(0, 0, 0), Vec3(1, 0, 0), Vec3(0, 1, 0));
//	Color c(1, 0, 0);
//
//	}


int main()
{
	auto v = Vec3(1, 2, 3);
	auto x = v * v;
    int wPixels = 20;
    int hPixels = 10;
    auto screen = std::vector(hPixels, std::vector<float>(wPixels, 0))
    Camera camera(Vec3(-1,1,1),
                  Vec3(-1,1,0),
                  Vec3(1,1,1), wPixels, hPixels, 4, screen);
	std::cout << x << std::endl;
//	test();
//    show(1000, 800);
    return 1;
