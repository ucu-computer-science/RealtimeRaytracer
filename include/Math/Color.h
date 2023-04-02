#pragma once

#include <ostream>

#include "glm/common.hpp"
#include "glm/vec3.hpp"

class Color : public glm::vec3
{
public:
	Color(const float r, const float g, const float b) : glm::vec3(r, g, b) {}
	Color() : Color{0, 0, 0} {}

	static Color white() { return {1, 1, 1}; }
	static Color black() { return {0, 0, 0}; }
	static Color red() { return {1, 0, 0}; }
	static Color green() { return {0, 1, 0}; }
	static Color blue() { return {0, 0, 1}; }
	static Color yellow() { return {1, 1, 0}; }
	static Color cyan() { return {0, 1, 1}; }
	static Color magenta() { return {1, 0, 1}; }
	static Color gray() { return {0.2f, 0.2f, 0.2f}; }

	static Color darkGreen() { return {0, 0.5f, 0}; }
	static Color skyBlue() { return {.529f, .808f, .922f}; }
        static Color gold() { return {1.f, .843f, 0}; }


	float r() const { return x; }
	float g() const { return y; }
	float b() const { return z; }

	Color& operator*=(float v)
	{
		x *= v;
		y *= v;
		z *= v;
		return *this;
	}
	Color& operator*=(Color c)
	{
		x *= c.x;
		y *= c.y;
		z *= c.z;
		return *this;
	}

	Color operator*(Color c) const
	{
		return {x * c.x, y * c.y, z * c.z};
	}

	Color& operator+=(Color c)
	{
		x += c.x;
		y += c.y;
		z += c.z;
		return *this;
	}
	Color operator+(Color c) const
	{
		return {x + c.x, y + c.y, z + c.z};
	}


	uint32_t toColor32() const
	{
		return ((int)(glm::clamp(r(), 0.0f, 1.0f) * 255) << 16) + ((int)(glm::clamp(g(), 0.0f, 1.0f) * 255) << 8) + ((int)(glm::clamp(b(), 0.0f, 1.0f) * 255) << 0);
	}
};

inline Color operator*(float v, Color c)
{
	return {c.x * v, c.y * v, c.z * v};
}

inline Color operator*(Color c, float v)
{
	return {c.x * v, c.y * v, c.z * v};
}

inline std::ostream& operator<<(std::ostream& os, const Color& c)
{
	os << "(" << c.r() << ", " << c.g() << ", " << c.b() << ")";
	return os;
}