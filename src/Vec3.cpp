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

Vec3 Vec3::cross(const Vec3& v) const {
	return { y() * v.z() - z() * v.y(),
			z() * v.x() - x() * v.z(),
			x() * v.y() - y() * v.x() };
}
Vec3 operator*(float x, const Vec3& v) {
	return { x * v.x(), x * v.y(), x * v.z() };
}
Vec3 operator*(const Vec3& v, const float x) {
	return { x * v.x(), x * v.y(), x * v.z() };
}