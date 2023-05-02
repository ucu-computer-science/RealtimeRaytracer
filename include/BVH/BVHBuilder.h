#pragma once
#include <memory>
#include <vector>

class GraphicalObject;
class Triangle;
class BVHNode;

class BVHBuilder
{
	inline static constexpr int maxTrianglesPerBox = 5;
	inline static bool showBoxes = false;
	inline static float lineWidth = 0.1f;

public:
	inline static std::vector<std::shared_ptr<BVHNode>> nodes;

	static void initializeBVH();

	static void buildTree(const std::vector<GraphicalObject*>& objects);
};
