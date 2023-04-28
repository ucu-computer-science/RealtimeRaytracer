#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "GraphicalObject.h"
#include "Triangle.h"
#include "Camera.h"
#include "Light.h"
#include "Scene.h"

class SceneParser
{
public:
	static void parseScene(const std::filesystem::path& path);

	static void recordScene(const std::vector<Object*>& objects, const std::filesystem::path& path);

	static void writeJson(const nlohmann::basic_json<>& j, const std::filesystem::path&);

	static Material assignMaterial(nlohmann::basic_json<> material);
};