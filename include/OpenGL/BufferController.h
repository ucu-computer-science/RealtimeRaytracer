#pragma once
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

class BufferController
{
	struct LightStruct {
		float lightType; // 0 - GlobalLight, 1 - PointLight, 2 - AreaLight(not implemented)
		glm::vec3 PAD;
		glm::vec4 pos;
		glm::vec4 color;
		glm::vec4 properties1; // intensity, [PointLight(distance) : GlobalLight(dir) : AreaLight(size)]
		glm::vec4 properties2; // [AreaLight(distance, pointSize)]
	};

	struct MaterialStruct
	{
		glm::vec4 color;
		glm::vec4 properties1; // lit, diffuse coeff, specular coeff, specular degree
		glm::vec4 properties2; // reflection
	};

	struct ObjectStruct {
		glm::vec4 data; // objType, materialIndex
		glm::vec4 pos; // pos
		glm::vec4 properties; // [Mesh(trianglesStart, triangleCount) : Sphere(radiusSquared) : Plane(normal)]
	};

	struct TriangleStruct
	{
		struct VertexStruct
		{
			glm::vec4 posU;
			glm::vec4 normalV;
		};

		VertexStruct vertices[3];
		glm::vec4 materialIndex; // materialIndex, normal
		glm::vec4 rows[3];
	};

	struct BVHNodeStruct {
		glm::vec4 min; // w = trianglesStart
		glm::vec4 max; // w = triangleCount
		glm::vec4 values; // hitNext, missNext, isLeaf
	};

	static void initializeLightsBuffer();
	static void initializeMaterialsBuffer();
	static void initializeObjectsBuffer();
	static void initializeTrianglesBuffer();
	static void initializeBVHBuffer();

public:
	static void initializeUniformBuffers();
};
