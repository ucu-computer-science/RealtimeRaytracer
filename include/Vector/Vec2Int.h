#ifndef Vec2Int_H
#define Vec2Int_H

#include <istream>

class Vec2Int
{

public:
	int val[2]{};

	Vec2Int(const int x, const int y) { val[0] = x; val[1] = y; }
	Vec2Int() : Vec2Int(0, 0) {}

	[[nodiscard]] int x() const { return val[0]; }
	[[nodiscard]] int y() const { return val[1]; }

	[[nodiscard]] const Vec2Int& operator+() const { return *this; }
	[[nodiscard]] Vec2Int operator-() const { return { -val[0], -val[1] }; }
	[[nodiscard]] int operator[](const int i) const { return val[i]; }
	[[nodiscard]] int& operator[](const int i) { return val[i]; }

	[[nodiscard]] Vec2Int operator+(const Vec2Int& v) const;
	[[nodiscard]] Vec2Int operator-(const Vec2Int& v) const;
	[[nodiscard]] int operator*(const Vec2Int& v) const;
	[[nodiscard]] Vec2Int operator/(int v) const;

	Vec2Int& operator+=(const Vec2Int& v);
	Vec2Int& operator-=(const Vec2Int& v);
	Vec2Int& operator*=(int f);
	Vec2Int& operator/=(int f);
};

[[nodiscard]] Vec2Int operator*(int x, const Vec2Int& v);
[[nodiscard]] Vec2Int operator*(const Vec2Int& v, int x);

inline std::istream& operator>>(std::istream& is, Vec2Int& v)
{
	is >> v.val[0] >> v.val[1];
	return is;
}
inline std::ostream& operator<<(std::ostream& os, const Vec2Int& v)
{
	os << "(" << v.val[0] << ", " << v.val[1] << ", " << ")";
	return os;
}

#endif // Vec2Int_H
