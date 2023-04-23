#include "Light.h"

#include "Material.h"
#include "Raycast.h"
#include "Scene.h"


PointLight::PointLight(glm::vec3 pos, Color color, float distance,
                       float intensity) : Object(pos, {{0, 0, 0}}), distance(distance), intensity(intensity),
                                          color(intensity * color)
{
	Scene::lights.emplace_back(this);
}
void PointLight::getIlluminationAtPoint(const Ray& ray, Color& inColor, Color& inSpecular)
{
	auto dir = pos - ray.interPoint;
	auto dist = length(dir);

	if (dist > distance)
		return;

	dir = normalize(dir);

	if (Raycast::castShadowRays({pos, -dir, dist}))
		return;

	auto distanceImpact = std::min(1 - (dist / distance), 1.f);
	auto lightFacingAtPoint = std::max(dot(dir, ray.surfaceNormal), 0.f);

	inColor += (distanceImpact * lightFacingAtPoint) * color;

	// TODO get coefs from material
	auto R = normalize(2 * lightFacingAtPoint * ray.surfaceNormal - (dir));
	inSpecular += distanceImpact * std::pow(std::max(dot(R, -ray.dir), 0.0f), ray.material->specular_degree) * color;
}

void Light::getIlluminationAtPoint(const Ray& ray, Color& inSpecular, Color& inColor)
{
	for (const auto& lightPoint : points)
	{
		auto dist = length(lightPoint - ray.interPoint);

		if (dist > distance)
			continue;

		auto dir = normalize(lightPoint - ray.interPoint);
		if (Raycast::castShadowRays({lightPoint, -dir, dist}))
			continue;

		auto distanceImpact = std::max(1 - (dist / distance), 0.f);
		auto lightFacingAtPoint = std::max(dot(dir, ray.surfaceNormal), 0.f);

		inColor += (distanceImpact * lightFacingAtPoint) * color;

		auto R = normalize(2 * lightFacingAtPoint * ray.surfaceNormal - (dir));
		inSpecular += distanceImpact * std::pow(std::max(dot(R, -ray.dir), 0.0f), ray.material->specular_degree) *
			color;
	}
}

Light::Light(glm::vec3 pos, Color color, float distance, float intensity,
             glm::vec3 size, glm::vec3 pointSize) : PointLight(pos, color, distance, intensity), size(size),
                                                    pointSize(pointSize)
{
	float dx = size.x / pointSize.x;
	float dy = size.y / pointSize.y;
	float dz = size.z / pointSize.z;
	for (int x = 0; x < pointSize.x; ++x)
	{
		for (int y = 0; y < pointSize.y; ++y)
		{
			for (int z = 0; z < pointSize.z; ++z)
			{
				auto point = pos - size / 2.0f + glm::vec3(x * dx, y * dy, z * dz);
				points.emplace_back(point);
			}
		}
	}
	//  this->intensity /= (float)points.size();
	// todo weird multiplication by 2
	this->color = this->color * (2 * intensity / (this->intensity * (float)points.size()));
	//    this->intensity /= points.size();
}

std::pair<Color, Color> getIlluminationAtPoint(const Ray& ray)
{
	Color color{};
	Color specular{};
	for (const auto& light : Scene::lights)
	{
		light->getIlluminationAtPoint(ray, color, specular);
	}
	return {color, specular};
}

void GlobalLight::getIlluminationAtPoint(const Ray& ray, Color& inSpecular, Color& inColor)
{
	if (Raycast::castShadowRays({ray.interPoint, pos, FLT_MAX}))
		return;
	auto lightFacingAtPoint = std::max(dot(pos, ray.surfaceNormal), 0.f);
	inColor += lightFacingAtPoint * color;

	auto R = normalize(2 * lightFacingAtPoint * ray.surfaceNormal - (pos));
	inSpecular += std::pow(std::max(dot(R, -ray.dir), 0.0f), ray.material->specular_degree) * color;
}
