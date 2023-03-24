#pragma once

#include <functional>
#include <SDL2/SDL.h>

#include "Vec2Int.h"

class ScreenMatrix;

int show(const Vector::Vec2Int& resolution);

inline void setPixel(SDL_Surface* surface, int x, int y, Uint8 r, Uint8 g, Uint8 b)
{

}
