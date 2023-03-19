//
// Created by ADMIN on 19-Mar-23.
//

#ifndef RAY_TRACING_RAY_H
#define RAY_TRACING_RAY_H


#include "Vector.h"
#include "Triangle.h"

class Ray {

    Vector &C, &P;
    [[nodiscard]] float det(const Vector& v1, const Vector& v2, const Vector& v3) const;
public:
    Ray(Vector &C, Vector &P): C{C}, P{P}{}
    ~Ray() = default;
    [[nodiscard]] float getT(const Triangle& triangle) const{
        auto norm = triangle.getPlaneEq().norm;
        auto d = triangle.getPlaneEq().d;
        return (norm*C + d)/(norm*(C-P));
    }
    [[nodiscard]] Vector getPlaneIntersectionPoint(const Triangle& triangle) const {
        float t = getT(triangle);
        return (1-t)*C + t*P;
    }
    [[nodiscard]] bool intersects(const Triangle& triangle) const {
        auto I = getPlaneIntersectionPoint(triangle);

        float d = det(triangle.getP1(), triangle.getP2(), triangle.getP3());


        if (det(I, triangle.getP2(), triangle.getP3())/d < 0)
            return false;
        if (det(triangle.getP1(), I , triangle.getP3())/d < 0)
            return false;
        if (det(triangle.getP2(), triangle.getP2(), I)/d < 0)
            return false;
        return true;
    }
};


#endif //RAY_TRACING_RAY_H