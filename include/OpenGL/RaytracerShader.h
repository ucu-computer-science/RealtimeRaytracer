#pragma once

#include "Shader.h"


class RaytracerShader : public Shader
{
public:
	unsigned int uboLights = 0;
	unsigned int uboMaterials = 0;
	unsigned int uboObjects = 0;
	unsigned int ssboTriangles = 0;
	unsigned int ssboBVHNodes = 0;

	unsigned int tboTriangles = 0;
	unsigned int tboTrianglesTex = 0;

	static constexpr int lightAlign = 20;
	static constexpr int materialAlign = 12;
	static constexpr int objectAlign = 12;
	static constexpr int triangleAlign = 40;
	static constexpr int bvhNodeAlign = 12;

	RaytracerShader(const char* vertexPath, const char* fragmentPath);

	void setLightsUBO(const float* data, int lightCount) const;
	void setMaterialsUBO(const float* data, int materialCount) const;
	void setObjectsUBO(const float* data, int objectCount) const;
	void setTrianglesSSBO(const float* data, int triangleCount) const;
	void setBVHNodesSSBO(const float* data, int bvhNodeCount) const;

	void setTrianglesTBO(const float* data, int triangleCount) const;
};
