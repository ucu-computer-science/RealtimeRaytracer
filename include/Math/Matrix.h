#pragma once
#include <vector>
#include <cmath>

#include "MathExtensions.h"

template <typename T>
class Matrix : std::vector<std::vector<T>>
{
public:
	Matrix(int n, int m) : std::vector<std::vector<T>>(n, std::vector<T>(m)) {}

	using std::vector<std::vector<T>>::vector;
	using std::vector<std::vector<T>>::operator[];

	template <typename = float>
	glm::vec3 operator*(const glm::vec3& v) const
	{
		return glm::vec3
		{
			operator[](0)[0] * v[0] + operator[](0)[1] * v[1] + operator[](0)[2] * v[2],
			operator[](1)[0] * v[0] + operator[](1)[1] * v[1] + operator[](1)[2] * v[2],
			operator[](2)[0] * v[0] + operator[](2)[1] * v[1] + operator[](2)[2] * v[2],
		};
	}


	static Matrix<float> getRotationMatrix(glm::vec3 angles)
	{
		float x = angles[0] / DEG_TO_RAD, y = angles[1] / DEG_TO_RAD, z = angles[2] / DEG_TO_RAD;

		float cosX = cos(x), cosY = cos(y), cosZ = cos(z);
		float sinX = sin(x), sinY = sin(y), sinZ = sin(z);

		return Matrix
		{
			{ cosY * cosZ, -cosX * sinZ + sinX * sinY * sinZ, sinX * sinZ + cosX * sinY * cosZ },
			{ cosY * sinZ, cosX * cosZ + sinX * sinY * sinZ, -sinX * cosZ + cosX * sinY * sinZ },
			{ -sinY, sinX * cosY, cosX * cosY },
		};
	}
};
