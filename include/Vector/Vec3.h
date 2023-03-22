#pragma once

#include <iostream>

namespace Vector
{
	class Vec3
	{

	public:
		float val[3]{};

		Vec3(const float x, const float y, const float z) { val[0] = x; val[1] = y; val[2] = z; }
		Vec3(const float x, const float y) : Vec3(x, y, 0) {}
		Vec3() : Vec3(0, 0, 0) {}

		float x() const { return val[0]; }
		float y() const { return val[1]; }
		float z() const { return val[2]; }

		const Vec3& operator+() const { return *this; }
		Vec3 operator-() const { return { -val[0], -val[1], -val[2] }; }
		float operator[](const int i) const { return val[i]; }
		float& operator[](const int i) { return val[i]; }

		Vec3 operator+(const Vec3& v) const;
		Vec3 operator-(const Vec3& v) const;
		float operator*(const Vec3& v) const;
		Vec3 operator/(float v) const;

		Vec3& operator+=(const Vec3& v);
		Vec3& operator-=(const Vec3& v);
		Vec3& operator*=(float f);
		Vec3& operator/=(float f);

		Vec3 cross(const Vec3& v) const;
		float length() const;
		Vec3 normalized() const;

		static float det(const Vec3& v1, const Vec3& v2, const Vec3& v3);
	};

	Vec3 operator*(float x, const Vec3& v);
	Vec3 operator*(const Vec3& v, float x);

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
}
