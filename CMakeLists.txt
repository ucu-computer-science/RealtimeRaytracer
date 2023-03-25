
cmake_minimum_required (VERSION 3.8)
set(CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_LIBRARY c:/msys64/mingw64/lib/libstdc++.a)

project ("RayTracer")

include_directories(include)
include_directories(include/Math)
include_directories(include/Object)
include_directories(include/Object/GraphicalObject)
include_directories(include/Raycast)
include_directories(glm)

add_executable (${PROJECT_NAME}  src/Math/Vec3.cpp src/Math/Vec2.cpp src/Math/Vec2Int.cpp  src/main.cpp
"src/Object/GraphicalObject.cpp" "src/Object/Object.cpp" "src/Ray/Ray.cpp" "src/Ray/Raycast.cpp" "src/Camera.cpp" "src/SDL_runner.cpp" "src/Scene.cpp" "src/Input.cpp"   )


find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL_PKG REQUIRED IMPORTED_TARGET sdl2)
target_link_libraries(RayTracer PUBLIC PkgConfig::SDL_PKG)

#[[find_package(SDL2 REQUIRED)
INCLUDE_DIRECTORIES(${PROJECT_NAME} "${SDL2_INCLUDE_DIR}")
target_link_libraries(${PROJECT_NAME} "${SDL2_LIBRARIES}")]]

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME}  PROPERTY CXX_STANDARD 20)
endif()