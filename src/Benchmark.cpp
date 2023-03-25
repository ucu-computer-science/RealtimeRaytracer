// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Benchmark.h"
#include "GraphicalObject.h"
#include <cmath>

#include "Triangle.h"
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/gtx/string_cast.hpp"
void Benchmark::benchmark(int ntimes) {
    auto timeMeasurments = measure_time(ntimes, 1920, 1080);
    show_stats(timeMeasurments, ntimes);
//        return {timeMeasurments.at(std::distance(timeMeasurments.begin(), result)), mean, sd}


}

void Benchmark::show_stats(std::vector<long long int> &timeMeasurments, int ntimes) {
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



    std::cout << "Min=" << timeMeasurments.at(std::distance(timeMeasurments.begin(), result)) << std::endl;
    std::cout << "Mean=" << mean << std::endl;
    std::cout << "Sd=" << sd << std::endl;
}

std::vector<long long> Benchmark::measure_time(int ntimes, int wPixels, int hPixels) {
    std::vector<long long> time_measurments;
    auto screen = std::vector(hPixels, std::vector<float>(wPixels, 0));
    constexpr float fov = 1;
    glm::vec2 screenResolution{ wPixels, hPixels };
    glm::vec2 cameraSize{ 2, 1 };

    Camera camera{ { 0.5, 0, 0.5 }, fov, screenResolution, cameraSize };
    GraphicalObject obj{ glm::vec3{ 1, 1, 1 } };
    //Square (Vec3(1, 1, 1), Vec3(1, 1, 1),
    //          Vec3(-1, 1, 1),
    //          Vec3(0, 3, -1), Color::cyan());
    //Square t2(Vec3(1, 1, 1), Vec3(1, 1, 1),
    //          Vec3(-1, 1, 1),
    //          Vec3(-1, 4, 1), Color::magenta());

    Triangle t3(glm::vec3(1, 1, 1),
        glm::vec3(-1, 1, 1),
        glm::vec3(0, 3, -1), Color::white());
    //Triangle t4({ 1, 1, 1 }, { 0, 3, -1 }, { -1,  4, 1 }, Color::white());
    Triangle t4(glm::vec3(1, 1, 1),
        glm::vec3(3, 1, 0),
        glm::vec3(0, 3, -1), Color::white());

    //Square t1{ Vec3(1, 1, 1), Vec3(0.2, 1, 0.8), Vec3(0.8, 1, 0.5), Color::cyan() };
    //Square t2{Vec3(1, 1, 1), Vec3(1, 1, 0.8), Vec3(0.4, 1, 0.2), Color::magenta() };

    obj.triangles.emplace_back(&t3);
    obj.triangles.emplace_back(&t4);

    auto pixels = new uint32_t[wPixels  * hPixels];

    for (int i = 0; i < ntimes; ++i) {
        auto start_time = get_current_time_fenced();
        Camera::instance->updatePixelMatrix(pixels);
        auto finish_time = get_current_time_fenced();
        auto total_time = finish_time - start_time;
        time_measurments.push_back(to_ms(total_time));
    }
    delete[] pixels;
    return time_measurments;
}

void Benchmark::benchmarkVectors(int ntimes) {
    auto res1 = measure_time_our_vector(ntimes);
    show_stats(res1, ntimes);

    //auto res2 = measure_time_dx_vector(ntimes);
    //show_stats(res2, ntimes);
    auto res3 = measure_time_glm_vector(ntimes);
    show_stats(res3, ntimes);

}

std::vector<long long> Benchmark::measure_time_our_vector(int ntimes) {
    std::vector<long long> time_measurments;

    for (int m = 0; m < ntimes; ++m) {
        auto start_time = get_current_time_fenced();
        Vec3 v1 (1.1, 1.1, 1.1);
        for (int k = 0; k < 10'000'000; ++k) {
            v1 = (2.f * v1) + v1;
            v1 = v1 - (v1 / 2.f);
        }
        auto finish_time = get_current_time_fenced();
        auto total_time = finish_time - start_time;
        time_measurments.push_back(to_ms(total_time));
        //std::cout << v1;
        std::cout << (v1);

    }
    std::cout  << std::endl;

    return time_measurments;
}

std::vector<long long> Benchmark::measure_time_dx_vector(int ntimes) {
    std::vector<long long> time_measurments;
//
//    for (int m = 0; m < ntimes; ++m) {
//        auto start_time = get_current_time_fenced();
//        dx::XMFLOAT3 p {1.1, 1.1, 1.1};
//        for (int k = 0; k < 10'000'000; ++k) {
//            auto v2 = dx::XMLoadFloat3(&p);
//            v2 = dx::XMVectorAdd(v2,v2);
//            dx::XMStoreFloat3(&p, v2);
//
//        }
//
//        auto finish_time = get_current_time_fenced();
//        auto total_time = finish_time - start_time;
//        time_measurments.push_back(to_ms(total_time));
//        std::cout << p.x<< p.y<< p.z;
//    }
//    std::cout  << std::endl;
    return time_measurments;
}
std::vector<long long> Benchmark::measure_time_glm_vector(int ntimes)
{
    std::vector<long long> time_measurments;

    for (int m = 0; m < ntimes; ++m) {
        auto start_time = get_current_time_fenced();
        glm::vec3 v1(1.1, 1.1, 1.1);
        for (int k = 0; k < 10'000'000; ++k) {
            v1 = (2.f * v1 )+ v1;
            v1 = v1 - (v1 / 2.f);
        }
        auto finish_time = get_current_time_fenced();
        auto total_time = finish_time - start_time;
        time_measurments.push_back(to_ms(total_time));
        std::cout << glm::to_string(v1);

    }
    std::cout  << std::endl;

    return time_measurments;
}
