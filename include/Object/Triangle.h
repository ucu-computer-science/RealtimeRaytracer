#pragma once
#ifndef RAYTRACER_TRIANGLE_H
#define RAYTRACER_TRIANGLE_H
#include "Color.h"
#include "Ray.h"
#include "glm/geometric.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glm/vec3.hpp"
#include <iostream>
class Triangle {
  struct PlaneEq {
    glm::vec3 norm;
    float d;

    PlaneEq(glm::vec3 norm, float d) : norm{norm}, d{d} {}
  };

  PlaneEq calcPlaneEq(bool normalize) const {
    glm::vec3 normal = cross(p2 - p1, p3 - p1);
    return {normalize ? glm::normalize(normal) : normal, dot(normal, p1)};
  }
  int64_t filler{};

public:
  glm::vec3 p1, p2, p3;
  PlaneEq planeEq;
  Color color;
  float reflection;
  bool isTwoSided;

  // precalculated
  glm::vec3 row1{};
  glm::vec3 row2{};
  glm::vec3 row3{};
  float valRow1{};
  float valRow2{};
  float valRow3{};

  void recalculateValues() {
    auto e1 = p2 - p1;
    auto e2 = p3 - p1;
    auto normal = calcPlaneEq(false).norm;

    // Depending on which component of the normal is largest, calculate
    // coefficients:
    if (fabs(normal.x) > fabs(normal.y) && fabs(normal.x) > fabs(normal.z)) {
      row1 = {0.0f, e2.z / normal.x, -e2.y / normal.x};
      valRow1 = cross(p3, p1).x / normal.x;
      row2 = {0.0f, -e1.z / normal.x, e1.y / normal.x};
      valRow2 = -cross(p2, p1).x / normal.x;
      row3 = {1.0f, normal.y / normal.x, normal.z / normal.x};
      valRow3 = -dot(p1, normal) / normal.x;
    } else if (fabs(normal.y) > fabs(normal.z)) {
      row1 = {-e2.z / normal.y, 0.0f, e2.x / normal.y};
      valRow1 = cross(p3, p1).y / normal.y;
      row2 = {e1.z / normal.y, 0.0f, -e1.x / normal.y};
      valRow2 = -cross(p2, p1).y / normal.y;
      row3 = {normal.x / normal.y, 1.0f, normal.z / normal.y};
      valRow3 = -dot(p1, normal) / normal.y;
    } else if (fabs(normal.z) > 0.0f) {
      row1 = {e2.y / normal.z, -e2.x / normal.z, 0.0f};
      valRow1 = cross(p3, p1).z / normal.z;
      row2 = {-e1.y / normal.z, e1.x / normal.z, 0.0f};
      valRow2 = -glm::cross(p2, p1).z / normal.z;
      row3 = {normal.x / normal.z, normal.y / normal.z, 1.0f};
      valRow3 = -dot(p1, normal) / normal.z;
    } else {
      // This triangle is degenerate. Set the transformation matrix to
      // the 0 matrix, which in turn will yield 0 values in places that
      // intersection calculations will detect and treat as a miss.
      row1 = {};
      valRow1 = 0.0f;
      row2 = {};
      valRow2 = 0.0f;
      row3 = {};
      valRow3 = 0.0f;
    }
  }
  void recalculatePlaneEq() { planeEq = calcPlaneEq(true); }
  Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3,
           Color color = Color::white(), bool isTwoSided = false)
      : p1{p1}, p2{p2}, p3{p3}, planeEq{calcPlaneEq(true)}, color{color},
        reflection{0}, isTwoSided(isTwoSided) {
    recalculateValues();
  }
  bool findIntersectionWith(Ray &ray) const {
    /*#ifdef CROSS_DOT_METHOD

          float t = getT(triangle);

          if (std::isnan(t) || t <= 0 || t >= closestT)
                  return false;
          auto P = pos + t * dir;
          //const auto edge0 = triangle->P2() - triangle->P1();
          if (const auto C0 = P - triangle->P1();
                  dot(triangle->getNorm(), cross(triangle->edge1, C0)) <= 0)
                  return false;

          //const auto edge1 = triangle->P3() - triangle->P2();
          if (const auto C1 = P - triangle->P2();
                  dot(triangle->getNorm(), cross(triangle->edge2, C1)) <= 0)
                  return false;

          //const auto edge2 = triangle->P1() - triangle->P3();
          if (const auto C2 = P - triangle->P3();
                  dot(triangle->getNorm(), cross(triangle->edge3, C2)) <= 0)
                  return false;

          closestT = t;
          closestTriangle = triangle;
          interPoint = &P;
          return true;
    #else //CROSS_DOT_METHOD
    #ifdef DET_METHOD
          float t = getT(triangle);

          if (std::isnan(t) || t <= 0 || t >= closestT)
                  return false;
          auto P = pos + t * dir;
          if (triangle->detSign > 0)
          {
                  if (triangle->optimizedDet(P, 1) < 0)
                          return false;
                  if (triangle->optimizedDet(P, 2) < 0)
                          return false;
                  if (triangle->optimizedDet(P, 3) < 0)
                          return false;
          }
          else if (triangle->detSign < 0)
          {
                  if (triangle->optimizedDet(P, 1) > 0)
                          return false;
                  if (triangle->optimizedDet(P, 2) > 0)
                          return false;
                  if (triangle->optimizedDet(P, 3) > 0)
                          return false;
          }
          else
          {
                  return false;
          }

          closestT = t;
          closestTriangle = triangle;
          interPoint = P;
          return true;

    #else
    #ifdef MOLLER_TRUMBORE_METHOD
          const float EPSILON = 0.0000001f;

          glm::vec3 h = cross(dir, (triangle->edge2));
          float a = dot(triangle->edge1, h);
          if (a > -EPSILON && a < EPSILON)
                  return false;    // This ray is parallel to this triangle.
          float f = 1.0f / a;
          glm::vec3 s = pos - triangle->P1();
          float u = f * dot(s, h);
          if (u < 0.0f || u > 1.0f)
                  return false;
          glm::vec3 q = cross(s, triangle->edge1);
          float v = f * dot(dir, q);
          if (v < 0.0f || u + v > 1.0f)
                  return false;
          // At this stage we can compute t to find out where the intersection
    point is on the line. float t = f * dot(triangle->edge2, q); if (t > EPSILON
    && closestT > t) // ray intersection
          {
                  //outIntersectionPoint = pos + dir * t;
                  closestT = t;
                  closestTriangle = triangle;
                  interPoint = pos + dir * t;
                  return true;
          }
          return true;
          //else // This means that there is a line intersection but not a ray
    intersection.
                  //return false;
      #else
       #ifdef BALDWIN_METHOD*/

    const float dz = dot(row3, ray.dir);

    if (dz == 0.0f)
      return false;

    const float oz = dot(row3, ray.pos) + valRow3;
    const float t = -oz / dz;

    if (t < 0 || ray.closestT < t || t >= ray.maxDist)
      return false;

    const auto hit = ray.pos + ray.dir * t;

    const float b1 = dot(row1, hit) + valRow1;

    if (b1 < 0.0f || b1 > 1.0f)
      return false;
    const float b2 = dot(row2, hit) + valRow2;

    if (b2 < 0.0f || b1 + b2 > 1.0f)
      return false;

    ray.closestT = t;
    ray.color = color;
    ray.surfaceNormal = planeEq.norm;
    ray.interPoint = hit;
    ray.reflection = reflection;
    return true;
  }
};

inline std::ostream &operator<<(std::ostream &os, const Triangle &t) {
  os << "Triangle(" << to_string(t.p1) << ", " << to_string(t.p2) << ", "
     << to_string(t.p3) << ")";
  return os;
}

#endif // RAYTRACER_TRIANGLE_H