//
// Created by ADMIN on 19-Mar-23.
//

#include "Camera.h"
Camera::Camera(Vec3 topLeft, Vec3 bottomLeft, Vec3 topRight,
               int wPixels, int hPixels, float fov,  std::vector<std::vector<float>>& screen, std::vector<Triangle>& triangles):
               topLeft{topLeft}, fov{fov}, wPixels{wPixels}, hPixels{hPixels}, screen{screen}, triangles{triangles} {
//    setDelta()
    deltaXDirection = (topLeft-topRight)/(float)wPixels;
    deltaYDirection = (topLeft-bottomLeft)/(float)hPixels;
    setFocalPoint(bottomLeft, topRight); // if doesn`t work change for sqrt
    std::cout << focalPoint<<std::endl;
}
void Camera::setFocalPoint(Vec3& bottomLeft, Vec3& topRight){
    Vec3 crPr = (deltaXDirection).cross(deltaYDirection);
    float t = fov/(crPr * crPr);
    focalPoint = -sqrt(t) * crPr + (topRight + bottomLeft)/2 ; // if doesn`t work change for sqrt
}