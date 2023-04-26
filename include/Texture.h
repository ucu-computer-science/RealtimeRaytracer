#pragma once

#include <filesystem>

#include "Color.h"


struct Texture
{
private:
	std::filesystem::path path;
	std::vector<Color> pixelColors;
	int width = 0, height = 0;

	bool load_image(std::vector<uint8_t>& image, const std::filesystem::path& filename);

public:
	Texture();
	Texture(const std::filesystem::path& path);

	Color getColor(int x, int y) const;
	Color getColor(float x, float y) const;

	int getWidth() const { return width; }
	int getHeight() const { return height; }
	std::filesystem::path getPath() { return path; }
};
