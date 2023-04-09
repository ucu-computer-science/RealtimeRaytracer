#pragma once

#include <vector>

class Object;
class GraphicalObject;
class PointLight;


class Scene
{
public:
	inline static std::vector<Object*> objects{};
	inline static std::vector<GraphicalObject*> graphicalObjects{};
        inline static std::vector<PointLight*> lights{};

};