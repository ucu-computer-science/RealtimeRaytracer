#include "Vec2.h"

Vec2 Vec2::operator+(const Vec2& v) const
{
	return { x() + v.x(), y() + v.y() };
}
Vec2 Vec2::operator-(const Vec2& v) const
{
	return { x() - v.x(), y() - v.y() };
}
float Vec2::operator*(const Vec2& v) const
{
	return x() * v.x() + y() * v.y();
}
Vec2 Vec2::operator/(const float v) const
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
Vec2& Vec2::operator*=(const float f)
{
	this->val[0] *= f;
	this->val[1] *= f;
	return *this;
}
Vec2& Vec2::operator/=(const float f)
{
	this->val[0] /= f;
	this->val[1] /= f;
	return *this;
}


Vec2 operator*(const float x, const Vec2& v) {
	return { x * v.x(), x * v.y() };
}
Vec2 operator*(const Vec2& v, const float x) {
	return { x * v.x(), x * v.y() };
}