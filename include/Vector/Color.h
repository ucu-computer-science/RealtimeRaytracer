#pragma once
#include <SDL_pixels.h>

#include "Vec3.h"

namespace Vector
{
	class Color : public Vec3
	{
	public:
		Color() { val[0] = 0; val[1] = 0; val[2] = 0; }
		Color(const double r, const double g, const double b) { val[0] = r; val[1] = g; val[2] = b; }

		static Color white() { return { 1, 1, 1 }; }
		static Color black() { return { 0, 0, 0 }; }
		static Color red() { return { 1, 0, 0 }; }
		static Color green() { return { 0, 1, 0 }; }
		static Color blue() { return { 0, 0, 1 }; }
		static Color yellow() { return { 1, 1, 0 }; }
		static Color cyan() { return { 0, 1, 1 }; }
		static Color magenta() { return { 1, 0, 1 }; }

		double r() const { return val[0]; }
		double g() const { return val[1]; }
		double b() const { return val[2]; }

		uint32_t toColor32() const
		{
			return ((int)(r() * 255) << 16) + ((int)(g() * 255) << 8) + ((int)(b() * 255) << 0);
		}
	};
}
