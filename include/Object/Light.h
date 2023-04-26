#pragma once

#include <vector>

#include "Color.h"
#include "Object.h"
#include "Ray.h"

class PointLight : public Object
{
public:
	float distance;
	float intensity;
	Color color;
	PointLight(glm::vec3 pos, Color color, float distance, float intensity);
	virtual void getIlluminationAtPoint(const Ray& ray, Color& inColor, Color& inSpecular);

    nlohmann::basic_json<> toJson() override;
};

class Light : public PointLight
{
private:
	std::vector<glm::vec3> points;

public:
    glm::vec3 size;
    glm::vec3 pointSize;
	Light(glm::vec3 pos, Color color, float distance, float intensity,
	      glm::vec3 size,
	      glm::vec3 pointSize); //: PointLight(pos, color, distance, intensity);
	void getIlluminationAtPoint(const Ray& ray, Color& inColor, Color& inSpecular) override;

    nlohmann::basic_json<> toJson() override;
};

class GlobalLight : public PointLight
{
public:
	// pos is the inverse direction of the light
	GlobalLight(glm::vec3 dirInv, Color color, float intensity) : PointLight(
		normalize(dirInv), color, FLT_MAX, intensity) {}
	void getIlluminationAtPoint(const Ray& ray, Color& inColor, Color& inSpecular) override;
};

std::pair<Color, Color> getIlluminationAtPoint(const Ray& ray);
