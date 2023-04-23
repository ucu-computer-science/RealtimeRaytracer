#pragma once

#include <vector>

class Object;
class GraphicalObject;
class PointLight;

class Scene
{
public:
	inline static std::vector<std::shared_ptr<Object>> objects{};
	inline static std::vector<std::shared_ptr<GraphicalObject>> graphicalObjects{};
	inline static std::vector<std::shared_ptr<PointLight>> lights{};
};
