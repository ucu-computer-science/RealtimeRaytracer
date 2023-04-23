#include "BoundingBox.h"
#include "Scene.h"
#include <algorithm>


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
	return true;
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

BVHNode::BVHNode(std::vector<std::shared_ptr<GraphicalObject>>& objects, size_t start, size_t end)
{
	if (start == end)
	{
		isLeaf = true;
		leafObj = objects[start];
		objects[start]->getBoundingBox(box);
		return;
	}

	glm::vec3 size = box.max - box.min;
	int axis = 0;
	if (size.y > size.x) axis = 1;
	if (size.z > size[axis]) axis = 2;
	float splitPos = box.min[axis] + size[axis] * 0.5f;

	std::ranges::sort(objects, [axis](auto a, auto b) { return a->getPos()[axis] < b->getPos()[axis]; });
	size_t splitIdx = start;
	while (objects[splitIdx]->getPos()[axis] < splitPos && splitIdx < end - 1) splitIdx++;

	this->left = std::make_shared<BVHNode>(objects, start, splitIdx);
	this->right = std::make_shared<BVHNode>(objects, splitIdx + 1, end);

	box = AABB::getUnitedBox(left->box, right->box);
}

bool BVHNode::intersect(Ray& ray, bool intersectAll)
{
	if (!box.intersects(ray))
		return false;

	if (isLeaf)
		return leafObj->intersect(ray, intersectAll);

	auto hitLeft = left->intersect(ray, intersectAll);
	auto hitRight = right->intersect(ray, intersectAll);
	return hitLeft || hitRight;
}



void BVHNode::buildTree(const std::vector<std::shared_ptr<GraphicalObject>>& objects)
{
	std::vector<std::shared_ptr<GraphicalObject>> filteredObjects{};
	for (const auto& obj : objects)
	{
		if (!obj->includeInBVH()) continue;
		filteredObjects.emplace_back(obj);
	}
	root = new BVHNode(filteredObjects, 0, filteredObjects.size() - 1);
}
