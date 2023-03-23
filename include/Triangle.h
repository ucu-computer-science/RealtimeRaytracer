// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cmath>
#include "Vec3.h"
#include "GraphicalObject.h"
#include "SimpleGraphicalObject.h"

class Triangle: public SimpleGraphicalObject {

	struct PlaneEq {
		Vec3 norm;
		float d;
		PlaneEq(Vec3 norm, const float d) : norm{ norm }, d{ d } {}
		~PlaneEq() = default;
	};


	Vec3 p1, p2, p3;
	PlaneEq planeEq;
    [[nodiscard]] float det(const Vec3& v1, const Vec3& v2, const Vec3& v3) const{return Vec3::det(v1, v2, v3);}; // todo
	[[nodiscard]] PlaneEq calcPlaneEq() const {
		return  { (p2 - p1).cross(p3 - p1), det(p1, p2 - p1, p3 - p1) };
	}
public:
	Triangle(Vec3 p1, Vec3 p2, Vec3 p3) : p1{ p1 }, p2{ p2 }, p3{ p3 }, planeEq{ calcPlaneEq() }{}
    Triangle() : p1{ }, p2{ }, p3{ }, planeEq{ calcPlaneEq() }{}

    ~Triangle() = default;
	[[nodiscard]] const PlaneEq& getPlaneEq() const { return planeEq; }

	[[nodiscard]] const Vec3& P1() const { return p1; }
	[[nodiscard]] const Vec3& P2() const { return p2; }
	[[nodiscard]] const Vec3& P3() const { return p3; }

    [[nodiscard]] float getT(const Vec3& pos, const Vec3& dir) const {
        auto norm = planeEq.norm;
        auto d = planeEq.d;
        return (norm * pos - d) / (norm * (pos - dir));
    }
    [[nodiscard]] Vec3 getPlaneIntersectionPoint(const Vec3& pos, const Vec3& dir) const {
        float t = getT(pos, dir);
        if (t>=1) {
            return (1 - t) * pos + t * dir;
        }
        else return { FLT_MAX,0,0};
    }
    [[nodiscard]] bool intersects(Ray& ray) const override {
        auto I = getPlaneIntersectionPoint(ray.getPos(), ray.getDir());
        if (I.x() ==  FLT_MAX) {
            return false;
        }
        if (I.isNan()) {
            return false;
        }

        float d = det(P1(), P2(), P3());

        if ((((det(I, P2(), P3()) / d)) < 0)){
            return false;}
        if ((((det(P1(), I, P3()) / d)) < 0 ))
            return false;
        if ((((det(P1(), P2(), I) / d)) < 0))
            return false;
        ray.setClosestDist(this, (ray.getDir() - I).norm());
        return true;
    }
};

#endif // TRIANGLE_H



