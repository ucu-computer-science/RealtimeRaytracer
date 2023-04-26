#include <nlohmann/json.hpp>
#include <fstream>
#include "iostream"
#include "GraphicalObject.h"
#include <string>
#include <sstream>
#include "Triangle.h"
#include "Camera.h"
#include "Light.h"
#include "Scene.h"

class SceneParser{
public:
    explicit SceneParser();

    static void ParseScene(std::string);

    static void RecordScene(std::vector<std::shared_ptr<Object>> objects, std::string path);

    static void recordJson(nlohmann::basic_json<> j, std::string path);

    static Material AssignMaterial(nlohmann::basic_json<> material);
};

