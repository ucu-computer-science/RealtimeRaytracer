#pragma once

#include <vector>

#include "Color.h"
#include "Object.h"
#include "Ray.h"

class Light : public Object
{
protected:
	Color color;
	float intensity;

	Color colorIntensified;

	Light(const glm::vec3& pos, const Color& color, float intensity);

public:
	virtual void getIlluminationAtPoint(const Ray& ray, Color& inColor, Color& inSpecular) = 0;

	nlohmann::basic_json<> toJson() override;
};

class PointLight : public Light
{
	float distance;

public:
	PointLight(glm::vec3 pos, Color color, float intensity, float distance);

	void getIlluminationAtPoint(const Ray& ray, Color& inColor, Color& inSpecular) override;

	nlohmann::basic_json<> toJson() override;
};

class AreaLight : public Light
{
	float distance;
	glm::vec3 size;
	glm::vec3 pointSize;

	std::vector<glm::vec3> points;

public:
	AreaLight(glm::vec3 pos, Color color, float distance, float intensity, glm::vec3 size, glm::vec3 pointSize);

	void getIlluminationAtPoint(const Ray& ray, Color& inColor, Color& inSpecular) override;

	nlohmann::basic_json<> toJson() override;
};

class GlobalLight : public Light
{
	glm::vec3 direction;

public:
	GlobalLight(glm::vec3 direction, Color color, float intensity);

	void getIlluminationAtPoint(const Ray& ray, Color& inColor, Color& inSpecular) override;
};

class EverywhereLight : public Light
{
public:
	EverywhereLight(const Color& color, float intensity);

	void getIlluminationAtPoint(const Ray& ray, Color& inColor, Color& inSpecular) override;
};

std::pair<Color, Color> getIlluminationAtPoint(const Ray& ray);
