#ifndef PIXEL_DISPLAYER_H
#define PIXEL_DISPLAYER_H

#include <vector>
#include "Color.h"

class PixelDisplayer
{
	static void displayPixels(const std::vector<std::vector<Color>>& pixels);
};
#endif // PIXEL_DISPLAYER_H
