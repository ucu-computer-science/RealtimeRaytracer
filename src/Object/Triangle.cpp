#include "Triangle.h"

#include "Ray.h"
#include "BoundingBoxes.h"

void Triangle::recalculateCoefficients()
{
	texVecU = vertices[1].uvPos - vertices[0].uvPos;
	texVecV = vertices[2].uvPos - vertices[0].uvPos;
#if INTERSECTION_METHOD==MOLLER
    auto p1 = globalVertexPositions[0], p2 = globalVertexPositions[1], p3 = globalVertexPositions[2];
    e1 = p2 - p1;
    e2 = p3 - p1;
#elif INTERSECTION_METHOD==BALDWIN

	auto p1 = globalVertexPositions[0], p2 = globalVertexPositions[1], p3 = globalVertexPositions[2];
	auto e1 = p2 - p1;
	auto e2 = p3 - p1;
	auto normal = obj->getRot() * cross(vertices[1].pos - vertices[0].pos, vertices[2].pos - vertices[1].pos);

	// Depending on which component of the normal is largest, calculate
	// coefficients:
	if (fabs(normal.x) > fabs(normal.y) && fabs(normal.x) > fabs(normal.z))
	{
		row1 = {0.0f, e2.z / normal.x, -e2.y / normal.x};
		valRow1 = cross(p3, p1).x / normal.x;
		row2 = {0.0f, -e1.z / normal.x, e1.y / normal.x};
		valRow2 = -cross(p2, p1).x / normal.x;
		row3 = {1.0f, normal.y / normal.x, normal.z / normal.x};
		valRow3 = -dot(p1, normal) / normal.x;
	}
	else if (fabs(normal.y) > fabs(normal.z))
	{
		row1 = {-e2.z / normal.y, 0.0f, e2.x / normal.y};
		valRow1 = cross(p3, p1).y / normal.y;
		row2 = {e1.z / normal.y, 0.0f, -e1.x / normal.y};
		valRow2 = -cross(p2, p1).y / normal.y;
		row3 = {normal.x / normal.y, 1.0f, normal.z / normal.y};
		valRow3 = -dot(p1, normal) / normal.y;
	}
	else if (fabs(normal.z) > 0.0f)
	{
		row1 = {e2.y / normal.z, -e2.x / normal.z, 0.0f};
		valRow1 = cross(p3, p1).z / normal.z;
		row2 = {-e1.y / normal.z, e1.x / normal.z, 0.0f};
		valRow2 = -glm::cross(p2, p1).z / normal.z;
		row3 = {normal.x / normal.z, normal.y / normal.z, 1.0f};
		valRow3 = -dot(p1, normal) / normal.z;
	}
	else
	{
		// This triangle is degenerate. Set the transformation matrix to
		// the 0 matrix, which in turn will yield 0 values in places that
		// intersection calculations will detect and treat as a miss.
		row1 = {};
		valRow1 = 0.0f;
		row2 = {};
		valRow2 = 0.0f;
		row3 = {};
		valRow3 = 0.0f;
	}
#endif
}

Triangle::Triangle(GraphicalObject* obj, Vertex v1, Vertex v2, Vertex v3, bool isTwoSided) : vertices({v1, v2, v3}),
                                                                                             localNormal(normalize(cross(v2.pos - v1.pos, v3.pos - v2.pos))),
                                                                                             isTwoSided(isTwoSided)
{
	for (auto& v : vertices)
	{
		if (v.normal == glm::vec3(0, 0, 0))
			v.normal = localNormal;
	}

	if (obj != nullptr)
		attachTo(obj);
}
void Triangle::attachTo(GraphicalObject* obj)
{
	this->obj = obj;

	updateGeometry();
}

bool Triangle::intersect(Ray& ray, bool intersectAll)
{

#if INTERSECTION_METHOD==BALDWIN

	const float dz = dot(row3, ray.dir);
	if (dz == 0.0f)
		return false;

	const float oz = dot(row3, ray.pos) + valRow3;
	const float t = -oz / dz;
	if (t < 0 || ray.closestT < t || t >= ray.maxDist)
		return false;

	const auto hit = ray.pos + ray.dir * t;
	const float u = dot(row1, hit) + valRow1;
	if (u < 0.0f || u > 1.0f)
		return false;

	const float v = dot(row2, hit) + valRow2;
	if (v < 0.0f || u + v > 1.0f)
		return false;

	ray.closestT = t;
	ray.closestMat = &obj->material;
	ray.surfaceNormal = getNormalAt(u, v, dot(globalNormal, ray.dir) > 0);
	ray.interPoint = hit;
	ray.closestT = t;
	ray.color = getColorAt(u, v);
	return true;
#elif INTERSECTION_METHOD==MOLLER
    	const float EPSILON = 0.0000001f;

		glm::vec3 h = cross(ray.dir, (e2));
		float a = dot(e1, h);
		if (a > -EPSILON && a < EPSILON)
			return false;    // This ray is parallel to this triangle.
		float f = 1.0f / a;
		glm::vec3 s = ray.pos - globalVertexPositions[0];
		float u = f * dot(s, h);
		if (u < 0.0f || u > 1.0f)
			return false;
		glm::vec3 q = cross(s, e1);
		float v = f * dot(ray.dir, q);
		if (v < 0.0f || u + v > 1.0f)
			return false;
		// At this stage we can compute t to find out where the intersection point is on the line.
		float t = f * dot(e2, q);
		if (t > EPSILON && ray.closestT > t) // ray intersection
		{
            ray.closestT = t;
            ray.closestMat = &obj->material;
            ray.surfaceNormal = getNormalAt(u, v, dot(globalNormal, ray.dir) > 0);
            ray.interPoint = ray.pos + ray.dir * t;
            ray.color = getColorAt(u, v);
            return true;
		}
		return false;
		//else // This means that there is a line intersection but not a ray intersection.
			//return false;
#endif
}

Color Triangle::getColorAt(float u, float v) const
{
	auto d = vertices[0].uvPos + u * texVecU + v * texVecV;
	return obj->material.texture->getColor(d.x, 1 - d.y);
}
glm::vec3 Triangle::getNormalAt(float u, float v, bool invert) const
{
	auto interpolatedNormal = normalize((1 - u - v) * globalVertexNormals[0] + u * globalVertexNormals[1] + v * globalVertexNormals[2]);
	return invert ? -interpolatedNormal : interpolatedNormal;
}

AABB Triangle::getBoundingBox() const
{
	float x_min = FLT_MAX, x_max = -FLT_MAX;
	float y_min = FLT_MAX, y_max = -FLT_MAX;
	float z_min = FLT_MAX, z_max = -FLT_MAX;

	for (const auto& pos : globalVertexPositions)
	{
		x_min = std::min(x_min, pos.x);
		x_max = std::max(x_max, pos.x);

		y_min = std::min(y_min, pos.y);
		y_max = std::max(y_max, pos.y);
		z_min = std::min(z_min, pos.z);
		z_max = std::max(z_max, pos.z);
	}
	return {{x_min - 0.05f, y_min - 0.05f, z_min - 0.05f}, {x_max + 0.05f, y_max + 0.05f, z_max + 0.05f}};
}

glm::vec3 Triangle::getCenter() const
{
	return (globalVertexPositions[0] + globalVertexPositions[1] + globalVertexPositions[2]) * 0.333f;
}

void Triangle::updateGeometry()
{
	globalVertexPositions = {
		obj->getRot() * vertices[0].pos + obj->getPos(),
		obj->getRot() * vertices[1].pos + obj->getPos(),
		obj->getRot() * vertices[2].pos + obj->getPos()
	};

	globalNormal = obj->getRot() * localNormal;

	globalVertexNormals = {
		obj->getRot() * vertices[0].normal,
		obj->getRot() * vertices[1].normal,
		obj->getRot() * vertices[2].normal
	};

	recalculateCoefficients();
}