rm build/Raytracer
cmake -S . -B build/ -G"Unix Makefiles"
make -C build
./build/RayTracer