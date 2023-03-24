// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef RAYTRACER_SQUARE_H
#define RAYTRACER_SQUARE_H


#include "GraphicalObject.h"
#include "Vec3.h"
#include "Triangle.h"

class Square: public GraphicalObject{
    Triangle ABC, BCD;
public:
    Square(Vec3 P1, Vec3 P2, Vec3 P3): ABC{P1, P2, P3}, BCD{P2, P3,  P2 + P3 - P1}
    {
        ;
        ;
    }
    ~Square() = default;
    [[nodiscard]] bool intersects(Ray& ray) const override{
        return ABC.intersects(ray) || BCD.intersects(ray);
    };


};


#endif //RAYTRACER_SQUARE_H
