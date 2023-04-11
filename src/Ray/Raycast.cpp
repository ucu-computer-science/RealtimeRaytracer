#include "Raycast.h"

#include "Camera.h"
#include "GraphicalObject.h"
#include "Light.h"
#include "Ray.h"
#include "Scene.h"

Color Raycast::castRay(Ray ray, int bounce) {
  Color color{0, 0, 0};

  bool hit = false;
  float colorImpact = 1;
  for (int i = 0; i < bounce; ++i) {
    for (const auto obj : Scene::graphicalObjects) {
      obj->findIntersectionWith(ray, hit);
    }
    if (!ray.hit())
      break;

    hit = true;
    // this is important. if we dont add this vector ,the ray from the point
    // will sometimes hit the object it just hit by adding this we get our point
    // slightly above the surface, thus there are slightly more directions to
    // hit
    ray.interPoint += ray.surfaceNormal * .001f;
//    auto hitinfo = getIlluminationAtPoint(ray.interPoint, ray.surfaceNormal);
    color += colorImpact * (1 - ray.reflection) * ray.color *
         getIlluminationAtPoint(ray);

    colorImpact *= ray.reflection;
    if (colorImpact <= 1e-6)
      break;
    // TODO specular, diffuse, random rays
    auto dir = ray.dir - (2 * dot(ray.dir, ray.surfaceNormal) *
                          ray.surfaceNormal); //* ((float)(rand()%1000)/1000);
//    color += (ray.color*std::pow(dot(ray.dir, dir), 10))*0.2;
    ray = Ray(ray.interPoint, dir);
  }
  color += colorImpact * Camera::instance->bgColor;
  return hit ? color : Camera::instance->bgColor;
}

bool Raycast::castShadowRays(Ray ray) {
  for (const auto obj : Scene::graphicalObjects) {
    obj->findIntersectionWith(ray, true);
    if (ray.hit())
      return true;
  }
  return false;
}