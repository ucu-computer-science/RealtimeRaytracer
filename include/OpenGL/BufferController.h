#pragma once
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

class BufferController
{
	struct LightStruct
	{
		float lightType;
		glm::vec3 PAD;
		glm::vec4 pos;
		glm::vec4 color;
		glm::vec4 properties1;
		glm::vec4 properties2;
	};

	struct MaterialStruct
	{
		glm::vec4 color;
		glm::vec4 properties1;
		glm::vec4 properties2;
	};

	struct ObjectStruct
	{
		glm::vec4 data;
		glm::vec4 pos;
		glm::vec4 properties;
	};

	struct TriangleStruct
	{
		struct VertexStruct
		{
			glm::vec4 posU;
			glm::vec4 normalV;
		};

		VertexStruct vertices[3];
		glm::vec4 materialIndex;
		glm::vec4 rows[3];
		glm::vec4 texVec;
	};

	struct BVHNodeStruct
	{
		glm::vec4 min;
		glm::vec4 max;
		glm::vec4 values;
	};

	static void initializeTexturesBuffer();
	static void initializeMaterialsBuffer();
	static void initializeLightsBuffer();
	static void initializeObjectsBuffer();
	static void initializeTrianglesBuffer();
	static void initializeBVHBuffer();

public:
	static void initializeUniformBuffers();
};
