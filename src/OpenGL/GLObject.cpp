#include "GLObject.h"

#include <iostream>

#include "Material.h"


GLBuffer::GLBuffer()
{
	glGenBuffers(1, &id);
}


VAO::VAO()
{
	glGenVertexArrays(1, &id);
}

void VAO::setVertices(const float* data, int size) const
{
	glBindVertexArray(id);

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
}


SSBO::SSBO(int align, int baseIndex) : align(align)
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, id);
	if (baseIndex != -1)
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, baseIndex, id);
}

void SSBO::bindBase(int index)
{
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, id);
}

void SSBO::setData(const float* data, int count)
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, id);
	glBufferData(GL_SHADER_STORAGE_BUFFER, count * align * sizeof(float), data, GL_STATIC_DRAW);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}


GLTexture::GLTexture()
{
	glGenTextures(1, &id);
}


GLCubeMap::GLCubeMap()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void GLCubeMap::setFaceTexture(const unsigned char* data, int faceInd, int width, int height) const
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);
	glTexImage2D(
		GL_TEXTURE_CUBE_MAP_POSITIVE_X + faceInd,
		0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
	);
}


GLTexture2D::GLTexture2D(const Texture* texture)
{
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//float borderColor[] = {1.0f, 1.0f, 0.0f, 1.0f};
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	auto* data = new unsigned char[texture->width * texture->height * 4];
	for (int i = 0; i < texture->width * texture->height; ++i)
	{
		data[i * 4 + 0] = texture->pixelColors[i].x * 255.0f;
		data[i * 4 + 1] = texture->pixelColors[i].y * 255.0f;
		data[i * 4 + 2] = texture->pixelColors[i].z * 255.0f;
		data[i * 4 + 3] = texture->pixelColors[i].w * 255.0f;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, 0);
}
