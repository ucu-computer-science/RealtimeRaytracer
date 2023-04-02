#include "Vec2.h"

Vec2 Vec2::operator+(const Vec2& v) const
{
	return { x() + v.x(), y() + v.y() };
}
Vec2 Vec2::operator-(const Vec2& v) const
{
	return { x() - v.x(), y() - v.y() };
}
double Vec2::operator*(const Vec2& v) const
{
	return x() * v.x() + y() * v.y();
}
Vec2 Vec2::operator/(const double v) const
{
	return { x() / v, y() / v };
}

Vec2& Vec2::operator+=(const Vec2& v)
{
	this->val[0] += v[0];
	this->val[1] += v[1];
	return *this;
}
Vec2& Vec2::operator-=(const Vec2& v)
{
	this->val[0] -= v[0];
	this->val[1] -= v[1];
	return *this;
}
Vec2& Vec2::operator*=(const double f)
{
	this->val[0] *= f;
	this->val[1] *= f;
	return *this;
}
Vec2& Vec2::operator/=(const double f)
{
	this->val[0] /= f;
	this->val[1] /= f;
	return *this;
}


Vec2 operator*(const double x, const Vec2& v)
{
	return { x * v.x(), x * v.y() };
}
Vec2 operator*(const Vec2& v, const double x)
{
	return { x * v.x(), x * v.y() };
}

std::ostream& operator<<(std::ostream& os, const Vec2& v)
{
	os << "(" << v.val[0] << ", " << v.val[1] << ", " << ")";
	return os;
}
