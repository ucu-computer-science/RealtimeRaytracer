// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Camera.h"
Camera::Camera(Vec3 topLeft, Vec3 bottomLeft, Vec3 topRight,
               int wPixels, int hPixels, float fov,  std::vector<std::vector<float>>& screen, graphicalObjectVector& objectVector):
        topLeft{topLeft}, fov{fov}, wPixels{wPixels}, hPixels{hPixels}, screen{screen}, objectVector{objectVector} {
//    setDelta()
    deltaXDirection = (topLeft-topRight)/(float)wPixels;
    deltaYDirection = (topLeft-bottomLeft)/(float)hPixels;
    setFocalPoint(); // if doesn`t work change for sqrt
}
void Camera::setFocalPoint(){
    Vec3 crPr = (deltaXDirection).cross(deltaYDirection);
    float t = fov/(crPr * crPr);
    focalPoint = -sqrt(t) * crPr - ((deltaXDirection)*(float)wPixels + (deltaYDirection)*(float)hPixels)/2 + topLeft ; // if doesn`t work change for sqrt
}
//void Camera::setFocalPoint(float nfov){
//    Vec3 crPr = (deltaXDirection).cross(deltaYDirection);
//    fov = nfov;
//    float t = fov/(crPr * crPr);
//    focalPoint = -sqrt(t) * crPr + ((deltaXDirection)*(float)wPixels + (deltaYDirection)(float)hPixels)/2 ; // if doesn`t work change for sqrt
//}