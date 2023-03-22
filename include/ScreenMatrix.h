#pragma once

#include <vector>
#include "Color.h"

using Vector::Color;

class ScreenMatrix : std::vector<std::vector<Color>> {
public:
	ScreenMatrix(const int width, const int height) : std::vector<std::vector<Color>>(width, std::vector<Color>(height)) {}

	using std::vector<std::vector<Color>>::operator[];
};
