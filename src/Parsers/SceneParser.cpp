#include "SceneParser.h"

#include <fstream>
#include <iostream>

#include "Light.h"

using json = nlohmann::json;

void SceneParser::parseScene(const std::filesystem::path& path)
{
	std::ifstream file(path);
	json j;
	file >> j;
	auto camera = new Camera(glm::vec3((float)j["Cameras"][0]["pos"][0], (float)j["Cameras"][0]["pos"][1], (float)j["Cameras"][0]["pos"][2]),
	                         (float)j["Cameras"][0]["fov"], (float)j["Cameras"][0]["lensRadius"],
	                         glm::vec2((float)j["Cameras"][0]["size"][0], (float)j["Cameras"][0]["size"][1]));
	for (auto light : j["PointLights"])
	{
		auto light1 = new PointLight{
			{(float)light["pos"][0], (float)light["pos"][1], (float)light["pos"][2]},
			{(float)light["color"][0], (float)light["color"][1], (float)light["color"][2]}, (float)light["distance"], (float)light["intensity"]
		};
	}

	for (auto plane : j["Planes"])
	{
		auto plane1 = new Plane{
			{(float)plane["normal"][0], (float)plane["normal"][1], (float)plane["normal"][2]},
			{(float)plane["pos"][0], (float)plane["pos"][1], (float)plane["pos"][2]}
		};
		plane1->material = loadMaterial(plane["material"]);
	}
	for (auto cube : j["Cubes"])
	{
		auto cube1 = new Cube{
			{(float)cube["pos"][0], (float)cube["pos"][1], (float)cube["pos"][2]},
			(float)cube["side"],
			{(float)cube["rot"][1], (float)cube["rot"][2], (float)cube["rot"][3], (float)cube["rot"][0]}
		};
		cube1->material = loadMaterial(cube["material"]);
	}
	for (auto sphere : j["Spheres"])
	{
		auto sphere1 = new Sphere{
			{(float)sphere["pos"][0], (float)sphere["pos"][1], (float)sphere["pos"][2]},
			(float)sphere["radius"]
		};
		sphere1->material = loadMaterial(sphere["material"]);
	}

	//for (auto importedObj : j["ImportedGraphicalObjects"])
	//{
	//	auto importPath = importedObj["importPath"];
	//	auto importedObj1 = new ImportedGraphicalObject(importPath);
	//	importedObj1->setMaterial(assignMaterial(importedObj["material"]));
	//}

	std::cout << "Scene parsed" << std::endl;
}

Material* SceneParser::loadMaterial(const json& material)
{
	auto mat = new Material();
	mat->color[0] = (float)material["color"][0];
	mat->color[1] = (float)material["color"][1];
	mat->color[2] = (float)material["color"][2];
	if (!material["texturePath"].empty())
		mat->texture = new Texture(material["texturePath"]);
	mat->lit = (bool)material["lit"];
	mat->diffuseCoeff = (float)material["diffuseCoeff"];
	mat->specularCoeff = (float)material["specularCoeff"];
	mat->specularDegree = (float)material["specularDegree"];
	mat->reflection = (float)material["reflection"];
	return mat;
}

void SceneParser::saveScene(const std::vector<Object*>& objects, const std::filesystem::path& path)
{
	json j;
	for (const auto& obj : objects)
	{
		auto info = obj->toJson();
		j[std::string(info["type"]) + "s"].emplace_back(info);
	}
	return writeToJson(j, path);
}

void SceneParser::writeToJson(const json& j, const std::filesystem::path& path)
{
	std::ofstream file(path);
	file << j;
	file.close();
	std::cout << "JSON data written to file.\n";
}
