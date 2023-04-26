#include "SceneParser.h"

using json = nlohmann::json;

SceneParser::SceneParser() {
}

void SceneParser::ParseScene(std::string path) {
    std::ifstream file(path);
    json j;
    file >> j;
    Camera* camera = new Camera(glm::vec3((float)j["Cameras"][0]["pos"][0], (float)j["Cameras"][0]["pos"][1], (float)j["Cameras"][0]["pos"][2]), (float)j["Cameras"][0]["fov"], glm::vec2((float)j["Cameras"][0]["size"][0], (float)j["Cameras"][0]["size"][1]));
    for (auto light: j["PointLights"]){
        PointLight* light1 = new PointLight{
                {(float)light["pos"][0], (float)light["pos"][1], (float)light["pos"][2]}, {(float)light["color"][0], (float)light["color"][1], (float)light["color"][2]}, (float)light["distance"], (float)light["intensity"]};
    }

    for (auto plane: j["Planes"]){
        Plane* plane1 = new Plane{
                {(float)plane["pos"][0], (float)plane["pos"][1], (float)plane["pos"][2]},
                {(float)plane["normal"][0], (float)plane["normal"][1], (float)plane["normal"][2]},
                Color{(float)plane["material"]["color"][0], (float)plane["material"]["color"][1], (float)plane["material"]["color"][2]}};
        plane1->setMaterial(AssignMaterial(plane["material"]));

    }
    for (auto cube: j["Cubes"]){
        Cube* cube1 = new Cube{
                {(float)cube["pos"][0], (float)cube["pos"][1], (float)cube["pos"][2]},
                {(float)cube["rot"][1], (float)cube["rot"][2], (float)cube["rot"][3], (float)cube["rot"][0]}, (float)cube["side"]};
        cube1->setMaterial(AssignMaterial(cube["material"]));
    }
    for (auto sphere: j["Spheres"]) {
        Sphere *sphere1 = new Sphere{
                {(float) sphere["pos"][0], (float) sphere["pos"][1], (float) sphere["pos"][2]},
                (float) sphere["radius"],
                Color{(float) sphere["material"]["color"][0], (float) sphere["material"]["color"][1], (float) sphere["material"]["color"][2]}
        };
        sphere1->setMaterial(AssignMaterial(sphere["material"]));
    }

    for (auto importedobj: j["ImportedGraphicalObjects"]) {
        ImportedGraphicalObject *importedobj1 = new ImportedGraphicalObject{
                (std::string)importedobj["importPath"]};
                importedobj1->setMaterial(AssignMaterial(importedobj["material"]));
        };


    std::cout << "Scene parsed" << std::endl;

}


Material SceneParser::AssignMaterial(json material){
    Material mat;
    mat.alpha = (float)material["alpha"];
    mat.lit = (float)material["lit"];
    mat.diffuseCoeff = (float)material["diffuseCoeff"];
    mat.specularCoeff = (float)material["specularCoeff"];
    mat.specularDegree = (float)material["specularDegree"];
    mat.reflection = (float)material["reflection"];
    mat.color[0] =  (float)material["color"][0];
    mat.color[1] =  (float)material["color"][1];
    mat.color[2] =  (float)material["color"][2];
    return mat;
}

void SceneParser::RecordScene(const std::vector<std::shared_ptr<Object>> objects, std::string path){
    json j;
    for (auto obj: objects){
        auto info = obj->toJson();
        j[std::string(info["type"]) + "s"].emplace_back(info);
    }
    return recordJson(j, path);
}

void SceneParser::recordJson(json j, std::string path){
    std::ofstream file(path);
    file << j;
    file.close();
    std::cout << "JSON data written to file.\n";
}