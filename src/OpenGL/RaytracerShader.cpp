#include "RaytracerShader.h"

#include "glad.h"

RaytracerShader::RaytracerShader(const char* vertexPath, const char* fragmentPath) : Shader(vertexPath, fragmentPath)
{
	glGenBuffers(1, &uboLights);
	glBindBuffer(GL_UNIFORM_BUFFER, uboLights);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, uboLights);

	glGenBuffers(1, &uboObjects);
	glBindBuffer(GL_UNIFORM_BUFFER, uboObjects);
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, uboObjects);

	glGenBuffers(1, &uboTriangles);
	glBindBuffer(GL_UNIFORM_BUFFER, uboTriangles);
	glBindBufferBase(GL_UNIFORM_BUFFER, 2, uboTriangles);

}
void RaytracerShader::setLightsUBO(const float* data, int lightCount) const
{
	glBindBuffer(GL_UNIFORM_BUFFER, uboLights);
	glBufferData(GL_UNIFORM_BUFFER, lightCount * lightAlign * sizeof(float), data, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	setInt("lightCount", lightCount);
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