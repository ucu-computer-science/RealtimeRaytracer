#include "RaytracerShader.h"

#include "glad.h"

RaytracerShader::RaytracerShader(const char* vertexPath, const char* fragmentPath) : Shader(vertexPath, fragmentPath)
{
	glGenBuffers(1, &uboLights);
	glBindBuffer(GL_UNIFORM_BUFFER, uboLights);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, uboLights);

	glGenBuffers(1, &uboMaterials);
	glBindBuffer(GL_UNIFORM_BUFFER, uboMaterials);
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, uboMaterials);

	glGenBuffers(1, &uboObjects);
	glBindBuffer(GL_UNIFORM_BUFFER, uboObjects);
	glBindBufferBase(GL_UNIFORM_BUFFER, 2, uboObjects);

	glGenBuffers(1, &uboTriangles);
	glBindBuffer(GL_UNIFORM_BUFFER, uboTriangles);
	glBindBufferBase(GL_UNIFORM_BUFFER, 3, uboTriangles);

	glGenBuffers(1, &uboBVHNodes);
	glBindBuffer(GL_UNIFORM_BUFFER, uboBVHNodes);
	glBindBufferBase(GL_UNIFORM_BUFFER, 4, uboBVHNodes);

}
void RaytracerShader::setLightsUBO(const float* data, int lightCount) const
{
	glBindBuffer(GL_UNIFORM_BUFFER, uboLights);
	glBufferData(GL_UNIFORM_BUFFER, lightCount * lightAlign * sizeof(float), data, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	setInt("lightCount", lightCount);
}
void RaytracerShader::setMaterialsUBO(const float* data, int materialCount) const
{
	glBindBuffer(GL_UNIFORM_BUFFER, uboMaterials);
	glBufferData(GL_UNIFORM_BUFFER, materialCount * materialAlign * sizeof(float), data, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	setInt("materialCount", materialCount);
}

void RaytracerShader::setObjectsUBO(const float* data, int objectCount) const
{
	glBindBuffer(GL_UNIFORM_BUFFER, uboObjects);
	glBufferData(GL_UNIFORM_BUFFER, objectCount * objectAlign * sizeof(float), data, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	setInt("objectCount", objectCount);
}

void RaytracerShader::setTrianglesUBO(const float* data, int triangleCount) const
{
	glBindBuffer(GL_UNIFORM_BUFFER, uboTriangles);
	glBufferData(GL_UNIFORM_BUFFER, triangleCount * triangleAlign * sizeof(float), data, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	setInt("triangleCount", triangleCount);
}
void RaytracerShader::setBVHNodesUBO(const float* data, int bvhNodeCount) const
{
	glBindBuffer(GL_UNIFORM_BUFFER, uboBVHNodes);
	glBufferData(GL_UNIFORM_BUFFER, bvhNodeCount * bvhNodeAlign* sizeof(float), data, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	setInt("bvhNodeCount", bvhNodeCount);
}
