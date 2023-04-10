#pragma once

#include <vector>

#include "Color.h"
#include "Object.h"

class PointLight : public Object
{


public:
    float distance;
    float intensity;
    Color color;
	PointLight(glm::vec3 pos, Color color, float distance, float intensity);
        virtual void getIlluminationAtPoint(const glm::vec3 &interPoint, const glm::vec3 &surfaceNorm, Color &inColor);

};

class Light: public PointLight {
private:
  glm::vec3 size;
  glm::vec3 pointSize;
  std::vector<glm::vec3> points;
public:
  Light(glm::vec3 pos, Color color, float distance, float intensity, glm::vec3 size, glm::vec3 pointSize);//: PointLight(pos, color, distance, intensity);
  void getIlluminationAtPoint(const glm::vec3 &interPoint, const glm::vec3 &surfaceNorm, Color &inColor) override;
};

class GlobalLight: public PointLight {
public:
  // pos is the inverse direction of the light
  GlobalLight(glm::vec3 dirInv, Color color, float intensity):PointLight(normalize(dirInv), color, FLT_MAX, intensity) {}
  void getIlluminationAtPoint(const glm::vec3 &interPoint, const glm::vec3 &surfaceNorm, Color &inColor) override;
};
Color getIlluminationAtPoint(const glm::vec3 &interPoint, const glm::vec3 &surfaceNorm);