#pragma once

#include <iostream>

class Vec3
{
public:
	float val[3];

	Vec3(float x, float y, float z)
	{
		val[0] = x;
		val[1] = y;
		val[2] = z;
	}
	Vec3(float x, float y) : Vec3(x, y, 0) {}
	Vec3() : Vec3(0, 0, 0) {}
	~Vec3() = default;
	//Vec3(glm::vec3 v) : Vec3(v.x, v.y, v.z) {}

	static Vec3 one() { return {1, 1, 1}; }
	static Vec3 forward() { return {0, 1, 0}; }
	static Vec3 backward() { return {0, -1, 0}; }
	static Vec3 up() { return {0, 0, 1}; }
	static Vec3 down() { return {0, 0, -1}; }
	static Vec3 left() { return {-1, 0, 0}; }
	static Vec3 right() { return {1, 0, 0}; }

	float x() const { return val[0]; }
	float y() const { return val[1]; }
	float z() const { return val[2]; }

	const Vec3& operator+() const { return *this; }
	Vec3 operator-() const { return {-val[0], -val[1], -val[2]}; }
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

inline std::ostream& operator<<(std::ostream& os, const Vec3& v)
{
	os << "(" << v.val[0] << ", " << v.val[1] << ", " << v.val[2] << ")";
	return os;
}
