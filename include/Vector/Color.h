#ifndef COLOR_H
#define COLOR_H

#include "Vec3.h"

class Color :public Vec3
{
public:
	Color(const float r, const float g, const float b) { val[0] = r; val[1] = g; val[2] = b; }

	[[nodiscard]] float r() const { return val[0]; }
	[[nodiscard]] float g() const { return val[1]; }
	[[nodiscard]] float b() const { return val[2]; }
};
#endif // COLOR_H
