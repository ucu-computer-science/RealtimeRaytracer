#pragma once

#include <istream>

namespace Vector
{
	class Vec2
	{

	public:
		double val[2]{};

		Vec2(const double x, const double y) { val[0] = x; val[1] = y; }
		Vec2() : Vec2(0, 0) {}

		[[nodiscard]] double x() const { return val[0]; }
		[[nodiscard]] double y() const { return val[1]; }

		[[nodiscard]] const Vec2& operator+() const { return *this; }
		[[nodiscard]] Vec2 operator-() const { return { -val[0], -val[1] }; }
		[[nodiscard]] double operator[](const int i) const { return val[i]; }
		[[nodiscard]] double& operator[](const int i) { return val[i]; }

		[[nodiscard]] Vec2 operator+(const Vec2& v) const;
		[[nodiscard]] Vec2 operator-(const Vec2& v) const;
		[[nodiscard]] double operator*(const Vec2& v) const;
		[[nodiscard]] Vec2 operator/(double v) const;

		Vec2& operator+=(const Vec2& v);
		Vec2& operator-=(const Vec2& v);
		Vec2& operator*=(double f);
		Vec2& operator/=(double f);
	};

	[[nodiscard]] Vec2 operator*(double x, const Vec2& v);
	[[nodiscard]] Vec2 operator*(const Vec2& v, double x);

	inline std::istream& operator>>(std::istream& is, Vec2& v);
	inline std::ostream& operator<<(std::ostream& os, const Vec2& v);
}
