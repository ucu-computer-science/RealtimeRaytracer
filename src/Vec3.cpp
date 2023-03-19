#include "Vec3.h"

Vec3 Vec3::operator+(const Vec3& v) const
{
	return { x() + v.x(), y() + v.y(), z() + v.z() };
}
Vec3 Vec3::operator-(const Vec3& v) const
{
	return { x() - v.x(), y() - v.y(), z() - v.z() };
}
float Vec3::operator*(const Vec3& v) const
{
	return x() * v.x() + y() * v.y() + z() * v.z();
}

Vec3 Vec3::operator/(const float v) const
{
	return { x() / v, y() / v, z() / v };
}

Vec3& Vec3::operator+=(const Vec3& v)
{
	this->val[0] += v[0];
	this->val[1] += v[1];
	this->val[2] += v[2];
	return *this;
}
Vec3& Vec3::operator-=(const Vec3& v)
{
	this->val[0] -= v[0];
	this->val[1] -= v[1];
	this->val[2] -= v[2];
	return *this;
}
Vec3& Vec3::operator*=(const float f)
{
	this->val[0] *= f;
	this->val[1] *= f;
	this->val[2] *= f;
	return *this;
}
Vec3& Vec3::operator/=(const float f)
{
	this->val[0] /= f;
	this->val[1] /= f;
	this->val[2] /= f;
	return *this;
}


Vec3 Vec3::cross(const Vec3& v) const {
	return { y() * v.z() - z() * v.y(),
			z() * v.x() - x() * v.z(),
			x() * v.y() - y() * v.x() };
}


Vec3 operator*(const float x, const Vec3& v) {
	return { x * v.x(), x * v.y(), x * v.z() };
}
Vec3 operator*(const Vec3& v, const float x) {
	return { x * v.x(), x * v.y(), x * v.z() };
}