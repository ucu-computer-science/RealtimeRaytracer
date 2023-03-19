
#include <iostream>
#include "Vector.h"
#include "Triangle.h"

int main()
{
	Vector v = Vector(1, 1, 1);
	Vector u =  v*-1;
    Vector w = v.xPr(u);
	std::cout << v*w << std::endl;
	return 0;
}
