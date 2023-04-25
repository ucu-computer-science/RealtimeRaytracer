#include "BoundingBoxes.h"

#include <algorithm>

#include "Scene.h"
#include <iostream>


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

BVHNode::BVHNode(std::vector<std::shared_ptr<IIntersectable>>& intersectables, size_t start, size_t end)
{
	material.color = Color::blue();
	material.lit = false;

	if (start == end)
	{
		isLeaf = true;
		leafIntersectable = intersectables[start];
		box = intersectables[start]->getBoundingBox();
		return;
	}

	size_t splitIdx = getSplitIndex(intersectables, start, end);

	this->left = std::make_shared<BVHNode>(intersectables, start, splitIdx);
	this->right = std::make_shared<BVHNode>(intersectables, splitIdx + 1, end);

	box = AABB::getUnitedBox(left->box, right->box);
}
size_t BVHNode::getSplitIndex(std::vector<std::shared_ptr<IIntersectable>>& intersectables, size_t start, size_t end) const
{
	glm::vec3 min{ FLT_MAX }, max{ -FLT_MAX };
	for (size_t i = start; i <= end; i++)
	{
		auto pos = intersectables[i]->getCenter();
		min.x = std::min(min.x, pos.x);
		min.y = std::min(min.y, pos.y);
		min.z = std::min(min.z, pos.z);

		max.x = std::max(max.x, pos.x);
		max.y = std::max(max.y, pos.y);
		max.z = std::max(max.z, pos.z);
	}
	auto size = max - min;
	int axis = 0;
	if (size.y > size.x) axis = 1;
	if (size.z > size[axis]) axis = 2;
	float splitPos = min[axis] + size[axis] * 0.5f;

	std::sort(intersectables.begin() + start, intersectables.begin() + end,
		[axis](auto a, auto b) { return a->getCenter()[axis] < b->getCenter()[axis]; });
	auto splitIdx = start;
	while (intersectables[splitIdx]->getCenter()[axis] < splitPos && splitIdx < end - 1) splitIdx++;
	return splitIdx;
}

bool BVHNode::intersect(Ray& ray, bool intersectAll)
{
	if (!box.intersects(ray))
		return false;

	//Visual
	if (showBoxes)
		intersectForVisual(ray);

	if (isLeaf)
		return leafIntersectable->intersect(ray, intersectAll);

	auto hitLeft = left->intersect(ray, intersectAll);
	auto hitRight = right->intersect(ray, intersectAll);
	return hitLeft || hitRight;
}

bool BVHNode::intersectForVisual(Ray& ray)
{
	auto tMin = -FLT_MAX, tMax = FLT_MAX;
	for (int i = 0; i < 3; i++)
	{
		auto invD = 1.0f / ray.dir[i];
		auto t0 = (box.min[i] - ray.pos[i]) * invD;
		auto t1 = (box.max[i] - ray.pos[i]) * invD;
		if (invD < 0.0f)
			std::swap(t0, t1);

		tMin = t0 > tMin ? t0 : tMin;
		tMax = t1 < tMax ? t1 : tMax;
		if (tMax <= tMin)
			return false;
	}

	for (const auto& t : {tMin, tMax})
	{
		auto point = ray.pos + t * ray.dir;
		if (ray.closestT > tMin && ((std::abs(box.min.x - point.x) <= lineWidth || std::abs(box.max.x - point.x) <= lineWidth ||
				std::abs(box.min.y - point.y) <= lineWidth || std::abs(box.max.y - point.y) <= lineWidth) &&
			(std::abs(box.min.y - point.y) <= lineWidth || std::abs(box.max.y - point.y) <= lineWidth ||
				std::abs(box.min.z - point.z) <= lineWidth || std::abs(box.max.z - point.z) <= lineWidth) &&
			(std::abs(box.min.z - point.z) <= lineWidth || std::abs(box.max.z - point.z) <= lineWidth ||
				std::abs(box.min.x - point.x) <= lineWidth || std::abs(box.max.x - point.x) <= lineWidth)))
		{
			ray.surfaceNormal = {0, 0, 1};
			ray.interPoint = point;
			ray.closestT = t;
			ray.closestObj = this;
			return true;
		}
	}

	return false;
}


std::shared_ptr<BVHNode> BVHNode::buildTree(const std::vector<std::shared_ptr<IIntersectable>>& intersectables)
{
	std::vector<std::shared_ptr<IIntersectable>> filtered{};
	for (const auto& obj : intersectables)
	{
		if (!obj->includeInBVH()) continue;
		filtered.emplace_back(obj);
	}
	return std::make_shared<BVHNode>(filtered, 0, filtered.size() - 1);
}

void BVHNode::dfs(const std::string& path) const
{
	if (isLeaf)
		std::cout << path << "-" << to_string(leafIntersectable->getCenter()) << '\n';
	else
		std::cout << path << '\n';

	if (left)
		left->dfs(path + "-left");
	if (right)
		right->dfs(path + "-right");
}
