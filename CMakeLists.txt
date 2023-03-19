
cmake_minimum_required (VERSION 3.8)
set(CXX_STANDARD 14)

project ("RayTracer")

include_directories(include)
include_directories(include/Vector)

add_executable (RayTracer src/Vector/Vec3.cpp src/Vector/Vec2.cpp src/Vector/Vec2Int.cpp src/Triangle.cpp 
				src/Ray.cpp src/Camera.cpp src/Screen.cpp src/PixelDisplayer.cpp src/main.cpp)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RayTracer PROPERTY CXX_STANDARD 20)
endif()
