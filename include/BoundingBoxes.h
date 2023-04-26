#pragma once

#include "GraphicalObject.h"
#include "glm/vec3.hpp"
#include <cfloat>

class IBoundable;

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
	inline static constexpr int maxTrianglesPerBox = 5;

	AABB box;
	std::shared_ptr<BVHNode> left;
	std::shared_ptr<BVHNode> right;
	bool isLeaf = false;
	std::vector<IBoundable*> leafIntersectables{};

public:
	BVHNode(std::vector<IBoundable*>& intersectables, size_t start, size_t end);
	size_t getSplitIndex(std::vector<IBoundable*>& intersectables, size_t start, size_t end) const;
	~BVHNode() { boxCount--; }

	bool intersect(Ray& ray, bool intersectAll = false) const;

	inline static std::shared_ptr<BVHNode> root;
	static std::shared_ptr<BVHNode> buildTree(const std::vector<IBoundable*>& intersectables);


	// Debugging
	inline static bool showBoxes = false;
	inline static float lineWidth = 0.03f;
	inline static int boxCount = 0;
	//bool intersectForVisual(Ray& ray);

	void dfs(const std::string& path = "") const;
};
