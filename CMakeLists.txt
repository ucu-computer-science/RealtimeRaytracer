
cmake_minimum_required (VERSION 3.18)
set(CXX_STANDARD 20)
set(PROFILING TRUE)
set(USING_VISUAL_STUDIO TRUE)
set(ENABLE_FAST_MATH ON)
project ("RayTracer")

include(FetchContent)
include_directories(include)
include_directories(include/Math)
include_directories(include/Object)
include_directories(include/Object/GraphicalObject)
include_directories(include/Raycast)
include_directories(glm)
include_directories(SDL2/include)
link_directories(SDL2/lib/x64)
enable_testing()

add_executable (${PROJECT_NAME} "src/main.cpp" "src/Object/GraphicalObject.cpp" "src/Object/Object.cpp"
        "src/Ray/Raycast.cpp" "src/Object/Camera.cpp" "src/SDLDisplayer.cpp"  "src/Input.cpp" "src/Math/Vec3.cpp" "src/Object/Light.cpp" 
        src/Material.cpp include/Material.h src/ObjectParser.cpp "include/BoundingBoxes.h" )
add_executable (Benchmark "src/Benchmark.cpp" "src/Object/GraphicalObject.cpp" "src/Object/Object.cpp"
        "src/Ray/Raycast.cpp" "src/Object/Camera.cpp" "src/Math/Vec3.cpp" "src/Object/Light.cpp" "include/BoundingBoxes.h" )

# Externally provided libraries
FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.10.x)

FetchContent_Declare(googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG main) # need master for benchmark::benchmark

FetchContent_MakeAvailable(
        googletest
        googlebenchmark)

if(${USING_VISUAL_STUDIO})
  target_link_libraries(${PROJECT_NAME} SDL2)
  target_link_libraries(${PROJECT_NAME} SDL2main)
  target_link_libraries(Benchmark benchmark::benchmark)
else()
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(SDL_PKG REQUIRED IMPORTED_TARGET sdl2)
  target_link_libraries(RayTracer PUBLIC PkgConfig::SDL_PKG)
  set(CMAKE_BUILD_TYPE Release)
  set(CMAKE_CXX_FLAGS "-Wall -Wextra")
  set(CMAKE_CXX_FLAGS_DEBUG "	-g")
  set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()
#find_package(PkgConfig REQUIRED)
#pkg_check_modules(SDL_PKG REQUIRED IMPORTED_TARGET sdl2)
#target_link_libraries(RayTracer PUBLIC PkgConfig::SDL_PKG)
#find_package(SDL2 REQUIRED)
#INCLUDE_DIRECTORIES(${PROJECT_NAME} "${SDL2_INCLUDE_DIR}")
#target_link_libraries(${PROJECT_NAME} "${SDL2_LIBRARIES}")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Benchmark  PROPERTY CXX_STANDARD 20)
  set_property(TARGET ${PROJECT_NAME}  PROPERTY CXX_STANDARD 20)
endif()