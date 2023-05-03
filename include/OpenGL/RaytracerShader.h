#pragma once

#include "Shader.h"


class RaytracerShader : public Shader
{
public:
	unsigned int ssboLights = 0;
	unsigned int ssboMaterials = 0;
	unsigned int ssboObjects = 0;
	unsigned int ssboTriangles = 0;
	unsigned int ssboBVHNodes = 0;

	unsigned int tboTriangles = 0;
	unsigned int tboTrianglesTex = 0;

	unsigned int cubeMapNodeLinks;

	static constexpr int lightAlign = 20;
	static constexpr int materialAlign = 12;
	static constexpr int objectAlign = 12;
	static constexpr int triangleAlign = 40;
	static constexpr int bvhNodeAlign = 12;

	RaytracerShader(const char* vertexPath, const char* fragmentPath);

	void setLights(const float* data, int lightCount) const;
	void setMaterials(const float* data, int materialCount) const;
	void setObjects(const float* data, int objectCount) const;
	void setTriangles(const float* data, int triangleCount) const;
	void setBVHNodes(const float* data, int bvhNodeCount) const;
};
