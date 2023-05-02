
cmake_minimum_required(VERSION 3.18)
set(CXX_STANDARD 20)
set(PROFILING TRUE)
set(USING_VISUAL_STUDIO TRUE)
set(ENABLE_FAST_MATH ON)
project("RayTracer")

include(FetchContent)
include_directories(include)
include_directories(include/Math)
include_directories(include/Object)
include_directories(include/Object/GraphicalObject)
include_directories(include/Raycast)
include_directories(include/ObjectAppearance)
include_directories(include/Parsers)
include_directories(include/Physics)
include_directories(include/shaders)
include_directories(include/OpenGL)

include_directories(libs/thread_pool_light)
include_directories(include/UI)

include_directories(libs)
include_directories(libs/SDL2/include)
include_directories(libs/stb_image)
link_directories(libs/SDL2/lib/x64)
enable_testing()

add_executable(${PROJECT_NAME}
        "src/Raytracer.cpp"
        "src/Object/GraphicalObject.cpp"
        "src/Object/Object.cpp"
        "src/Ray/Raycast.cpp"
        "src/Object/Camera.cpp"
        "src/Input.cpp"
        "src/Object/Light.cpp"
        "src/Parsers/ObjectParser.cpp"
        "src/BoundingBoxes.cpp"
        "src/UI/Canvas.cpp"
        "src/Object/Triangle.cpp"
        "libs/stb_image/stb_image.h"
        "src/ObjectAppearance/Texture.cpp"
        "src/Parsers/SceneParser.cpp"
        "src/Object/PolyMesh.cpp"
        "include/Object/Vertex.h" 
        "src/Physics/Physics.cpp"
        "src/Utils.cpp"
        "src/UI/SDLHandler.cpp"
        "src/OpenGL/glad.c" 
        "src/OpenGL/Shader.cpp"
        "src/Logger.cpp" 
        "src/MyTime.cpp" 
        "src/OpenGL/RaytracerShader.cpp"
        "src/OpenGL/BufferController.cpp" 
        "src/ObjectAppearance/Material.cpp")

target_link_libraries(${PROJECT_NAME} SDL2)
target_link_libraries(${PROJECT_NAME} SDL2main)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif ()