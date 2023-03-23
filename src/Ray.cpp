// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Ray.h"
#include "Triangle.h"

void Ray::setClosestDist(const Triangle* triangle, float distance) {
    closestDist = std::min(closestDist, distance);
    if (closestDist == distance) {
        closestTriangle = triangle;
    }
}

Ray::Ray(Vec3 pos, Vec3 dir)
        : pos{pos }, dir{dir }, closestDist{FLT_MAX}, closestTriangle(nullptr) {
}
