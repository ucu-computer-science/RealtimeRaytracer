#pragma once

#include <memory>
#include <vector>

#include "glm/vec2.hpp"

struct PixelMatrix;
class UIElement;
class Texture;

class Canvas
{
	std::vector<std::shared_ptr<UIElement>> elements{};

public:
	Canvas() = default;

	void drawUI(const PixelMatrix* pixelMatrix) const;
	void addElement(const std::shared_ptr<UIElement>& element);

	inline static std::shared_ptr<Canvas> mainCanvas = nullptr;
};

class UIElement
{
protected:
	glm::vec2 pos;

public:
	UIElement(glm::vec2 pos);

	virtual void draw(const PixelMatrix* pixelMatrix) = 0;
};

class Image : public UIElement
{
	Texture* sprite;

public:
	Image(const glm::vec2& pos, Texture* sprite);

	void draw(const PixelMatrix* pixelMatrix) override;
};
