#include "Triangle.h"

#include "BoundingBoxes.h"
#include "Ray.h"

void Triangle::recalculateCoefficients()
{
	texVecU = vertices[1].uvPos - vertices[0].uvPos;
	texVecV = vertices[2].uvPos - vertices[0].uvPos;

	auto p1 = globalVertexPositions[0], p2 = globalVertexPositions[1], p3 = globalVertexPositions[2];
	auto e1 = p2 - p1;
	auto e2 = p3 - p1;
	auto normal = mesh->getRot() * cross(vertices[1].pos - vertices[0].pos, vertices[2].pos - vertices[1].pos);

	// Depending on which component of the normal is largest, calculate
	// coefficients:
	if (fabs(normal.x) > fabs(normal.y) && fabs(normal.x) > fabs(normal.z))
	{
		row1 = {0.0f, e2.z / normal.x, -e2.y / normal.x};
		row1Val = cross(p3, p1).x / normal.x;
		row2 = {0.0f, -e1.z / normal.x, e1.y / normal.x};
		row2Val = -cross(p2, p1).x / normal.x;
		row3 = {1.0f, normal.y / normal.x, normal.z / normal.x};
		row3Val = -dot(p1, normal) / normal.x;
	}
	else if (fabs(normal.y) > fabs(normal.z))
	{
		row1 = {-e2.z / normal.y, 0.0f, e2.x / normal.y};
		row1Val = cross(p3, p1).y / normal.y;
		row2 = {e1.z / normal.y, 0.0f, -e1.x / normal.y};
		row2Val = -cross(p2, p1).y / normal.y;
		row3 = {normal.x / normal.y, 1.0f, normal.z / normal.y};
		row3Val = -dot(p1, normal) / normal.y;
	}
	else if (fabs(normal.z) > 0.0f)
	{
		row1 = {e2.y / normal.z, -e2.x / normal.z, 0.0f};
		row1Val = cross(p3, p1).z / normal.z;
		row2 = {-e1.y / normal.z, e1.x / normal.z, 0.0f};
		row2Val = -glm::cross(p2, p1).z / normal.z;
		row3 = {normal.x / normal.z, normal.y / normal.z, 1.0f};
		row3Val = -dot(p1, normal) / normal.z;
	}
	else
	{
		// This triangle is degenerate. Set the transformation matrix to
		// the 0 matrix, which in turn will yield 0 values in places that
		// intersection calculations will detect and treat as a miss.
		row1 = {};
		row1Val = 0.0f;
		row2 = {};
		row2Val = 0.0f;
		row3 = {};
		row3Val = 0.0f;
	}
}

Triangle::Triangle(Mesh* mesh, Vertex v1, Vertex v2, Vertex v3) : vertices({v1, v2, v3}),localNormal(normalize(cross(v2.pos - v1.pos, v3.pos - v2.pos)))
{
	for (auto& v : vertices)
	{
		if (v.normal == glm::vec3(0, 0, 0))
			v.normal = localNormal;
	}

	if (mesh != nullptr)
		attachTo(mesh);
}
void Triangle::attachTo(Mesh* obj)
{
	this->mesh = obj;

	updateGeometry();
}

bool Triangle::intersect(Ray& ray, bool intersectAll) const
{
	const float dz = dot(row3, ray.dir);
	if (dz == 0.0f)
		return false;

	const float oz = dot(row3, ray.pos) + row3Val;
	const float t = -oz / dz;
	if (t < 0 || ray.closestT < t || t >= ray.maxDist)
		return false;

	const auto hitPos = ray.pos + ray.dir * t;
	const float u = dot(row1, hitPos) + row1Val;
	if (u < 0.0f || u > 1.0f)
		return false;

	const float v = dot(row2, hitPos) + row2Val;
	if (v < 0.0f || u + v > 1.0f)
		return false;

	ray.closestT = t;
	ray.closestMat = mesh->material;
	ray.surfaceNormal = getNormalAt(u, v, dot(globalNormal, ray.dir) > 0);
	ray.interPoint = hitPos;
	ray.closestT = t;
	ray.color = getColorAt(u, v);
	return true;
}

Color Triangle::getColorAt(float u, float v) const
{
	auto d = vertices[0].uvPos + u * texVecU + v * texVecV;
	return mesh->material->texture->getColor(d.x, 1 - d.y);
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
		mesh->getRot() * vertices[0].pos + mesh->getPos(),
		mesh->getRot() * vertices[1].pos + mesh->getPos(),
		mesh->getRot() * vertices[2].pos + mesh->getPos()
	};

	globalNormal = mesh->getRot() * localNormal;

	globalVertexNormals = {
		mesh->getRot() * vertices[0].normal,
		mesh->getRot() * vertices[1].normal,
		mesh->getRot() * vertices[2].normal
	};

	recalculateCoefficients();
}
