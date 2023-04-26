
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
include_directories(libs)
include_directories(libs/SDL2/include)
include_directories(libs/stb_image)
link_directories(libs/SDL2/lib/x64)
enable_testing()

add_executable (${PROJECT_NAME} "src/main.cpp" "src/Object/GraphicalObject.cpp" "src/Object/Object.cpp"
        "src/Ray/Raycast.cpp" "src/Object/Camera.cpp" "src/SDLDisplayer.cpp"  "src/Input.cpp""src/Object/Light.cpp" 
        "src/Material.cpp" "include/Material.h" "src/ObjectParser.cpp" "src/BoundingBoxes.cpp"  "src/Canvas.cpp" "src/Object/Triangle.cpp" 
        "include/IBoundable.h" "libs/stb_image/stb_image.h" "src/Texture.cpp" "src/SceneParser.cpp")

target_link_libraries(${PROJECT_NAME} SDL2)
target_link_libraries(${PROJECT_NAME} SDL2main)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME}  PROPERTY CXX_STANDARD 20)
endif()