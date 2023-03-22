#pragma once

#include <vector>

class Object;
class GraphicalObject;

class Scene
{
public:
	static std::vector<Object*> objects;
	static std::vector<GraphicalObject*> graphicalObjects;
};

