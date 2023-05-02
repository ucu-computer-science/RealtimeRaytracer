#pragma once

#include "Action.h"
#include "glad.h"
#include "Light.h"
#include "RaytracerShader.h"

class Raytracer
{
	inline static constexpr int triangleBufferSize = 1000;

	static void initializeScreenVertexBuffer();
	static void initializeScene();

public:
	inline static int width, height;

	inline static RaytracerShader* mainShader;
	inline static GLuint screenVertexArray;

	inline static Action onUpdate{};

	static void initialize(int width, int height);
	static void loop();
	static void quit();
};
