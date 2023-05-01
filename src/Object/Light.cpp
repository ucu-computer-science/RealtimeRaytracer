#include "Light.h"

#include "GraphicalObject.h"
#include "Material.h"
#include "Raycast.h"
#include "Scene.h"


Light::Light(const glm::vec3& pos, const Color& color, float intensity) : Object(pos), color(color), intensity(intensity), colorIntensified(color * intensity)
{
	Scene::lights.emplace_back(this);
}

nlohmann::basic_json<> Light::toJson()
{
	auto j = Object::toJson();
	j["color"][0] = color[0];
	j["color"][1] = color[1];
	j["color"][2] = color[2];
	j["intensity"] = intensity;
	return j;
}

PointLight::PointLight(glm::vec3 pos, Color color, float intensity, float distance) : Light(pos, color, intensity), distance(distance) { }

void PointLight::getIlluminationAtPoint(const Ray& ray, Color& inColor, Color& inSpecular)
{
	auto dir = pos - ray.interPoint;
	auto dist = length(dir);
	if (dist > distance)
		return;

	dir = normalize(dir);
	if (Raycast::castShadowRays({pos, -dir, dist}))
		return;

	auto distanceImpact = (float)std::min(1 - (dist / distance), 1.f);
	auto lightFacingAtPoint = std::max(dot(dir, ray.surfaceNormal), 0.f);
	inColor += (distanceImpact * lightFacingAtPoint) * colorIntensified;

	auto h = normalize(dir - ray.dir);
	inSpecular += distanceImpact * (float)std::pow(std::max(dot(h, ray.surfaceNormal), 0.0f), ray.closestMat->specularDegree) * colorIntensified;
}

nlohmann::basic_json<> PointLight::toJson()
{
	auto j = Light::toJson();
	j["type"] = "PointLight";
	j["distance"] = distance;
	return j;
};

AreaLight::AreaLight(glm::vec3 pos, Color color, float intensity, float distance, glm::vec3 size, glm::vec3 pointSize) : Light(pos, color, intensity),
distance(distance), size(size), pointSize(pointSize)
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
	colorIntensified /= (float)points.size();
}

void AreaLight::getIlluminationAtPoint(const Ray& ray, Color& inColor, Color& inSpecular)
{
	for (const auto& lightPoint : points)
	{
		auto dist = length(lightPoint - ray.interPoint);
		if (dist > distance)
			continue;

		auto dir = normalize(lightPoint - ray.interPoint);
		if (Raycast::castShadowRays({/*getPos()*/lightPoint, -dir, dist}))
			continue;

		auto distanceImpact = (float)std::max(1 - (dist / distance), 0.f);
		auto lightFacingAtPoint = std::max(dot(dir, ray.surfaceNormal), 0.f);
		inColor += distanceImpact * lightFacingAtPoint * colorIntensified;

		auto H = normalize(dir - ray.dir);
		inSpecular += distanceImpact * (float)std::pow(std::max(dot(H, ray.surfaceNormal), 0.0f), ray.closestMat->specularDegree) * colorIntensified;
	}
}

nlohmann::basic_json<> AreaLight::toJson()
{
	auto j = Light::toJson();
	j["type"] = "AreaLight";
	j["size"][0] = size[0];
	j["size"][1] = size[1];
	j["size"][2] = size[2];
	j["pointSize"][0] = pointSize[0];
	j["pointSize"][1] = pointSize[1];
	j["pointSize"][2] = pointSize[2];
	return j;
};

GlobalLight::GlobalLight(glm::vec3 direction, Color color, float intensity) : Light({}, color, intensity), direction(direction) {}

void GlobalLight::getIlluminationAtPoint(const Ray& ray, Color& inColor, Color& inSpecular)
{
	if (Raycast::castShadowRays({ray.interPoint, direction, FLT_MAX}))
		return;

	auto light = std::max(dot(direction, ray.surfaceNormal), 0.f);
	inColor += light * colorIntensified;

	auto h = normalize(direction - ray.dir);
	inSpecular += (float)std::pow(std::max(dot(h, ray.surfaceNormal), 0.0f), ray.closestMat->specularDegree) * colorIntensified;
}
EverywhereLight::EverywhereLight(const Color& color, float intensity): Light({}, color, intensity) {}

void EverywhereLight::getIlluminationAtPoint(const Ray& ray, Color& inColor, Color& inSpecular)
{
	inColor += colorIntensified;
}


std::pair<Color, Color> getIlluminationAtPoint(const Ray& ray)
{
	Color diffuse{};
	Color specular{};
	for (const auto& light : Scene::lights)
	{
		light->getIlluminationAtPoint(ray, diffuse, specular);
	}
	return {diffuse, specular};
}
