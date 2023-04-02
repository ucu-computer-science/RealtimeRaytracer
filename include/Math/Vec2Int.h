#pragma once

#include <istream>

class Vec2Int
{
public:
	int val[2]{};

	Vec2Int(const int x, const int y)
	{
		val[0] = x;
		val[1] = y;
	}
	Vec2Int() : Vec2Int(0, 0) {}

	int x() const { return val[0]; }
	int y() const { return val[1]; }

	const Vec2Int& operator+() const { return *this; }
	Vec2Int operator-() const { return { -val[0], -val[1] }; }
	int operator[](const int i) const { return val[i]; }
	int& operator[](const int i) { return val[i]; }

	Vec2Int operator+(const Vec2Int& v) const;
	Vec2Int operator-(const Vec2Int& v) const;
	int operator*(const Vec2Int& v) const;
	Vec2Int operator/(int v) const;

	Vec2Int& operator+=(const Vec2Int& v);
	Vec2Int& operator-=(const Vec2Int& v);
	Vec2Int& operator*=(int f);
	Vec2Int& operator/=(int f);
};

[[nodiscard]] Vec2Int operator*(int x, const Vec2Int& v);
[[nodiscard]] Vec2Int operator*(const Vec2Int& v, int x);

inline std::ostream& operator<<(std::ostream& os, const Vec2Int& v);
