#include "Camera.h"

#include "Benchmark.h"
#include "GraphicalObject.h"
#include "Light.h"
#include "SDLDisplayer.h"
#include "Triangle.h"
#include "mathExtensions.h"
#include "ObjectParser.h"

void createBlueBallScene(float fov, int width, int height) {
  Camera camera{{0, -28, -5}, fov, glm::vec2((float)width / (float)height, 1)};
  GlobalLight light8{{-0.1, -0.9, 1}, Color::white(), 1};
  GlobalLight light9{{-0.3, -0.1, 1}, Color::white(), 1};
  Plane plane1{{-100, 0, 0}, {1, 0, 1}, Color::skyBlue()};
  Plane plane2{{0, -100, 0}, {0, 1, 1}, Color::skyBlue()};
  Plane plane3{{100, 0, 0}, {-1, 0, 1}, Color::skyBlue()};
  Plane plane45{{0, 100, 0}, {0, -1, 1}, Color::skyBlue()};
  Plane plane4{{0, 0, -10}, {0, 0, 1}, Color::white()};
  Sphere sphere1{
      {-4, 2, -5}, 5, Color{100.f / 100.f, 49.8f / 100.f, 31.4f / 100.f}};
  Sphere sphere2{{-6, -10, -9}, 1, Color::gold()};
  Sphere sphere3{{7, 7, -4}, 6, Color::hotpink()};
  Sphere sphere4{{7, -5, -7}, 3, Color::pink()};
  sphere1.setReflection(.3f);
  sphere2.setReflection(.3f);
  sphere3.setReflection(.3f);
  sphere4.setReflection(.3f);
}
void createRedGreenRoom(float fov, int width, int height) {
  PointLight light3{
      {0, 0, 8}, {255 / 255.0f, 236 / 255.0f, 156 / 255.0f}, FLT_MAX, 1};
  Square sq{{0, 0, 9.999f}, {{-90 * DEG_TO_RAD, 0, 0}}, 5};
  sq.setColor({3.f, 3.f, 3.f});
  Plane plane1{{-10, 0, 0}, {1, 0, 0}, Color::red()};
  ;
  Plane plane2{{10, 0, 0}, {-1, 0, 0}, Color::green()};
  Plane plane3{{0, 0, 10}, {0, 0, -1}, Color::white()};
  Plane plane4{{0, 0, -10}, {0, 0, 1}, Color::white()};
  Plane plane5{{0, 10, 0}, {0, -1, 0}, Color::white()};
  Plane plane6{{0, -10, 0}, {0, 1, 0}, Color::white()};
  Cube cube1{glm::vec3{4, -4, -6.7},
             {{0 * DEG_TO_RAD, 0 * DEG_TO_RAD, -28 * DEG_TO_RAD}},
             6.6f};
  Sphere sphere1{
      {-4, 2, -5}, 5, Color{100.f / 100.f, 49.8f / 100.f, 31.4f / 100.f}};
  sphere1.setReflection(0.7f);
  cube1.setColor(Color::gold());
  cube1.setReflection(0.3f);
}
inline void createFirstSceene(float fov, int width, int height) {
  PointLight light3{
      {0, 0, 8}, {255 / 255.0f, 236 / 255.0f, 156 / 255.0f}, 20, 1};
  Cube obj3{glm::vec3{0.5, 1.5, 1.5},
            {{45 * DEG_TO_RAD, 45 * DEG_TO_RAD, 45 * DEG_TO_RAD}},
            1};
  obj3.setColor(Color::magenta());
  Sphere obj5{{-2, 1, 0}, sqrt(3.f), Color::blue()};
  Sphere obj6{{-5, 3, 3}, sqrt(2.f), Color::yellow()};
  obj5.setReflection(0);
  obj6.setReflection(0.5);
  Plane obj8{{0, 0, 0}, {0, 0, 1}, Color::darkGreen()};
  SquarePyramid obj11{
      {2, 2, 2}, {{45 * DEG_TO_RAD, 45 * DEG_TO_RAD, 45 * DEG_TO_RAD}}, 1, 2};
  obj11.setColor(Color::cyan());
}
// the above functions are for copying. We need to make it work other way
int main(int argv, char *args[]) {
  constexpr float fov = 1;
  int width = 640 * 2, height = 360 * 2;
      Camera camera{{0, -28, -5}, fov, glm::vec2((float)width / (float)height, 1)};
    GlobalLight light8{{-0.1, -0.9, 1}, Color::white(), 2};
    GlobalLight light9{{-0.3, -0.1, 1}, Color::white(), 2};
    Plane plane1{{-100, 0, 0}, {1, 0, 1}, Color::skyBlue()};
    Plane plane2{{0, -100, 0}, {0, 1, 1}, Color::skyBlue()};
    Plane plane3{{100, 0, 0}, {-1, 0, 1}, Color::skyBlue()};
    Plane plane45{{0, 100, 0}, {0, -1, 1}, Color::skyBlue()};
    Plane plane4{{0, 0, -10}, {0, 0, 1}, Color::white()};
  Model model("../models/Man.obj");
//  for (auto i : model.triangles){
//      std::cout << *i << std::endl;
//  }
  GraphicalObject cube({0,0,0},{{0,0,0}}, Color::black(), 0.7f);
  cube.triangles = model.triangles;


  SDLDisplayer::display(width, height);





















  //        createBlueBallScene(fov, width, height);
//  Camera camera{{0, -28, -5}, fov, glm::vec2((float)width / (float)height, 1)};
//  GlobalLight light8{{-0.1, -0.9, 1}, Color::white(), 2};
//  GlobalLight light9{{-0.3, -0.1, 1}, Color::white(), 2};
//  Plane plane1{{-100, 0, 0}, {1, 0, 1}, Color::skyBlue()};
//  Plane plane2{{0, -100, 0}, {0, 1, 1}, Color::skyBlue()};
//  Plane plane3{{100, 0, 0}, {-1, 0, 1}, Color::skyBlue()};
//  Plane plane45{{0, 100, 0}, {0, -1, 1}, Color::skyBlue()};
//  Plane plane4{{0, 0, -10}, {0, 0, 1}, Color::white()};
//  Sphere sphere1{
//      {-4, 2, -5}, 5, Color{100.f / 100.f, 49.8f / 100.f, 31.4f / 100.f}};
//  Sphere sphere2{{-6, -10, -9}, 1, Color::gold()};
//  Sphere sphere3{{7, 7, -4}, 6, Color::hotpink()};
//  Sphere sphere4{{7, -5, -7}, 3, Color::pink()};
//  sphere1.setReflection(.3f);
//  sphere2.setReflection(.3f);
//  sphere3.setReflection(.3f);
//  sphere4.setReflection(.3f);
  //        createFirstSceene(fov, width, height);
  //	Camera camera{{0, -28, 3}, fov, glm::vec2((float)width / (float)height,
  //1)};
  //        PointLight light3{{0, 0, 8}, {255 / 255.0f, 236 / 255.0f, 156 /
  //        255.0f}, 20, 1}; Light light6{{0, 0, 8}, {1,1,1}, FLT_MAX, 0.4, {0,
  //        0, 0}, {1, 1, 1}};

  //        Light light6{{0, -8, 14}, {255 / 255.0f, 236 / 255.0f, 156 /
  //        255.0f}, FLT_MAX, 1.5, {5, 5, 0}, {10, 10, 1}};

  //        GlobalLight light9{{0, 0, -1}, Color::white(), 1};

  //        PointLight light4{{0, -15, 8}, {1,1,1}, 50, 0.4};

  //	Square sq{{0, -15, 9.999f}, {{-90 * DEG_TO_RAD, 0, 0}}, 5};

  //        sq2.setColor({3, 3, 3});

//          Cube cube2{glm::vec3{4, -4, 0}, {{0 * DEG_TO_RAD, 0 * DEG_TO_RAD,
//          -28 * DEG_TO_RAD}}, 6.6f}; Cube cube3{glm::vec3{4, -4, 6.6}, {{0 *
//          DEG_TO_RAD, 0 * DEG_TO_RAD, -28 * DEG_TO_RAD}}, 6.6f};
//  ////        plane4.setReflection(.5f);
  //
  //
  //
  //        Plane planeWhite2{{0, 200, 200}, {0, -0.5, -1}, Color::skyBlue()};;
  //
//          cube2.setReflection(0.3f);
//          cube3.setReflection(0.3f);

  //        Sphere sphere2{{5, 5, -5}, 5, Color::gold()};
  //	plane1.setReflection(0);
  //	plane2.setReflection(0);
  //	plane3.setReflection(0);
  //	plane4.setReflection(0);
  //	plane5.setReflection(0);
  //	plane6.setReflection(0);

//  SDLDisplayer::display(width, height);
  return 0;
}