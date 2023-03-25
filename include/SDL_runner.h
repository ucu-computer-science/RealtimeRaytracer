#pragma once

#include <functional>

#ifdef __MINGW64__
#include "SDL.h"
#else
#include <SDL2/SDL.h>
#endif // __MINGW64__
#include "Vec2Int.h"

class ScreenMatrix;

int show(const Vec2Int& resolution);
