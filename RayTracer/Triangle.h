#pragma once
#ifndef RAY_TRACING_TRIANGLE_H
#define RAY_TRACING_TRIANGLE_H
#include "Vector.h"
//float detC(Vector& v1, Vector& v2, Vector& v3) {
//}
//float detR(Vector& v1, Vector& v2, Vector& v3) {
//}





class Triangle {

    struct PlaneEq{
        Vector norm;
        float d;
        PlaneEq(Vector norm, float d): norm{norm}, d{d} {};
        ~PlaneEq() = default;
    };


    Vector P1, P2, P3;
    PlaneEq planeEq;
    [[nodiscard]] float det(const Vector& v1, const Vector& v2, const Vector& v3) const;
    [[nodiscard]] PlaneEq calcPlaneEq() const{
        return  {(P2-P1).xPr(P3-P1), det(P1, P2-P1, P3-P1)} ;
    }
public:
    Triangle(Vector P1, Vector P2, Vector P3): P1{P1}, P2{P2}, P3{P3}, planeEq{calcPlaneEq()}{};
    ~Triangle() = default;
    [[nodiscard]] const PlaneEq& getPlaneEq() const{
        return planeEq;
    }
    [[nodiscard]] const Vector& getP1() const {
        return P1;
    }
    [[nodiscard]] const Vector& getP2() const {
        return P2;
    }
    [[nodiscard]] const Vector& getP3() const {
        return P3;
    }



};
#endif