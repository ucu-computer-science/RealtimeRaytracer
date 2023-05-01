#pragma once

#include "Shader.h"

class RaytracerShader : public Shader
{
public:
	unsigned int uboLights = 0;
	unsigned int uboObjects = 0;
	unsigned int uboTriangles = 0;

	static constexpr int lightAlign = 20;
	static constexpr int objectAlign = 24;
	static constexpr int triangleAlign = 52;


	RaytracerShader(const char* vertexPath, const char* fragmentPath);

	void setLightsUBO(const float* data, int lightCount) const;
	void setObjectsUBO(const float* data, int objectCount) const;
	void setTrianglesUBO(const float* data, int triangleCount) const;
};
