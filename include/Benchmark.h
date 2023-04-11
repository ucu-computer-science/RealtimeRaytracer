// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// http://www.viva64.com
#ifndef RAYTRACER_BENCHMARK_H
#define RAYTRACER_BENCHMARK_H

#include "Camera.h"
#include <atomic>
#include <chrono>
#include <vector>

#include <algorithm>
// #include "statslib"
#include "Vec3.h"
// #include "DirectXMath.h"
//
// namespace dx = DirectX;
namespace Benchmark {
inline std::chrono::high_resolution_clock::time_point
get_current_time_fenced() {
  std::atomic_thread_fence(std::memory_order_seq_cst);
  auto res_time = std::chrono::high_resolution_clock::now();
  std::atomic_thread_fence(std::memory_order_seq_cst);
  return res_time;
}

template <class D> inline long long to_ms(const D &d) {
  return std::chrono::duration_cast<std::chrono::milliseconds>(d).count();
}

void benchmark(int ntimes);
void show_stats(std::vector<long long> &timeMeasurments, int ntimes);
;
//    std::vector<long long> measure_time(int n, int wPixels, int hPixels);
std::vector<long long> measure_time_our_vector(int);
std::vector<long long> measure_time_dx_vector(int);
std::vector<long long> measure_time_glm_vector(int);

void benchmarkVectors(int ntimes);
;
}; // namespace Benchmark

void measure_time();
#endif // RAYTRACER_BENCHMARK_H