#include "GraphicalObject.h"
#include "Vec3.h"
#include "Triangle.h"

class Square : public GraphicalObject {
public:
	Square(Vec3 pos, Vec3 P1, Vec3 P2, Vec3 P3, Color color): GraphicalObject(pos)
	{
		triangles.emplace_back(new Triangle(P1, P2, P3, color));
		triangles.emplace_back(new Triangle(P2, P3, P2 + P3 - P1, color));
	}
};
