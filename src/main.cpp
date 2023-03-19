
#include <iostream>
#include <Vec3.h>
#include <Triangle.h>	
#include <Color.h>

int main()
{
	auto v = Vec3(1, 2, 3);
	auto x = v * v;
	std::cout << x << std::endl;
	return 0;
}
