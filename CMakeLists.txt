
cmake_minimum_required (VERSION 3.8)
set(CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_LIBRARY c:/msys64/mingw64/lib/libstdc++.a)
project ("RayTracer")

include_directories(include)
include_directories(include/Vector)
include_directories(include/Object)
include_directories(include/Raycast)

add_executable (RayTracer src/Vector/Vec3.cpp src/Vector/Vec2.cpp src/Vector/Vec2Int.cpp  src/main.cpp 
"src/Object/GraphicalObject.cpp" "src/Object/Object.cpp" "src/Ray/Ray.cpp" "src/Ray/Raycast.cpp" "src/Camera.cpp" "src/SDL_runner.cpp" "src/Scene.cpp" "include/Input.h" "src/Input.cpp" "include/Matrix.h"   "include/Square.h")

find_package(PkgConfig REQUIRED) 
pkg_check_modules(SDL_PKG REQUIRED IMPORTED_TARGET sdl2)

target_link_libraries(RayTracer PUBLIC PkgConfig::SDL_PKG)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RayTracer PROPERTY CXX_STANDARD 20)
endif()