
cmake_minimum_required (VERSION 3.8)
set(CXX_STANDARD 14)

project ("RayTracer")

include_directories(include)

add_executable (RayTracer src/main.cpp "src/Vec3.cpp" src/Triangle.cpp src/Ray.cpp)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RayTracer PROPERTY CXX_STANDARD 20)
endif()