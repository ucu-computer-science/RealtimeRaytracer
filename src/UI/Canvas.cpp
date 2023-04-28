#include "Canvas.h"

#include <iostream>

#include "Color.h"
#include "SDLDisplayer.h"
#include "Texture.h"


void Canvas::drawUI(const PixelMatrix* pixelMatrix) const
{
	for (const auto& element : elements)
	{
		element->draw(pixelMatrix);
	}
}

void Canvas::addElement(const std::shared_ptr<UIElement>& element)
{
	elements.push_back(element);
}

UIElement::UIElement(glm::vec2 pos) : pos(pos) { }

Image::Image(const glm::vec2& pos, Texture* sprite) : UIElement(pos), sprite(sprite) { }

void Image::draw(const PixelMatrix* pixelMatrix)
{
	auto width = sprite->getWidth(), height = sprite->getHeight();

	auto startY = (int)pos.y - height / 2;
	auto startX = (int)pos.x - width / 2;
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			auto currColor = pixelMatrix->getPixelSafe(x, y);
			auto spriteColor = sprite->getColor(x, y);
			pixelMatrix->setPixelSafe(startX + x, startY + y, (currColor * spriteColor).toColor32());
		}
	}
}