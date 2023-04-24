#pragma once
#include <cstdint>

class Canvas
{
public:
	static void drawUI(uint32_t* pixels, int width, int height);
	static void drawScope(uint32_t* pixels, int width, int height);
};
