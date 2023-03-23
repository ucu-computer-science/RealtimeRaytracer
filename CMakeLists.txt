
cmake_minimum_required (VERSION 3.8)
set(CXX_STANDARD 17)

project ("RayTracer")
set(PROJECT_NAME RayTracer)

set(WARNINGS_AS_ERRORS OFF)
set(ENABLE_PVS_STUDIO OFF)
#! Select appropriate sanitizers.
#  Definitely enable sanitizers while developing.
#  Disable it for the production builds and before submitting for grading.
#  Only one of Memory (MSAN), Address (ASAN), or Thread (TSan)
#  sanitizers is applicable at the time -- the first defined.

#! UndefinedBehaviorSanitizer (UBSan)
#  Info: https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html
set(ENABLE_UBSan OFF)
#! AddressSanitizer -- detects use after free or after scope exit,
#  memory overflows and leaks.
#  Info: https://github.com/google/sanitizers/wiki/AddressSanitizer
set(ENABLE_ASAN OFF)
#! ThreadSanitizer -- detects data races.
set(ENABLE_TSan OFF)
#! MemorySanitizer detects uninitialized memory reads
#  Info: https://github.com/google/sanitizers/wiki/MemorySanitizer
set(ENABLE_MSAN OFF)
include_directories(include)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

#add_executable (RayTracer src/main.cpp "src/Vec3.cpp" src/Triangle.cpp src/Ray.cpp src/SDL_runner.cpp)
#
#find_package(SDL2 REQUIRED COMPONENTS SDL2)
#target_link_libraries(RayTracer PRIVATE SDL2::SDL2)
add_executable (${PROJECT_NAME} src/main.cpp "src/Vec3.cpp" src/Triangle.cpp src/Ray.cpp include/Camera.cpp include/Camera.h include/GraphicalObject.cpp include/GraphicalObject.h include/Square.cpp include/Square.h include/SimpleGraphicalObject.cpp include/SimpleGraphicalObject.h include/Benchmark.cpp include/Benchmark.h)

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads)
if (UNIX)
    find_package(Curses)
    target_link_libraries(${PROJECT_NAME} curses)
endif (UNIX)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET RayTracer PROPERTY CXX_STANDARD 20)
endif()

INSTALL(PROGRAMS
        $<TARGET_FILE:${PROJECT_NAME}>	# ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
        DESTINATION bin)

# Define ALL_TARGETS variable to use in PVS and Sanitizers
set(ALL_TARGETS ${PROJECT_NAME})

# Include CMake setup
include(cmake/main-config.cmake)