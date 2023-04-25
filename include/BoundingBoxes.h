#pragma once

#include "GraphicalObject.h"
#include "glm/vec3.hpp"
#include "Ray.h"

class IIntersectable;

class AABB
{
public:
	glm::vec3 min, max;

	AABB() : min(), max() { }
	AABB(glm::vec3 min, glm::vec3 max): min(min), max(max) { }

	bool intersects(const Ray& ray, float tMin = -FLT_MAX, float tMax = FLT_MAX) const;
	static AABB getUnitedBox(const AABB& box1, const AABB& box2);
};

class BVHNode : GraphicalObject
{
	AABB box;
	std::shared_ptr<BVHNode> left;
	std::shared_ptr<BVHNode> right;
	bool isLeaf = false;
	std::shared_ptr<IIntersectable> leafIntersectable;

	// Visual
	inline static bool showBoxes = false;
	inline static float lineWidth = 0.1f;

public:
	BVHNode(std::vector<std::shared_ptr<IIntersectable>>& intersectables, size_t start, size_t end);
	size_t getSplitIndex(std::vector<std::shared_ptr<IIntersectable>>& intersectables, size_t start, size_t end) const;

	bool intersect(Ray& ray, bool intersectAll = false) override;
	bool intersectForVisual(Ray& ray);

	inline static std::shared_ptr<BVHNode> root;
	static std::shared_ptr<BVHNode> buildTree(const std::vector<std::shared_ptr<IIntersectable>>& intersectables);

	void dfs(const std::string& path = "") const;
};
