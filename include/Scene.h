#pragma once

#include <vector>

class Light;
class Object;
class GraphicalObject;

class Scene
{
public:
	inline static std::vector<Object*> objects{};
	inline static std::vector<GraphicalObject*> graphicalObjects{};
	inline static std::vector<Light*> lights{};
};
