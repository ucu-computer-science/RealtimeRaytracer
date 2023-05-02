#include "BoundingBoxes.h"

#include <algorithm>

#include "Ray.h"
#include "Scene.h"
#include "Triangle.h"


void BVHBuilder::initializeBVH()
{
	buildTree(Scene::triangles);
}


void BVHBuilder::buildTree(const std::vector<Triangle*>& objects)
{
	nodes.clear();

	nodes.push_back(nullptr);
	nodes[0] = std::make_shared<BVHNode>(nodes, Scene::triangles, 0, Scene::triangles.size() - 1, maxTrianglesPerBox);
}


AABB AABB::getUnitedBox(const AABB& box1, const AABB& box2)
{
	auto x_min = std::min(box1.min.x, box2.min.x);
	auto x_max = std::max(box1.max.x, box2.max.x);

	auto y_min = std::min(box1.min.y, box2.min.y);
	auto y_max = std::max(box1.max.y, box2.max.y);

	auto z_min = std::min(box1.min.z, box2.min.z);
	auto z_max = std::max(box1.max.z, box2.max.z);
	return {{x_min, y_min, z_min}, {x_max, y_max, z_max}};
}

bool AABB::intersects(const Ray& ray, float tMin, float tMax) const
{
	for (int i = 0; i < 3; i++)
	{
		auto invD = 1.0f / ray.dir[i];
		auto t0 = (min[i] - ray.pos[i]) * invD;
		auto t1 = (max[i] - ray.pos[i]) * invD;
		if (invD < 0.0f)
			std::swap(t0, t1);

		tMin = t0 > tMin ? t0 : tMin;
		tMax = t1 < tMax ? t1 : tMax;
		if (tMax <= tMin)
			return false;
	}
	return tMax > 0;
}

BVHNode::BVHNode(std::vector<std::shared_ptr<BVHNode>>& nodes, std::vector<Triangle*>& triangles,
                 int start, int end, int maxTrianglesPerBox, int nextRightNode)
{
	missNext = nextRightNode;
	if (end - start < maxTrianglesPerBox)
	{
		isLeaf = true;
		hitNext = missNext;
		leafTrianglesStart = start;
		leafTriangleCount = end - start + 1;
		box = triangles[start]->getBoundingBox();
		for (int i = start + 1; i <= end; ++i)
			box = AABB::getUnitedBox(box, triangles[i]->getBoundingBox());
		return;
	}

	size_t splitIdx = getSplitIndex(triangles, start, end);

	leftInd = (int)BVHBuilder::nodes.size();
	rightInd = (int)BVHBuilder::nodes.size() + 1;
	hitNext = leftInd;

	nodes.push_back(nullptr);
	nodes.push_back(nullptr);
	nodes[leftInd] = std::make_shared<BVHNode>(nodes, triangles, start, splitIdx, maxTrianglesPerBox, rightInd);
	nodes[rightInd] = std::make_shared<BVHNode>(nodes, triangles, splitIdx + 1, end, maxTrianglesPerBox, nextRightNode);


	box = AABB::getUnitedBox(nodes[leftInd]->box, nodes[rightInd]->box);
}

int BVHNode::getSplitIndex(std::vector<Triangle*>& triangles, int start, int end) const
{
	glm::vec3 min{FLT_MAX}, max{-FLT_MAX};
	for (size_t i = start; i <= end; i++)
	{
		auto pos = triangles[i]->getCenter();
		min.x = std::min(min.x, pos.x);
		min.y = std::min(min.y, pos.y);
		min.z = std::min(min.z, pos.z);

		max.x = std::max(max.x, pos.x);
		max.y = std::max(max.y, pos.y);
		max.z = std::max(max.z, pos.z);
	}
	auto range = max - min;
	int axis = 0;
	if (range.y > range.x) axis = 1;
	if (range.z > range[axis]) axis = 2;
	float splitPos = min[axis] + range[axis] * 0.5f;

	std::sort(triangles.begin() + start, triangles.begin() + end + 1,
	          [axis](auto a, auto b) { return a->getCenter()[axis] < b->getCenter()[axis]; });
	auto splitIdx = start;
	while (triangles[splitIdx]->getCenter()[axis] < splitPos && splitIdx < end - 1) splitIdx++;
	return splitIdx;
}


bool BVHNode::intersect(Ray& ray) const
{
	if (!box.intersects(ray))
		return false;

	if (isLeaf)
	{
		bool hit = false;
		for (int i = leafTrianglesStart; i < leafTrianglesStart + leafTriangleCount; i++)
		{
			if (!Scene::triangles[i]->intersect(ray)) continue;
			hit = true;
		}
		return hit;
	}

	auto hitLeft = Scene::triangles[leftInd]->intersect(ray);
	auto hitRight = Scene::triangles[rightInd]->intersect(ray);
	return hitLeft || hitRight;
}
