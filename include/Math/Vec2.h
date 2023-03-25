#pragma once

#include <istream>


class Vec2
{
public:
	double val[2]{};

	Vec2(const double x, const double y)
	{
		val[0] = x;
		val[1] = y;
	}
	Vec2() : Vec2(0, 0) {}

	double x() const { return val[0]; }
	double y() const { return val[1]; }

	const Vec2& operator+() const { return *this; }
	Vec2 operator-() const { return { -val[0], -val[1] }; }
	double operator[](const int i) const { return val[i]; }
	double& operator[](const int i) { return val[i]; }

	Vec2 operator+(const Vec2& v) const;
	Vec2 operator-(const Vec2& v) const;
	double operator*(const Vec2& v) const;
	Vec2 operator/(double v) const;

	Vec2& operator+=(const Vec2& v);
	Vec2& operator-=(const Vec2& v);
	Vec2& operator*=(double f);
	Vec2& operator/=(double f);
};

[[nodiscard]] Vec2 operator*(double x, const Vec2& v);
[[nodiscard]] Vec2 operator*(const Vec2& v, double x);

inline std::istream& operator>>(std::istream& is, Vec2& v);
inline std::ostream& operator<<(std::ostream& os, const Vec2& v);
