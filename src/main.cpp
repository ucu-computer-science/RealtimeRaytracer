// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <iostream>
#include <Vec3.h>
#include <Triangle.h>
#include <Color.h>
#include <Camera.h>
//#include <curses.h>
//#include <ncurses.h>
#define ARROW_UP     72
#define ARROW_DOWN   80
#define ARROW_LEFT   75
#define ARROW_RIGHT  77




#ifdef _WIN32
#include <conio.h>
#include <windows.h>
void set_cursor(int x = 0 , int y = 0)
{
    HANDLE handle;
    COORD coordinates;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition ( handle , coordinates );
}
#endif
//#include "SDL_runner.h"
//void test(){
//	Triangle t(Vec3(0, 0, 0), Vec3(1, 0, 0), Vec3(0, 1, 0));
//	Color c(1, 0, 0);
//
//	}
#include <chrono>
//#include<unistd.h>
#include <memory>
#include "Benchmark.h"
#include "Square.h"

int main() {
//    int wPixels = 450;
//    int hPixels = 98;
        Benchmark::benchmark(50);
//        Triangle t(Vec3(1, 1, 1), Vec3(-1, 1, 1), Vec3(0, 3, -1));
#ifdef SHOW
    auto screen = std::vector(hPixels, std::vector<float>(wPixels, 0));

    graphicalObjectVector graphicalObjects;
    graphicalObjects.emplace_back(new  Square(Vec3(1, 1, 1),
                                                   Vec3(-1, 1, 1),
                                                   Vec3(0, 3, -1)));
    graphicalObjects.emplace_back(new  Square(Vec3(1, 1, 1),
                                              Vec3(-1, 1, 1),
                                              Vec3(-1, 4, 1)));
//    graphicalObjects.emplace_back(new Triangle(Vec3(1, 1, 1),
//                                                   Vec3(3,1,0),
//                                                   Vec3(0, 3, -1)));
//    graphicalObjects.emplace_back(new Square)
    Camera camera(Vec3(-3, 1, 1),
                  Vec3(-3, 1, 0),
                  Vec3(-1, 1, 1), wPixels, hPixels, 1, screen, graphicalObjects);
    char key;
    int dist_index;
    const float MOVE_SCALE = 0.2;
    while(true  ){
#ifdef __linux__
        std::cin >> key;
#elif _WIN32
        key = getch();
#endif


        switch( key ){

                case 'w':
                    //code her...
                    camera.moveZ(MOVE_SCALE);
//                    std::cout<< "ARROW_UP" << std::endl;

                    break;
                case 's':
                    camera.moveZ(-MOVE_SCALE);
//                    std::cout<< "ARROW_DOWN" << std::endl;

                    //code her...
                    break;
                case 'a':
                    camera.moveX(-MOVE_SCALE);
//                    std::cout<< "ARROW_LEFT" << std::endl;

                    //code her...
                    break;
                case 'd':
//                    std::cout<< "ARROW_RIGHT" << std::endl;

                    camera.moveX(MOVE_SCALE);
                    //code her...
                    break;
                case 'r':
                    camera.moveY(MOVE_SCALE);
                    break;
                case 'f':
                    camera.moveY(-MOVE_SCALE);
                    break;
                case 'q':
                    goto OUT_LABEL;
                    break;
                default:

//                    //code her...
                    break;


            }

        camera.update();
#ifdef __linux__
        printf("\x1b[H");
#elif _WIN32
        set_cursor(0 ,0);
#endif
        for (const auto& i: screen){

            for (auto j: i) {



                putchar((bool)j? '@': ' ');
            }
            putchar('\n');
        }
//        usleep(40000);
//
//
//        mvwin(childwin, y, x);
//        wrefresh(childwin);

        }
OUT_LABEL:
//    for (int t = 0; t < 200; ++t) {
////        camera.setFov(t*t/20);
//        camera.moveX(MOVE_SCALE);
//
//    }
//    delwin(childwin);
//    delwin(mainwin);
//    endwin();
//    refresh();

//	test();
//    show(1000, 800);
#endif //SHOW
    return 0;
}