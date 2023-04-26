// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// http://www.viva64.com
#include "Benchmark.h"
#include "GraphicalObject.h"
#include "Light.h"
#include "immintrin.h"
#include <cmath>
// #include "SDLDisplayer.h"
#include "Triangle.h"
#include "glm/gtx/string_cast.hpp"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "MathExtensions.h"
// void Benchmark::benchmark(int ntimes)
//{
//	auto timeMeasurments = measure_time(ntimes, 1920, 1080);
//	show_stats(timeMeasurments, ntimes);
//	//        return
//{timeMeasurments.at(std::distance(timeMeasurments.begin(), result)), mean, sd}
// }

// void Benchmark::show_stats(std::vector<long long int>& timeMeasurments, int
// ntimes)
//{
//	auto result = std::min_element(timeMeasurments.begin(),
//timeMeasurments.end()); 	long long sum = 0; 	for (auto i : timeMeasurments)
//	{
//		sum += i;
//	}
//	double mean = ((double)sum) / ntimes;
//
//	double var = 0;
//	for (auto i : timeMeasurments)
//	{
//		var += ((double)i - mean) * ((double)i - mean);
//	}
//	double sd = sqrt(var / (ntimes - 1));
//
//
//
//	std::cout << "Min=" <<
//timeMeasurments.at(std::distance(timeMeasurments.begin(), result)) <<
//std::endl; 	std::cout << "Mean=" << mean << std::endl; 	std::cout << "Sd=" << sd
//<< std::endl;
// }

void measure_time() {
  //  std::vector<long long> time_measurments;
  int ntimes = 100;
  constexpr float fov = 1;
  int width = 640 * 2, height = 360 * 2;

  Camera camera{{0, -38, 0}, fov, glm::vec2((float)width / (float)height, 1)};

  Light light3{{0, 0, 8}, {255 / 255.0f, 236 / 255.0f, 156 / 255.0f},
               35,        1,
               {0, 0, 0}, {1, 1, 1}};

  Square sq{{0, 0, 9.9999f}, {{-90 * DEG_TO_RAD, 0, 0}}, 5};
  sq.setColor({3, 3, 3});
  Plane plane1{{-10, 0, 0}, {1, 0, 0}, Color::red()};
  Plane plane2{{10, 0, 0}, {-1, 0, 0}, Color::green()};
  Plane plane3{{0, 0, 10}, {0, 0, -1}, Color::white()};
  Plane plane4{{0, 0, -10}, {0, 0, 1}, Color::white()};
  Plane plane5{{0, 10, 0}, {0, -1, 0}, Color::white()};
  Plane plane6{{0, -10, 0}, {0, 1, 0}, Color::white()};
  Cube cube1{glm::vec3{4, -4, -6.7},
             {{0 * DEG_TO_RAD, 0 * DEG_TO_RAD, -28 * DEG_TO_RAD}},
             6.6f};
  Sphere sphere1{{-4, 2, -5}, 5, Color::skyBlue()};
  cube1.setColor(Color::skyBlue());
  cube1.setReflection(0.3f);
  sphere1.setReflection(0.3f);
  plane1.setReflection(0);
  plane2.setReflection(0);
  auto pixels = new uint32_t[height * width];
  const int pitch = width * sizeof(uint32_t);
  //      while (true)
  //      {
  ////        onUpdate();
  //        Camera::instance->updatePixelMatrix(pixels, width, height);
  //      }

  for (int i = 0; i < ntimes; ++i) {
    //		auto start_time = get_current_time_fenced();
    Camera::instance->updatePixelMatrix(pixels, width, height);
    //		auto finish_time = get_current_time_fenced();
    //		auto total_time = finish_time - start_time;
    //		time_measurments.push_back(to_ms(total_time));
  }
  delete[] pixels;

  //	return time_measurments;
}

// void Benchmark::benchmarkVectors(int ntimes)
//{
//	auto res1 = measure_time_our_vector(ntimes);
//	show_stats(res1, ntimes);
//
//	//auto res2 = measure_time_dx_vector(ntimes);
//	//show_stats(res2, ntimes);
//	auto res3 = measure_time_glm_vector(ntimes);
//	show_stats(res3, ntimes);
// }

// std::vector<long long> Benchmark::measure_time_our_vector(int ntimes)
//{
//	std::vector<long long> time_measurments;
//
//	for (int m = 0; m < ntimes; ++m)
//	{
//		auto start_time = get_current_time_fenced();
//		Vec3 v1(1.1, 1.1, 1.1);
//		for (int k = 0; k < 10'000'000; ++k)
//		{
//			v1 = (2.f * v1) + v1;
//			v1 = v1 - (v1 / 2.f);
//		}
//		auto finish_time = get_current_time_fenced();
//		auto total_time = finish_time - start_time;
//		time_measurments.push_back(to_ms(total_time));
//		//std::cout << v1;
////		std::cout << (v1);
//	}
//	std::cout << std::endl;
//
//	return time_measurments;
//}

// std::vector<long long> Benchmark::measure_time_dx_vector(int ntimes)
//{
//	std::vector<long long> time_measurments;
//	//
//	//    for (int m = 0; m < ntimes; ++m) {
//	//        auto start_time = get_current_time_fenced();
//	//        dx::XMFLOAT3 p {1.1, 1.1, 1.1};
//	//        for (int k = 0; k < 10'000'000; ++k) {
//	//            auto v2 = dx::XMLoadFloat3(&p);
//	//            v2 = dx::XMVectorAdd(v2,v2);
//	//            dx::XMStoreFloat3(&p, v2);
//	//
//	//        }
//	//
//	//        auto finish_time = get_current_time_fenced();
//	//        auto total_time = finish_time - start_time;
//	//        time_measurments.push_back(to_ms(total_time));
//	//        std::cout << p.x<< p.y<< p.z;
//	//    }
//	//    std::cout  << std::endl;
//	return time_measurments;
// }
// std::vector<long long> Benchmark::measure_time_glm_vector(int ntimes)
//{
//	std::vector<long long> time_measurments;
//
//	for (int m = 0; m < ntimes; ++m)
//	{
//		auto start_time = get_current_time_fenced();
//		glm::vec3 v1(1.1, 1.1, 1.1);
//		for (int k = 0; k < 10'000'000; ++k)
//		{
//			v1 = (2.f * v1) + v1;
//			v1 = v1 - (v1 / 2.f);
//		}
//		auto finish_time = get_current_time_fenced();
//		auto total_time = finish_time - start_time;
//		time_measurments.push_back(to_ms(total_time));
//		std::cout << glm::to_string(v1);
//	}
//	std::cout << std::endl;
//
//	return time_measurments;
// }

#include <benchmark/benchmark.h>

static void BM_updatePixelMatrix(benchmark::State &state) {
  //  if (state.thread_index() == 0) {
  //    int ntimes = 1000;
  constexpr float fov = 1;
  int width = state.range(0), height = state.range(1);
  Camera camera{{0, -38, 0}, fov, glm::vec2((float)width / (float)height, 1)};

  Light light3{{0, 0, 8}, {255 / 255.0f, 236 / 255.0f, 156 / 255.0f},
               35,        1,
               {0, 0, 0}, {1, 1, 1}};

  Square sq{{0, 0, 9.9999f}, {{-90 * DEG_TO_RAD, 0, 0}}, 5};
  sq.setColor({3, 3, 3});
  Plane plane1{{-10, 0, 0}, {1, 0, 0}, Color::red()};
  Plane plane2{{10, 0, 0}, {-1, 0, 0}, Color::green()};
  Plane plane3{{0, 0, 10}, {0, 0, -1}, Color::white()};
  Plane plane4{{0, 0, -10}, {0, 0, 1}, Color::white()};
  Plane plane5{{0, 10, 0}, {0, -1, 0}, Color::white()};
  Plane plane6{{0, -10, 0}, {0, 1, 0}, Color::white()};
  Cube cube1{glm::vec3{4, -4, -6.7},
             {{0 * DEG_TO_RAD, 0 * DEG_TO_RAD, -28 * DEG_TO_RAD}},
             6.6f};
  Sphere sphere1{{-4, 2, -5}, 5, Color::skyBlue()};
  cube1.setColor(Color::skyBlue());
  cube1.setReflection(0.3f);
  sphere1.setReflection(0.3f);
  //    plane1.setReflection(0);
  //    plane2.setReflection(0);
  auto pixels = new uint32_t[height * width];
  //  }
  // Perform setup here
  for (auto _ : state) {
    // This code gets timed
    //    measure_time();
    //    for (int i = 0; i < ntimes; ++i)
    //    {
    camera.updatePixelMatrix(pixels, width, height);
    //      state.bytes_processed();
    //      state.KeepRunning();
    //    }
  }
  //  if (state.thread_index() == 0) {
  // Teardown code here.
  delete[] pixels;

  //  }
}
// Register the function as a benchmark
BENCHMARK(BM_updatePixelMatrix)->Args({640, 360});
// Run the benchmark
BENCHMARK_MAIN();
// int main(){
//
////  Benchmark::benchmark(1000);
////  float r3data[8] = {10,10,10,0,12,12,12,12};
////  float dirdata[8] = {2,2,2,1,2,2,2,1};
////  float resdata[8];
////  float resdata4[4];
////  float res5data4[8];
////
////
////  __m256 r3;
////  __m256 dir;
////
////  r3 = _mm256_load_ps(r3data);
////  dir = _mm256_load_ps(dirdata);
////
////  r3 = _mm256_mul_ps(r3, dir);
////
////  __m128 res0 = _mm256_extractf32x4_ps(r3, 0);
//////  _mm_testc_ps()
////  __m256 res5 = _mm256_cmp_ps(r3, _mm256_setzero_ps(), 0);
////
////      _mm256_store_ps(resdata, res5);
//////      _mm256_store_ps(resdata, r3);
////  _mm_store_ps(resdata4, res0);
////  for (int i = 0; i < 8; ++i) {
////    printf("%f ", resdata[i]);
////  }
////  printf("\n");
////  for (int i = 0; i < 4; ++i) {
////    printf("%f ", resdata4[i]);
////  }
// printf("%llu", sizeof(Triangle));
//   //  auto res = Benchmark::measure_time_our_vector(1000);
////  Benchmark::show_stats(res, 100);
//
//  return 0;
//}