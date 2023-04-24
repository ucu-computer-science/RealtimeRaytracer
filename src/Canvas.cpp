#include "Canvas.h"

#include "Color.h"
#include "glm/vec2.hpp"


void Canvas::drawUI(uint32_t* pixels, int width, int height)
{
	drawScope(pixels, width, height);
}

void Canvas::drawScope(uint32_t* pixels, int width, int height)
{
	auto centerX = width / 2;
	auto centerY = height / 2;

	glm::vec2 scopeSize{25, 25};
	int scopeWidth = 2;
	auto scopeColor = Color::white();
	for (int y = centerY - (int)scopeSize.y / 2; y < centerY + (int)scopeSize.y / 2; ++y)
	{
		for (int x = centerX - scopeWidth / 2; x < centerX + scopeWidth / 2; ++x)
		{
			pixels[(height - y - 1) * width + x] = scopeColor.toColor32();
		}
	}

	for (int x = centerX - (int)scopeSize.x / 2; x < centerX + (int)scopeSize.x / 2; ++x)
	{
		for (int y = centerY - scopeWidth / 2; y < centerY + scopeWidth / 2; ++y)
		{
			pixels[(height - y - 1) * width + x] = scopeColor.toColor32();
		}
	}
}
