#include "Vec3.h"
#include <cmath>

using Vector::Vec3;

Vec3 Vec3::operator+(const Vec3& v) const
{
	return { x() + v.x(), y() + v.y(), z() + v.z() };
}
Vec3 Vec3::operator-(const Vec3& v) const
{
	return { x() - v.x(), y() - v.y(), z() - v.z() };
}
double Vec3::operator*(const Vec3& v) const
{
	return x() * v.x() + y() * v.y() + z() * v.z();
}
Vec3 Vec3::operator/(const double v) const
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
Vec3& Vec3::operator*=(const double f)
{
	this->val[0] *= f;
	this->val[1] *= f;
	this->val[2] *= f;
	return *this;
}
Vec3& Vec3::operator/=(const double f)
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

double Vec3::length() const
{
	return std::sqrt(x() * x() + y() * y() + z() * z());
}

Vec3 Vec3::normalized() const
{
	const auto l = length();
	return { x() / l, y() / l, z() / l };
}

double Vec3::det(const Vec3& v1, const Vec3& v2, const Vec3& v3)
{
	const double x = v2[1] * v3[2] - v3[1] * v2[2];
	const double y = v2[0] * v3[2] - v3[0] * v2[2];
	const double z = v2[0] * v3[1] - v3[0] * v2[1];

	return v1[0] * x - v1[1] * y + v1[2] * z;
}

Vec3 Vector::operator*(const double x, const Vec3& v) {
	return { x * v.x(), x * v.y(), x * v.z() };
}
Vec3 Vector::operator*(const Vec3& v, const double x) {
	return { x * v.x(), x * v.y(), x * v.z() };
}

