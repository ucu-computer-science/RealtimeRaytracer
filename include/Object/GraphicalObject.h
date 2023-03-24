#pragma once

#include <vector>
#include "Object.h"

class Triangle;

class GraphicalObject : public Object
{
public:
	std::vector<Triangle*> triangles{};

	GraphicalObject(Vec3 pos);
};
