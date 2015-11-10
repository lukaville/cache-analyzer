#include <functional>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include "result.h"
#include "benchmark.cpp"

void print_progress(double current, double maximum) {
    int progress_width = 70;
    int progress = current / maximum * progress_width;
    printf("[\033[31m");
    for (int i = 0; i < progress_width; ++i) {
        if (i <= progress) {
            printf("=");
        } else {
            printf(" ");
        }
    }
    printf("\033[0m]");
}

void start_benchmark(std::function<Result*(double, double)> benchmark_function, std::string file) {
    std::ofstream out(file);
    out << "{ \"data\": [";

    int min_size_bytes = 1024;
    int max_size_bytes = 1024 * 1024 * 8;
    int times = max_size_bytes / 100;
    double step = 1.1;

    for(double i = min_size_bytes; i < max_size_bytes; i *= step) {
        Result* result = measure(times, i);
        out << "{\"point\": " << result->point << ", \"value\": " << result->value;

        if (i * step > max_size_bytes) {
            out << "}";
        } else {
            out << "},";
        }

        printf("%07.2f %07.1f ", result->point, result->value);
        print_progress(result->value, 25300.0);
        printf("\n");
    }

    out << "]}";
    out.close();
}

int main() {
    start_benchmark(measure, "www/data.json");
    system("./open_graph.sh");
}
