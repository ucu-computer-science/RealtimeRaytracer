
#include <iostream>
#include <Vec3.h>
#include <Triangle.h>	
#include <Color.h>

void test(){	
	Triangle t(Vec3(0, 0, 0), Vec3(1, 0, 0), Vec3(0, 1, 0));
	Color c(1, 0, 0);

	}


	
int main()
{
	auto v = Vec3(1, 2, 3);
	auto x = v * v;
	std::cout << x << std::endl;
	test();
	return 0;

	
}
