#pragma once
#include <ostream>
#include <glm/common.hpp>
#include <glm/vec4.hpp>

class Color : public glm::vec4
{
public:
	Color(float r, float g, float b, float a = 1) : glm::vec4(r, g, b, a) {}
	Color(int r, int g, int b, int a = 255) : glm::vec4((float)r / 255.f, (float)g / 255.f, (float)b / 255.f, (float)a / 255.f) {}
	Color() : Color{0, 0, 0, 0} {}

	static Color white() { return {1.f, 1.f, 1.f}; }
	static Color black() { return {0.f, 0.f, 0.f}; }
	static Color red() { return {1.f, 0.f, 0.f}; }
	static Color green() { return {0.f, 1.f, 0.f}; }
	static Color blue() { return {0.f, 0.f, 1.f}; }
	static Color yellow() { return {1.f, 1.f, 0.f}; }
	static Color cyan() { return {0.f, 1.f, 1.f}; }
	static Color magenta() { return {1.f, 0.f, 1.f}; }
	static Color gray() { return {0.2f, 0.2f, 0.2f}; }

	static Color darkGreen() { return {0.f, 0.5f, 0.f}; }
	static Color skyblue() { return {.529f, .808f, .922f}; }
	static Color gold() { return {1.f, .843f, 0.f}; }
	static Color pink() { return {255, 192, 203}; }
	static Color hotPink() { return {255, 105, 180}; }

	float r() const { return x; }
	float g() const { return y; }
	float b() const { return z; }
	float a() const { return w; }

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

	Color operator*(Color c) const { return {x * c.x, y * c.y, z * c.z}; }

	Color& operator+=(Color c)
	{
		x += c.x;
		y += c.y;
		z += c.z;
		return *this;
	}
	Color operator+(Color c) const { return {x + c.x, y + c.y, z + c.z}; }

	uint32_t toColor32() const
	{
		return ((int)(glm::clamp(a(), 0.0f, 1.0f) * 255) << 24) +
			((int)(glm::clamp(r(), 0.0f, 1.0f) * 255) << 16) +
			((int)(glm::clamp(g(), 0.0f, 1.0f) * 255) << 8) +
			((int)(glm::clamp(b(), 0.0f, 1.0f) * 255) << 0);
	}
	static Color fromColor32(uint32_t color32)
	{
		auto a = (float)(color32 >> 24 & 0xFF) / 255;
		auto r = (float)(color32 >> 16 & 0xFF) / 255;
		auto g = (float)(color32 >> 8 & 0xFF) / 255;
		auto b = (float)(color32 >> 0 & 0xFF) / 255;
		return {r, g, b, a};
	}

	static Color lerp(const Color& c1, const Color& c2, float value)
	{
		auto r = c1.r() + (c2.r() - c1.r()) * value;
		auto g = c1.g() + (c2.g() - c1.g()) * value;
		auto b = c1.b() + (c2.b() - c1.b()) * value;
		return {r, g, b};
	}
};


inline Color operator*(float v, Color c) { return {c.x * v, c.y * v, c.z * v}; }
inline Color operator*(Color c, float v) { return {c.x * v, c.y * v, c.z * v}; }

inline std::ostream& operator<<(std::ostream& os, const Color& c)
{
	os << "(" << c.r() << ", " << c.g() << ", " << c.b() << ")";
	return os;
}