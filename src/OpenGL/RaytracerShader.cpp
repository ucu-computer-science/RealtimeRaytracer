#include "RaytracerShader.h"

#include "glad.h"
#include "Scene.h"
#include "stb_image.h"

RaytracerShader::RaytracerShader(const char* vertexPath, const char* fragmentPath) : Shader(vertexPath, fragmentPath)
{
	glGenBuffers(1, &ssboLights);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboLights);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssboLights);

	glGenBuffers(1, &ssboMaterials);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboMaterials);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ssboMaterials);

	glGenBuffers(1, &ssboObjects);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboObjects);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, ssboObjects);

	glGenBuffers(1, &ssboTriangles);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboTriangles);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, ssboTriangles);

	glGenBuffers(1, &ssboBVHNodes);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboBVHNodes);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, ssboBVHNodes);



	glGenTextures(1, &cubeMapNodeLinks);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapNodeLinks);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	std::string cubemapPaths[6] =
	{
		"textures/skybox/right.jpg",
		"textures/skybox/left.jpg",
		"textures/skybox/top.jpg",
		"textures/skybox/bottom.jpg",
		"textures/skybox/front.jpg",
		"textures/skybox/back.jpg"
	};

	int width, height, nrChannels;
	for (unsigned int i = 0; i < 6; i++)
	{
		unsigned char* data = stbi_load(cubemapPaths[i].c_str(), &width, &height, &nrChannels, 0);
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
		);
		stbi_image_free(data);
	}
	setInt("cubemap", 0);
}

void RaytracerShader::setLights(const float* data, int lightCount) const
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboLights);
	glBufferData(GL_SHADER_STORAGE_BUFFER, lightCount * lightAlign * sizeof(float), data, GL_STATIC_DRAW);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	setInt("lightCount", lightCount);
}
void RaytracerShader::setMaterials(const float* data, int materialCount) const
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboMaterials);
	glBufferData(GL_SHADER_STORAGE_BUFFER, materialCount * materialAlign * sizeof(float), data, GL_STATIC_DRAW);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	setInt("materialCount", materialCount);
}

void RaytracerShader::setObjects(const float* data, int objectCount) const
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboObjects);
	glBufferData(GL_SHADER_STORAGE_BUFFER, objectCount * objectAlign * sizeof(float), data, GL_STATIC_DRAW);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	setInt("objectCount", objectCount);
}

void RaytracerShader::setTriangles(const float* data, int triangleCount) const
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboTriangles);
	glBufferData(GL_SHADER_STORAGE_BUFFER, triangleCount * triangleAlign * sizeof(float), data, GL_STATIC_DRAW);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	setInt("triangleCount", triangleCount);
}

void RaytracerShader::setBVHNodes(const float* data, int bvhNodeCount) const
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboBVHNodes);
	glBufferData(GL_SHADER_STORAGE_BUFFER, bvhNodeCount * bvhNodeAlign * sizeof(float), data, GL_STATIC_DRAW);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	setInt("bvhNodeCount", bvhNodeCount);
}
