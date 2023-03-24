#pragma once

#include <iostream>

class Vec3
{
public:
	double val[3]{};

	Vec3(const double x, const double y, const double z)
	{
		val[0] = x;
		val[1] = y;
		val[2] = z;
	}
	Vec3(const double x, const double y) : Vec3(x, y, 0) {}
	Vec3() : Vec3(0, 0, 0) {}

	double x() const
	{
		return val[0];
	}
	double y() const
	{
		return val[1];
	}
	double z() const
	{
		return val[2];
	}

	const Vec3& operator+() const
	{
		return *this;
	}
	Vec3 operator-() const
	{
		return { -val[0], -val[1], -val[2] };
	}
	double operator[](const int i) const
	{
		return val[i];
	}
	double& operator[](const int i)
	{
		return val[i];
	}

	Vec3 operator+(const Vec3& v) const;
	Vec3 operator-(const Vec3& v) const;
	double operator*(const Vec3& v) const;
	Vec3 operator/(double v) const;

	Vec3& operator+=(const Vec3& v);
	Vec3& operator-=(const Vec3& v);
	Vec3& operator*=(double f);
	Vec3& operator/=(double f);

	Vec3 cross(const Vec3& v) const;
	double length() const;
	Vec3 normalized() const;

	static double det(const Vec3& v1, const Vec3& v2, const Vec3& v3);
};

Vec3 operator*(double x, const Vec3& v);
Vec3 operator*(const Vec3& v, double x);

inline std::istream& operator>>(std::istream& is, Vec3& v)
{
	is >> v.val[0] >> v.val[1] >> v.val[2];
	return is;
}
inline std::ostream& operator<<(std::ostream& os, const Vec3& v)
{
	os << "(" << v.val[0] << ", " << v.val[1] << ", " << v.val[2] << ")";
	return os;
}
