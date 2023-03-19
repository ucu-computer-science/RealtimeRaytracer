
#include <iostream>
#include "Vec3.h"
#include "Triangle.h"	

int main()
{
	const auto v = Vec3(1, 1, 1);
	const Vec3 u = v * -1;
	const Vec3 w = v.cross(u);
	std::cout << v * w << std::endl;
	return 0;
}
