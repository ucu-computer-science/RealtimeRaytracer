#pragma once

#include <vector>

#include "GLObject.h"
#include "Shader.h"


class RaytracerShader : public Shader
{
public:
	SSBO* ssboLights;
	SSBO* ssboMaterials;
	SSBO* ssboObjects;
	SSBO* ssboTriangles;
	SSBO* ssboBVHNodes;

	VAO* vaoScreen;

	GLCubeMap* skybox;

	std::vector<GLTexture2D*> textures{};

	static constexpr int lightAlign = 20;
	static constexpr int materialAlign = 12;
	static constexpr int objectAlign = 12;
	static constexpr int triangleAlign = 44;
	static constexpr int bvhNodeAlign = 12;

	void setUpScreenTriangles() const;
	RaytracerShader(const char* vertexPath, const char* fragmentPath);

	void addTexture2D(const Texture* texture);
};
