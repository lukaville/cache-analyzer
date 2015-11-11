#include <functional>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include "benchmark.cpp"

const int COLOR_RED = 31;
const int COLOR_GREEN = 32;
const int COLOR_YELLOW = 33;
const int COLOR_BLUE = 34;
const int COLORS[] = {COLOR_RED, COLOR_GREEN, COLOR_YELLOW, COLOR_BLUE}; 

typedef std::function<double(int, int)> BenchmarkFunction;

void print_progress(double kilobytes, double current, double maximum, int color) {
    printf("%07.2f %07.1f ", kilobytes, current);

    int progress_width = 70;
    int progress = current / maximum * progress_width;

    printf("[\033[%dm", color);
    for (int i = 0; i < progress_width; ++i) {
        if (i <= progress) {
            printf("=");
        } else {
            printf(" ");
        }
    }
    printf("\033[0m]\n");
}

void start_benchmarks(std::vector<BenchmarkFunction> benchmarks, std::string file) {
    std::ofstream out(file);
    out << "{ \"data\": [";

    int min_size_bytes = 1024;
    int max_size_bytes = 1024 * 1024 * 8;
    int times = max_size_bytes / 100 / 2;
    double step = 1.1;

    for(double bytes = min_size_bytes; bytes < max_size_bytes; bytes *= step) {
        double kilobytes = bytes / 1024;
        
        out << "{\"point\": " << kilobytes;
        for(int i = 0; i < benchmarks.size(); ++i) {
            double time = benchmarks.at(i)(times, bytes);
            out << ", \"value" << i << "\": " << time;
            print_progress(kilobytes, time, 25300.0, COLORS[i]);
        }

        if (bytes * step > max_size_bytes) {
            out << "}";
        } else {
            out << "},";
        }
    }

    out << "]}";
    out.close();
}

int main() {
    std::vector<BenchmarkFunction> benchmarks;
    benchmarks.push_back(get_benchmark_sequence_34);
    benchmarks.push_back(get_benchmark_random);
    benchmarks.push_back(get_benchmark_sequence);
    start_benchmarks(benchmarks, "www/data.json");
    system("./open_graph.sh");
}
