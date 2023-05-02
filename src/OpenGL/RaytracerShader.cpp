#include "RaytracerShader.h"

#include "glad.h"
#include "Scene.h"

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

	//glGenBuffers(1, &ssboTriangles);
	//glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboTriangles);
	//glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, ssboTriangles);

	glGenBuffers(1, &ssboBVHNodes);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboBVHNodes);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, ssboBVHNodes);


	glGenBuffers(1, &tboTriangles);
	glBindBuffer(GL_TEXTURE_BUFFER, tboTriangles);
	glBufferData(GL_TEXTURE_BUFFER, 15000000, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_TEXTURE_BUFFER, 0);

	glGenTextures(1, &tboTrianglesTex);
	glBindTexture(GL_TEXTURE_BUFFER, tboTrianglesTex);
	glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, tboTriangles);
	glBindTexture(GL_TEXTURE_BUFFER, 0);
	glBindImageTexture(3, tboTrianglesTex, 0, GL_TRUE, 0, GL_READ_WRITE, GL_RGBA32F);
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

void RaytracerShader::setTrianglesSSBO(const float* data, int triangleCount) const
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboTriangles);
	glBufferData(GL_SHADER_STORAGE_BUFFER, triangleCount * triangleAlign * sizeof(float), data, GL_STATIC_DRAW);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	setInt("triangleCount", triangleCount);
}

void RaytracerShader::setBVHNodesSSBO(const float* data, int bvhNodeCount) const
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboBVHNodes);
	glBufferData(GL_SHADER_STORAGE_BUFFER, bvhNodeCount * bvhNodeAlign * sizeof(float), data, GL_STATIC_DRAW);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	setInt("bvhNodeCount", bvhNodeCount);
}

void RaytracerShader::setTrianglesTBO(const float* data, int triangleCount) const
{
	glBindBuffer(GL_TEXTURE_BUFFER, tboTriangles);
	void* ptr = glMapBuffer(GL_TEXTURE_BUFFER, GL_WRITE_ONLY);
	auto c = (glm::vec4*)ptr; //color is a simple struct containing 4 GLfloats.
	for (int i = 0; i < triangleCount * triangleAlign / 4; ++i)
	{
		c[i].r = data[i * 4 + 0];
		c[i].g = data[i * 4 + 1];
		c[i].b = data[i * 4 + 2];
		c[i].a = data[i * 4 + 3];
	}
	glUnmapBuffer(GL_TEXTURE_BUFFER);
	glBindBuffer(GL_TEXTURE_BUFFER, 0);

	setInt("triangleCount", triangleCount);
}
