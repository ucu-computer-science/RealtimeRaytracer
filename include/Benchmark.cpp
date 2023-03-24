// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Benchmark.h"



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



    std::cout << timeMeasurments.at(std::distance(timeMeasurments.begin(), result)) << std::endl;
    std::cout << mean << std::endl;
    std::cout << sd << std::endl;
}

std::vector<long long> Benchmark::measure_time(int ntimes, int wPixels, int hPixels) {
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

void Benchmark::benchmarkVectors(int ntimes) {
    auto res1 = measure_time_our_vector(ntimes);
    show_stats(res1, ntimes);

    auto res2 = measure_time_dx_vector(ntimes);
    show_stats(res2, ntimes);

}

std::vector<long long> Benchmark::measure_time_our_vector(int ntimes) {
    std::vector<long long> time_measurments;

    for (int m = 0; m < ntimes; ++m) {
        auto start_time = get_current_time_fenced();
        Vec3 v1 (1.1, 1.1, 1.1);
        for (int k = 0; k < 10'000'000; ++k) {
            v1 = v1 + v1;
        }
        auto finish_time = get_current_time_fenced();
        auto total_time = finish_time - start_time;
        time_measurments.push_back(to_ms(total_time));
        std::cout << v1;

    }
    std::cout  << std::endl;

    return time_measurments;
}

std::vector<long long> Benchmark::measure_time_dx_vector(int ntimes) {
    std::vector<long long> time_measurments;

    for (int m = 0; m < ntimes; ++m) {
        auto start_time = get_current_time_fenced();
        dx::XMFLOAT3 p {1.1, 1.1, 1.1};
        for (int k = 0; k < 10'000'000; ++k) {
            auto v2 = dx::XMLoadFloat3(&p);
            v2 = dx::XMVectorAdd(v2,v2);
            dx::XMStoreFloat3(&p, v2);

        }

        auto finish_time = get_current_time_fenced();
        auto total_time = finish_time - start_time;
        time_measurments.push_back(to_ms(total_time));
        std::cout << p.x<< p.y<< p.z;
    }
    std::cout  << std::endl;
    return time_measurments;
}
