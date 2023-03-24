#include "Vec2Int.h"

Vec2Int Vec2Int::operator+(const Vec2Int& v) const
{
	return { x() + v.x(), y() + v.y() };
}
Vec2Int Vec2Int::operator-(const Vec2Int& v) const
{
	return { x() - v.x(), y() - v.y() };
}
int Vec2Int::operator*(const Vec2Int& v) const
{
	return x() * v.x() + y() * v.y();
}
Vec2Int Vec2Int::operator/(const int v) const
{
	return { x() / v, y() / v };
}

Vec2Int& Vec2Int::operator+=(const Vec2Int& v)
{
	this->val[0] += v[0];
	this->val[1] += v[1];
	return *this;
}
Vec2Int& Vec2Int::operator-=(const Vec2Int& v)
{
	this->val[0] -= v[0];
	this->val[1] -= v[1];
	return *this;
}
Vec2Int& Vec2Int::operator*=(const int f)
{
	this->val[0] *= f;
	this->val[1] *= f;
	return *this;
}
Vec2Int& Vec2Int::operator/=(const int f)
{
	this->val[0] /= f;
	this->val[1] /= f;
	return *this;
}


Vec2Int operator*(const int x, const Vec2Int& v)
{
	return { x * v.x(), x * v.y() };
}
Vec2Int operator*(const Vec2Int& v, const int x)
{
	return { x * v.x(), x * v.y() };
}

std::istream& operator>>(std::istream& is, Vec2Int& v)
{
	is >> v.val[0] >> v.val[1];
	return is;
}
std::ostream& operator<<(std::ostream& os, const Vec2Int& v)
{
	os << "(" << v.val[0] << ", " << v.val[1] << ", " << ")";
	return os;
}
