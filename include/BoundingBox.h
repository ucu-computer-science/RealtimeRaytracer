#pragma once

#include "GraphicalObject.h"
#include "glm/vec3.hpp"
#include "Ray.h"


class AABB
{
public:
	glm::vec3 min, max;

	AABB() : min(), max() { }
	AABB(glm::vec3 min, glm::vec3 max): min(min), max(max) { }

	bool intersects(const Ray& ray, float tMin = FLT_MIN, float tMax = FLT_MAX) const;
	static AABB getUnitedBox(const AABB& box1, const AABB& box2);
};

class BVHNode : GraphicalObject
{
	AABB box;
	std::shared_ptr<BVHNode> left;
	std::shared_ptr<BVHNode> right;
	bool isLeaf;
	std::shared_ptr<GraphicalObject> leafObj;

	 bool includeInBVH() override { return true; }

public:
	BVHNode(std::vector<std::shared_ptr<GraphicalObject>>& objects, size_t start, size_t end);

	bool intersect(Ray& ray, bool intersectAll = false) override;

	inline static BVHNode* root;
	static void buildTree(const std::vector<std::shared_ptr<GraphicalObject>>& objects);
};
