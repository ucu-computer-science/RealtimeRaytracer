#pragma once

#include <glm/vec3.hpp>
#include <cfloat>
#include "GraphicalObject.h"


class GraphicalObject;
class Triangle;
class BVHNode;

class BVHBuilder
{
	inline static constexpr int maxTrianglesPerBox = 3;
	inline static bool showBoxes = false;
	inline static float lineWidth = 0.1f;

public:
	inline static std::vector<std::shared_ptr<BVHNode>> nodes;

	static void initializeBVH();

	static void buildTree(const std::vector<Triangle*>& objects);
};

class AABB
{
public:
	glm::vec3 min, max;

	AABB() : min(), max() { }
	AABB(glm::vec3 min, glm::vec3 max) : min(min), max(max) { }

	bool intersects(const Ray& ray, float tMin = 0, float tMax = FLT_MAX) const;

	static AABB getUnitedBox(const AABB& box1, const AABB& box2);
};

class BVHNode
{
public:
	AABB box;
	int leftInd, rightInd;
	bool isLeaf = false;
	int leafTrianglesStart = 0, leafTriangleCount = 0;
	int hitNext = -1, missNext = -1;

	BVHNode(std::vector<std::shared_ptr<BVHNode>>& nodes, std::vector<Triangle*>& triangles, int start, int end, int maxTrianglesPerBox, int nextRightNode = -1);
	int getSplitIndex(std::vector<Triangle*>& triangles, int start, int end) const;

	bool intersect(Ray& ray) const;
};