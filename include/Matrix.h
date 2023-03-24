#pragma once
#include <vector>
#include "Vec3.h"
#include <cmath>

using Vector::Vec3;

# define PI           3.14159265358979323846f
constexpr double degToRad = 180 / PI;

template <typename T>
class Matrix :std::vector<std::vector<T>>
{
public:
	Matrix(int n, int m) : std::vector<std::vector<T>>(n, std::vector<T>(m)) {}

	using std::vector<std::vector<T>>::vector;
	using std::vector<std::vector<T>>::operator[];

	template<typename = double>
	Vec3 operator*(const Vec3& v) const
	{
		return Vec3
		{
			operator[](0)[0] * v[0] + operator[](0)[1] * v[1] + operator[](0)[2] * v[2],
			operator[](1)[0] * v[0] + operator[](1)[1] * v[1] + operator[](1)[2] * v[2],
			operator[](2)[0] * v[0] + operator[](2)[1] * v[1] + operator[](2)[2] * v[2],
		};
	}


	static Matrix<double> getRotationMatrix(Vec3 angles)
	{
		double x = angles[0] / degToRad, y = angles[1] / degToRad, z = angles[2] / degToRad;

		double cosX = cos(x), cosY = cos(y), cosZ = cos(z);
		double sinX = sin(x), sinY = sin(y), sinZ = sin(z);

		return Matrix
		{
			{cosY * cosZ, -cosX * sinZ + sinX * sinY * sinZ, sinX * sinZ + cosX * sinY * cosZ},
			{cosY * sinZ, cosX * cosZ + sinX * sinY * sinZ, -sinX * cosZ + cosX * sinY * sinZ},
			{-sinY, sinX * cosY, cosX * cosY},
		};
	}
};
