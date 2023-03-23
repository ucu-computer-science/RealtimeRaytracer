// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#ifndef RAY_H
#define RAY_H

//#include "GraphicalObject.h"
#include "Vec3.h"
#include <iostream>
#include <cfloat>

class Ray {

	Vec3 pos, dir;
    float closestDist;
    const class Triangle* closestTriangle;
	[[nodiscard]] float det(const Vec3& v1, const Vec3& v2, const Vec3& v3) const{ return Vec3::det(v1, v2, v3);}; // todo
public:
	Ray(Vec3 pos, Vec3 dir);
	~Ray() = default;
    [[nodiscard]] const Vec3& getDir() const{
        return dir;
    }
    [[nodiscard]] const Vec3& getPos() const{
        return pos;
    }
    void setClosestDist(const Triangle* triangle, float distance);



//	[[nodiscard]] bool intersects(const GraphicalObject& triangle) const {
//        triangle.intersects(pos, dir);
//
//	}

};


#endif // RAY_H
