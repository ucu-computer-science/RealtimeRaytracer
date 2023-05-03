#pragma once

#include "glad.h"


class Texture;

class GLObject
{
protected:
	virtual ~GLObject() = default;

public:
	GLuint id = -1;
};


class VAO : public GLObject
{
public:
	VAO();

	void setVertices(const float* data, int size) const;
};


class GLBuffer : public GLObject
{
protected:
	GLBuffer();

	virtual void bindBase(int index) = 0;
	virtual void setData(const float* data, int count) = 0;
};


class SSBO : public GLBuffer
{
public:
	int align = -1;

	SSBO(int align, int baseIndex = -1);

	void bindBase(int index) override;
	void setData(const float* data, int count) override;
};


class GLTexture : public GLObject
{
public:
	GLTexture();
};


class GLCubeMap : public GLTexture
{
public:
	GLCubeMap();

	void setFaceTexture(const unsigned char* data, int faceInd, int width, int height) const;
};


class GLTexture2D : public GLTexture
{
public:
	GLTexture2D(const Texture* texture);
};