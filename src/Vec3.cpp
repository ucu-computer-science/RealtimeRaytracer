// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Vec3.h"
//#include <xmmintrin.h>
#include <immintrin.h>
#include <iostream>
//#include <DirectXMath.h>
//#include <DirectXPackedVector.h>
//#include <DirectXColors.h>
//namespace  dx = DirectX;
#if defined(_M_IX86) || defined(__i386__)

#endif
#define USE_INTRINSICS
Vec3 Vec3::operator+(const Vec3& v) const{
//{       dx::XMFLOAT3 xmfloat3{}
#ifdef USE_INTRINSICS
    __m128 v1 = _mm_set_ps(x(), y(), z(), 0 );
    __m128 v2 = _mm_set_ps(v.x(), v.y(), v.z(), 0 );
    v1 = _mm_add_ps(v1, v2);
    return { v1.m128_f32};
#else
    return  { x() + v.x(), y() + v.y(), z() + v.z() };
#endif // USE_INTRINSICS
}
Vec3 Vec3::operator-(const Vec3& v) const
{
#ifdef USE_INTRINSICS
    __m128 v1 = _mm_set_ps(x(), y(), z(), 0 );
    __m128 v2 = _mm_set_ps(v.x(), v.y(), v.z(), 0 );
    v1 = _mm_sub_ps(v1, v2);
    return { v1.m128_f32};
#else
	return { x() - v.x() , y() - v.y() , z() - v.z()  };
#endif // USE_INTRINSICS
}
float Vec3::operator*(const Vec3& v) const
{
#ifdef USE_INTRINSICS
    __m128 v1 = _mm_set_ps(x(), y(), z(), 0 );
    __m128 v2 = _mm_set_ps(v.x(), v.y(), v.z(), 0 );
    v1 = _mm_mul_ps(v1, v2);
    v1 = _mm_hadd_ps(v1,v1);
    return v1.m128_f32[3];
#else
    return x() * v.x() + y() * v.y() + z() * v.z();
#endif // USE_INTRINSICS
//    exit(0);
//    _mm_extra
//    return v1.m128_f32[0];
}

Vec3 Vec3::operator/(float v) const
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

float Vec3::det(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3) {
    return v1.x()*v2.y()*v3.z() + v1.y()*v2.z()*v3.x() + v1.z()*v2.x()*v3.y() -
           v1.z()*v2.y()*v3.x() - v1.y()*v2.x()*v3.z() - v1.x()*v2.z()*v3.y();
}

bool Vec3::operator==(const Vec3 &v) const {
    return (x() == v.x()) && (y() == v.y()) && (z() == v.z());
}


Vec3 operator*(const float x, const Vec3& v) {
	return { x * v.x(), x * v.y(), x * v.z() };
}
Vec3 operator*(const Vec3& v, const float x) {
	return { x * v.x(), x * v.y(), x * v.z() };
}