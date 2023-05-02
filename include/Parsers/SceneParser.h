#pragma once

#include <nlohmann/json.hpp>

#include "GraphicalObject.h"
#include "Camera.h"

class SceneParser
{
public:
	static void parseScene(const std::filesystem::path& path);
	static void saveScene(const std::vector<Object*>& objects, const std::filesystem::path& path);

	static void writeToJson(const nlohmann::basic_json<>& j, const std::filesystem::path&);

	static Material* loadMaterial(const nlohmann::basic_json<>& material);
};