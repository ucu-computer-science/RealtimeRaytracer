#pragma once

class AABB;
struct Ray;

class IIntersectable
{
public:
	virtual bool includeInBVH() { return true; }

	virtual bool intersect(Ray& ray, bool intersectAll = false) = 0;
	virtual AABB getBoundingBox() const = 0;
	virtual glm::vec3 getCenter() const = 0;
};
