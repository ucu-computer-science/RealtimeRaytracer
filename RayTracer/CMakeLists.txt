# CMakeList.txt : CMake project for win32interraction, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CXX_STANDARD 14)
# Add source to this project's executable.
add_executable (RayTracer "main.cpp"  "Vector.cpp" "Vector.h" "Triangle.h" "Triangle.cpp" Ray.cpp Ray.h PixelPos.cpp PixelPos.h FocalPoint.cpp FocalPoint.h)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RayTracer PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
