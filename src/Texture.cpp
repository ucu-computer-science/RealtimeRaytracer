#include "Texture.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Texture::Texture() : width(2), height(2)
{
	pixelColors = std::vector<Color>(4);
	pixelColors[0] = Color::white();
	pixelColors[1] = Color::white();
	pixelColors[2] = Color::white();
	pixelColors[3] = Color::white();
}

Texture::Texture(const std::filesystem::path& path) : path(path)
{
	std::vector<uint8_t> image;
	bool success = loadImage(image, path);
	if (!success)
		std::cerr << "Error loading texture " << path << "\n";

	const size_t RGBA = 4;
	pixelColors.reserve(static_cast<size_t>(width) * static_cast<size_t>(height));
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			size_t index = RGBA * (y * width + x);
			pixelColors.emplace_back(image[index + 0], image[index + 1], image[index + 2], image[index + 3]);
		}
	}
}

bool Texture::loadImage(std::vector<uint8_t>& image, const std::filesystem::path& filename)
{
	int n;
	unsigned char* data = stbi_load(filename.string().c_str(), &width, &height, &n, 4);
	if (data != nullptr)
	{
		image = std::vector(data, data + width * height * 4);
	}
	stbi_image_free(data);
	return (data != nullptr);
}

Color Texture::getColor(float x, float y) const
{
	int x_ = (int)std::max(ceil(x * (float)width) - 1, 0.0f);
	int y_ = (int)std::max(ceil(y * (float)height) - 1, 0.0f);
	return getColor(x_, y_);
}

Color Texture::getColor(int x, int y) const
{
	return pixelColors[y * width + x];
}
