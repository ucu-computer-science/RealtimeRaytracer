//
// Created by ADMIN on 19-Mar-23.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include <iostream>
#include "Vec3.h"
#include <math.h>
#include "Ray.h"
#include <vector>
class Camera {
    Vec3 topLeft;
    float fov;
    Vec3 focalPoint;
    Vec3 deltaXDirection, deltaYDirection;
    int wPixels, hPixels;
    std::vector<std::vector<float>>& screen;
    std::vector<Triangle>& triangles;

public:
    Camera(Vec3 topLeft, Vec3 bottomLeft, Vec3 topRight,
           int wPixels, int hPixels, float fov, std::vector<std::vector<float>>& screen, std::vector<Triangle>& triangles);
    void setFocalPoint(Vec3& bottomLeft, Vec3& topRight);
//    void setDelta(Vec3& bottomLeft, Vec3& topRight);

    void update() {
        for (int i = 0; i < hPixels; ++i) {
            for (int j = 0; j < wPixels; ++j) {
                Ray ray {focalPoint, (((float)j)*deltaXDirection +((float)i)*deltaYDirection + topLeft)};
                screen[i][j] = 0;
                for (auto &t: triangles) {
                    screen[i][j] = ray.intersects(t) || (bool) screen[i][j];

                }
            }
        }
    };
};


#endif //RAYTRACER_CAMERA_H
