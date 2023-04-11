#pragma once
#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H
#include <ostream>

#include "glm/common.hpp"
#include "glm/vec3.hpp"

class Color : public glm::vec3 {
public:
  Color(const float r, const float g, const float b) : glm::vec3(r, g, b) {}
  Color(int r, int g, int b)
      : glm::vec3((float)r / 255.f, (float)g / 255.f, (float)b / 255.f) {}
  Color() : Color{0, 0, 0} {}

  static Color white() { return {1.f, 1.f, 1.f}; }
  static Color black() { return {0.f, 0.f, 0.f}; }
  static Color red() { return {1.f, 0.f, 0.f}; }
  static Color green() { return {0.f, 1.f, 0.f}; }
  static Color blue() { return {0.f, 0.f, 1.f}; }
  static Color yellow() { return {1.f, 1.f, 0.f}; }
  static Color cyan() { return {0.f, 1.f, 1.f}; }
  static Color magenta() { return {1.f, 0.f, 1.f}; }
  static Color gray() { return {0.2f, 0.2f, 0.2f}; }

  static Color darkGreen() { return {0.f, 0.5f, 0.f}; }
  static Color skyBlue() { return {.529f, .808f, .922f}; }
  static Color gold() { return {1.f, .843f, 0.f}; }
  static Color pink() { return {255, 192, 203}; }
  static Color hotpink() { return {255, 105, 180}; }

  float r() const { return x; }
  float g() const { return y; }
  float b() const { return z; }

  Color &operator*=(float v) {
    x *= v;
    y *= v;
    z *= v;
    return *this;
  }
  Color &operator*=(Color c) {
    x *= c.x;
    y *= c.y;
    z *= c.z;
    return *this;
  }

  Color operator*(Color c) const { return {x * c.x, y * c.y, z * c.z}; }

  Color &operator+=(Color c) {
    x += c.x;
    y += c.y;
    z += c.z;
    return *this;
  }
  Color operator+(Color c) const { return {x + c.x, y + c.y, z + c.z}; }

  uint32_t toColor32() const {
    return ((int)(glm::clamp(r(), 0.0f, 1.0f) * 255) << 16) +
           ((int)(glm::clamp(g(), 0.0f, 1.0f) * 255) << 8) +
           ((int)(glm::clamp(b(), 0.0f, 1.0f) * 255) << 0);
  }
};

inline Color operator*(float v, Color c) { return {c.x * v, c.y * v, c.z * v}; }

inline Color operator*(Color c, float v) { return {c.x * v, c.y * v, c.z * v}; }

inline std::ostream &operator<<(std::ostream &os, const Color &c) {
  os << "(" << c.r() << ", " << c.g() << ", " << c.b() << ")";
  return os;
}
#endif // RAYTRACER_COLOR_H