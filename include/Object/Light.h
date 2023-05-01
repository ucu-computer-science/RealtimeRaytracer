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

	Color getColor() const { return color; }
	float getIntensity() const { return intensity; }

	nlohmann::basic_json<> toJson() override;
};

class PointLight : public Light
{
public:
	float distance;

	PointLight(glm::vec3 pos, Color color, float intensity, float distance);

	void getIlluminationAtPoint(const Ray& ray, Color& inColor, Color& inSpecular) override;

	nlohmann::basic_json<> toJson() override;
};

class AreaLight : public Light
{
	std::vector<glm::vec3> points;

public:
	float distance;
	glm::vec3 size;
	glm::vec3 pointSize;

	AreaLight(glm::vec3 pos, Color color, float intensity, float distance, glm::vec3 size, glm::vec3 pointSize);

	void getIlluminationAtPoint(const Ray& ray, Color& inColor, Color& inSpecular) override;

	nlohmann::basic_json<> toJson() override;
};

class GlobalLight : public Light
{
public:
	glm::vec3 direction;

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
