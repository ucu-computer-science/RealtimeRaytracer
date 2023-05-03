#include "Canvas.h"

#include "Color.h"
#include "Material.h"
#include "SDLHandler.h"


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
			auto x_ = startX + x, y_ = startY + y;
			auto currColor = Color::fromColor32(pixelMatrix->getPixelSafe(x_, y_));
			auto spriteColor = sprite->getColor(x, y);
			auto finalColor = Color::lerp(currColor, spriteColor, spriteColor.a());
			pixelMatrix->setPixelSafe(x_, y_, finalColor.toColor32());
		}
	}
}