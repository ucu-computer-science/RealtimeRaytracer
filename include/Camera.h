// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include <iostream>
#include "Vec3.h"
#include <math.h>
#include "Ray.h"
#include "GraphicalObject.h"
#include "Triangle.h"
#include <vector>
class Camera {
    Vec3 topLeft;
    float fov;
    Vec3 focalPoint;
    Vec3 deltaXDirection, deltaYDirection;
    int wPixels, hPixels;
    std::vector<std::vector<float>>& screen;
    graphicalObjectVector& objectVector;

public:
    Camera(Vec3 topLeft, Vec3 bottomLeft, Vec3 topRight,
           int wPixels, int hPixels, float fov, std::vector<std::vector<float>>& screen, graphicalObjectVector& objectVector);
    void setFocalPoint();
//    void setDelta(Vec3& bottomLeft, Vec3& topRight);

    void update() {
        for (int i = 0; i < hPixels; ++i) {
            for (int j = 0; j < wPixels; ++j) {
                Ray ray{focalPoint, (-(((float) j) * deltaXDirection + ((float) i) * deltaYDirection) + topLeft)};
//                std::cout<<(((float)j)*deltaXDirection +((float)i)*deltaYDirection)<<std::endl;
                screen[i][j] = 0;
                for (auto &t: objectVector) {
//                    std::cout<< ray.intersects(t) << std::endl;
//                    if (i==5){
//                        int a = 0;
//                    };
                    screen[i][j] = screen[i][j] || t->intersects(ray);

                }
            }
        }
    };
    void setFov(float new_fov) {
        fov = new_fov;
        setFocalPoint();
    };
    void moveX(float x){
        topLeft += {x,0,0};
        setFocalPoint();
    }
    void moveY(float y){
        topLeft += {0,y,0};
        setFocalPoint();
    }
    void moveZ(float z){
        topLeft += {0,0,z};
        setFocalPoint();
    }

};


#endif //RAYTRACER_CAMERA_H
