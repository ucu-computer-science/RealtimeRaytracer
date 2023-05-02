#include "BVHBuilder.h"

#include "BVHNode.h"
#include "GraphicalObject.h"
#include "Scene.h"

void BVHBuilder::initializeBVH()
{
	buildTree(Scene::graphicalObjects);
}


void BVHBuilder::buildTree(const std::vector<GraphicalObject*>& objects)
{
	std::vector<Triangle*> triangles{};
	for (const auto& obj : objects)
	{
		for (const auto& triangle : obj->triangles)
		{
			triangles.push_back(triangle.get());
		}
	}
	nodes.push_back(nullptr);
	nodes[0] = std::make_shared<BVHNode>(nodes, triangles, 0, triangles.size() - 1, maxTrianglesPerBox);
}
