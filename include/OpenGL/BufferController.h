#pragma once

class BufferController
{
	static void initializeLightsBuffer();
	static void initializeMaterialsBuffer();
	static void initializeObjectsBuffer();
	static void initializeTrianglesBuffer();
	static void initializeBVHBuffer();

public:
	static void initializeUniformBuffers();
};