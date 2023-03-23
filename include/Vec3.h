// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#ifndef VEC3_H
#define VEC3_H

#include <istream>
#include <cmath>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
namespace  dx = DirectX;
class Vec3
{

public:
	float val[3]{};
    
//    dx::XMFLOAT3 xmfloat3;: xmfloat3{x,y,z}
	Vec3(const float x, const float y, const float z) { val[0] = x; val[1] = y; val[2] = z; }
	Vec3(const float x, const float y) : Vec3(x, y, 0) {}
	Vec3() : Vec3(0, 0, 0) {}
    Vec3(float * vec) : Vec3(vec[3], vec[2], vec[1]) {}

	[[nodiscard]] float x() const { return val[0]; }
	[[nodiscard]] float y() const { return val[1]; }
	[[nodiscard]] float z() const { return val[2]; }

	[[nodiscard]] const Vec3& operator+() const { return *this; }
	[[nodiscard]] Vec3 operator-() const { return { -val[0], -val[1], -val[2] }; }
	[[nodiscard]] float operator[](const int i) const { return val[i]; }
	[[nodiscard]] float& operator[](const int i) { return val[i]; }

	[[nodiscard]] Vec3 operator+(const Vec3& v) const;
	[[nodiscard]] Vec3 operator-(const Vec3& v) const;
	[[nodiscard]] float operator*(const Vec3& v) const;
	[[nodiscard]] Vec3 operator/(float v) const;

	Vec3& operator+=(const Vec3& v);
	Vec3& operator-=(const Vec3& v);
	Vec3& operator*=(float f);
	Vec3& operator/=(float f);

	[[nodiscard]] Vec3 cross(const Vec3& v) const;

    [[nodiscard]] static float det(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3); //todo

    [[nodiscard]]  bool operator== (const Vec3& v) const;
    [[nodiscard]] float norm() const{
        /**returns squared length*/
        return (this->operator*(*this));
    }
    [[nodiscard]] bool isNan() const{
        return std::isnan(x()) || std::isnan(y()) || std::isnan(z());
    }
};

[[nodiscard]] Vec3 operator*(float x, const Vec3& v);
[[nodiscard]] Vec3 operator*(const Vec3& v, float x);

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

#endif // VEC3_H
