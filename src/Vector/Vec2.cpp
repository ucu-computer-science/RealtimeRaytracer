#include "Vec2.h"
using Vector::Vec2;

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


Vec2 Vector::operator*(const float x, const Vec2& v) {
	return { x * v.x(), x * v.y() };
}
Vec2 Vector::operator*(const Vec2& v, const float x) {
	return { x * v.x(), x * v.y() };
}

std::istream& Vector::operator>>(std::istream& is, Vec2& v)
{
	is >> v.val[0] >> v.val[1];
	return is;
}
std::ostream& Vector::operator<<(std::ostream& os, const Vec2& v)
{
	os << "(" << v.val[0] << ", " << v.val[1] << ", " << ")";
	return os;
}
