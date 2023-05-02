#pragma once

#include <glm/vec3.hpp>
#include "GraphicalObject.h"


class AABB
{
public:
	glm::vec3 min, max;

	AABB() : min(), max() { }
	AABB(glm::vec3 min, glm::vec3 max): min(min), max(max) { }

	bool intersects(const Ray& ray, float tMin = -FLT_MAX, float tMax = FLT_MAX) const;
	static AABB getUnitedBox(const AABB& box1, const AABB& box2);
};

class BVHNode
{
public:
	int nodeArrayIndex = -1;

	AABB box;
	int leftInd, rightInd;
	bool isLeaf = false;
	int leafTrianglesStart, leafTriangleCount;
	int hitNext = -1, missNext = -1;

	BVHNode(std::vector<std::shared_ptr<BVHNode>>& nodes, std::vector<Triangle*>& triangles, int start, int end, int maxTrianglesPerBox, int nextRightNode = -1);
	size_t getSplitIndex(std::vector<Triangle*>& triangles, size_t start, size_t end) const;

	bool intersect(Ray& ray, bool intersectAll = false) const;
};
