#include "Light.h"

#include <iostream>

#include "Raycast.h"
#include "Scene.h"

PointLight::PointLight(glm::vec3 pos, Color color, float distance,
             float intensity)
    : Object(pos, {{0, 0, 0}}), distance(distance), intensity(intensity), color(intensity * color){

  Scene::lights.emplace_back(this);

}
void PointLight::getIlluminationAtPoint(const glm::vec3 &interPoint,
                                         const glm::vec3 &surfaceNorm,
                                         Color &inColor) {
  auto dist = length(pos - interPoint);

  if (dist > distance) {
    return;
  }

  auto dir = normalize(pos - interPoint);

  if (Raycast::castShadowRays({pos, -dir, dist}))
    return;

  auto distanceImpact = std::min(1 - (dist / distance), 1.f);
  auto lightFacingAtPoint = std::max(dot(dir, surfaceNorm), 0.f);

  inColor += (distanceImpact * lightFacingAtPoint) * color;

}

void Light::getIlluminationAtPoint(const glm::vec3 &interPoint,
                                    const glm::vec3 &surfaceNorm,
                                    Color &inColor) {

  for (const auto &lightPoint : points) {

    auto dist = length(lightPoint - interPoint);

    if (dist > distance) {
      continue;
    }

    auto dir = normalize(lightPoint - interPoint);

    if (Raycast::castShadowRays({lightPoint, -dir, dist}))
      continue;

    auto distanceImpact = std::max(1 - (dist / distance), 0.f);
    auto lightFacingAtPoint = std::max(dot(dir, surfaceNorm), 0.f);

    inColor += (distanceImpact * lightFacingAtPoint) * color;

  }
}

Light::Light(glm::vec3 pos, Color color, float distance,
             float intensity, glm::vec3 size, glm::vec3 pointSize)
    : PointLight(pos, color, distance, intensity), size(size),
      pointSize(pointSize) {

  float dx = size.x / pointSize.x;
  float dy = size.y / pointSize.y;
  float dz = size.z / pointSize.z;
  for (int x = 0; x < pointSize.x; ++x) {
    for (int y = 0; y < pointSize.y; ++y) {
      for (int z = 0; z < pointSize.z; ++z) {
        auto point = pos - size / 2.0f + glm::vec3(x * dx, y * dy, z * dz);
        points.emplace_back(point);
      }
    }
  }
  this->intensity /= points.size();
  this->color /= points.size();
}

Color getIlluminationAtPoint(const glm::vec3 &interPoint, const glm::vec3 &surfaceNorm) {
  Color color{};

  for (const auto light : Scene::lights) {
     light->getIlluminationAtPoint(interPoint, surfaceNorm, color);
  }
  return color;
}
void GlobalLight::getIlluminationAtPoint(const glm::vec3 &interPoint,
                                         const glm::vec3 &surfaceNorm,
                                         Color &inColor) {
  if (Raycast::castShadowRays({interPoint, pos, FLT_MAX}))
    return;
  auto lightFacingAtPoint = std::max(dot(pos, surfaceNorm), 0.f);
  inColor += lightFacingAtPoint * color;
}