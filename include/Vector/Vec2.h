#pragma once

#include <istream>

namespace Vector
{
	class Vec2
	{

	public:
		float val[2]{};

		Vec2(const float x, const float y) { val[0] = x; val[1] = y; }
		Vec2() : Vec2(0, 0) {}

		[[nodiscard]] float x() const { return val[0]; }
		[[nodiscard]] float y() const { return val[1]; }

		[[nodiscard]] const Vec2& operator+() const { return *this; }
		[[nodiscard]] Vec2 operator-() const { return { -val[0], -val[1] }; }
		[[nodiscard]] float operator[](const int i) const { return val[i]; }
		[[nodiscard]] float& operator[](const int i) { return val[i]; }

		[[nodiscard]] Vec2 operator+(const Vec2& v) const;
		[[nodiscard]] Vec2 operator-(const Vec2& v) const;
		[[nodiscard]] float operator*(const Vec2& v) const;
		[[nodiscard]] Vec2 operator/(float v) const;

		Vec2& operator+=(const Vec2& v);
		Vec2& operator-=(const Vec2& v);
		Vec2& operator*=(float f);
		Vec2& operator/=(float f);
	};

	[[nodiscard]] Vec2 operator*(float x, const Vec2& v);
	[[nodiscard]] Vec2 operator*(const Vec2& v, float x);

	inline std::istream& operator>>(std::istream& is, Vec2& v);
	inline std::ostream& operator<<(std::ostream& os, const Vec2& v);
}
