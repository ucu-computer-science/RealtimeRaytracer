//
// Created by ADMIN on 22-Mar-23.
//

#ifndef RAYTRACER_BENCHMARK_H
#define RAYTRACER_BENCHMARK_H

#include <vector>
#include "Camera.h"
#include <chrono>
#include <algorithm>
//#include "statslib"
inline std::chrono::high_resolution_clock::time_point get_current_time_fenced()
{
    std::atomic_thread_fence(std::memory_order_seq_cst);
    auto res_time = std::chrono::high_resolution_clock::now();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    return res_time;
}


template<class D>
inline long long to_ms(const D& d)
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(d).count();
}

class Benchmark {
//    std::vector<std::vector<float>>& screen;
//    Camera& camera;
//    Benchmark(Camera& camera, std::vector<std::vector<float>>& screen): camera{camera}, screen{screen}{}
public:
    static void benchmark(int ntimes){
        auto timeMeasurments = measure_time(ntimes, 1920, 1080);

        auto result = std::min_element(timeMeasurments.begin(), timeMeasurments.end());
        long long sum = 0;
        for (auto i: timeMeasurments){
            sum+= i;
        }
        double mean = ((double)sum)/ntimes;

        double var = 0;
        for( auto i: timeMeasurments){
            var += ((double)i-mean)*((double)i-mean);
        }
        double sd = sqrt(var/(ntimes-1));



        std::cout << timeMeasurments.at(std::distance(timeMeasurments.begin(), result)) << std::endl;
        std::cout << mean << std::endl;
        std::cout << sd << std::endl;
//        return {timeMeasurments.at(std::distance(timeMeasurments.begin(), result)), mean, sd}


    }
    static std::vector<long long> measure_time(int ntimes, int wPixels, int hPixels){
        std::vector<long long> time_measurments;
        auto screen = std::vector(hPixels, std::vector<float>(wPixels, 0));
        graphicalObjectVector graphicalObjects;
        graphicalObjects.emplace_back(new  Triangle(Vec3(1, 1, 1),
                                                    Vec3(-1, 1, 1),
                                                    Vec3(0, 3, -1)));
        graphicalObjects.emplace_back(new Triangle(Vec3(1, 1, 1),
                                                   Vec3(3,1,0),
                                                   Vec3(0, 3, -1)));
        Camera camera(Vec3(-3, 1, 1),
                      Vec3(-3, 1, 0),
                      Vec3(-1, 1, 1), wPixels, hPixels, 0.1, screen, graphicalObjects);

        for (int i = 0; i < ntimes; ++i) {
            auto start_time = get_current_time_fenced();
            camera.update();
            auto finish_time = get_current_time_fenced();
            auto total_time = finish_time - start_time;
            time_measurments.push_back(to_ms(total_time));
        }
        return time_measurments;
    }
};


#endif //RAYTRACER_BENCHMARK_H
