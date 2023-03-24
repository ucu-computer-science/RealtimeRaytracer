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
//#define USE_INTRINSICS_AVX
Vec3 Vec3::operator+(const Vec3& v) const{
//{       dx::XMFLOAT3 xmfloat3{}
#ifdef USE_INTRINSICS_SSE
    __m128 v1 = _mm_set_ps(x(), y(), z(), 0 );
    __m128 v2 = _mm_set_ps(v.x(), v.y(), v.z(), 0 );
    v1 = _mm_add_ps(v1, v2);
    return {v1};
#else
 #ifdef USE_INTRINSICS_AVX
    __m256 v1 = _mm256_set_ps(x(), y(), z(), 0, v.x(), v.y(), v.z() ,0);
//    __m256 v2 = _mm256_set_ps(v.x(), v.y(), v.z(), 0, 0, 0 ,0 ,0 );
//    v1 = _mm256_add_ps(v1, v2);
//    return {v1};
    return {_mm_add_ps(_mm256_extractf128_ps(v1, 0), _mm256_extractf128_ps(v1, 1))};

 #else
    return  { x() + v.x(), y() + v.y(), z() + v.z() };
#endif // USE_INTRINSICS_AVX

#endif // USE_INTRINSICS_SSE
}
Vec3 Vec3::operator-(const Vec3& v) const
{
#ifdef USE_INTRINSICS_SSE
    __m128 v1 = _mm_set_ps(x(), y(), z(), 0 );
    __m128 v2 = _mm_set_ps(v.x(), v.y(), v.z(), 0 );
    v1 = _mm_sub_ps(v1, v2);
    return { v1};
#else
#ifdef USE_INTRINSICS_AVX

//    __m256 v1 = _mm256_set_ps(x(), y(), z(), 0, 0, 0 ,0 ,0);
//    __m256 v2 = _mm256_set_ps(v.x(), v.y(), v.z(), 0, 0, 0 ,0 ,0 );
//    v1 = _mm256_sub_ps(v1, v2);
//    return { v1};
//#else
    __m256 v1 = _mm256_set_ps(x(), y(), z(), 0, v.x(), v.y(), v.z() ,0);
//    __m128 v2 = _mm_sub_ps(_mm256_extractf128_ps(v1, 0), _mm256_extractf128_ps(v1, 1));
        return {_mm_sub_ps(_mm256_extractf128_ps(v1, 0), _mm256_extractf128_ps(v1, 1))};

#endif // USE_INTRINSICS_AVX
    return { x() - v.x() , y() - v.y() , z() - v.z()  };

#endif // USE_INTRINSICS_SSE
}
float Vec3::operator*(const Vec3& v) const
{
#ifdef USE_INTRINSICS_SSE
    __m128 v1 = _mm_set_ps(x(), y(), z(), 0 );
    __m128 v2 = _mm_set_ps(v.x(), v.y(), v.z(), 0 );
    v1 = _mm_mul_ps(v1, v2);
    v1 = _mm_hadd_ps(v1,v1);
    return v1.m128_f32[3];
#else

    #ifdef USE_INTRINSICS_AVX
//    __m256 v1 = _mm256_set_ps(x(), y(), z(), 0, 0, 0 ,0 ,0);
//    __m256 v2 = _mm256_set_ps(v.x(), v.y(), v.z(), 0, 0, 0 ,0 ,0 );
//    v1 = _mm256_mul_ps(v1, v2);
//    v1 = _mm256_hadd_ps(v1, v1);
    __m256 v1 = _mm256_set_ps(x(), y(), z(), 0, v.x(), v.y(), v.z() ,0);
    __m128 v2 = _mm_mul_ps(_mm256_extractf128_ps(v1, 0), _mm256_extractf128_ps(v1, 1));
    return _mm_hadd_ps(v2, v2).m128_f32[3];
//std::cout<<v1.m256_f32[7];
//    exit(0);
//    return v1.m256_f32[7];
#else
    return x() * v.x() + y() * v.y() + z() * v.z();
#endif //USE_INTRINSICS_AVX
#endif // USE_INTRINSICS_SSE
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
	val[0] += v.val[0];
	val[1] += v.val[1];
	val[2] += v.val[2];
	return *this;
}
Vec3& Vec3::operator-=(const Vec3& v)
{
	val[0] -= v.val[0];
	val[1] -= v.val[1];
	val[2] -= v.val[2];
	return *this;
}
Vec3& Vec3::operator*=(const float f)
{
	val[0] *= f;
	val[1] *= f;
	val[2] *= f;
	return *this;
}
Vec3& Vec3::operator/=(const float f)
{
	val[0] /= f;
	val[1] /= f;
	val[2] /= f;
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