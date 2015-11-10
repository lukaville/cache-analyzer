#include <functional>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include "result.h"
#include "benchmark.cpp"

void start_benchmark(std::function<Result*(double, double)> benchmark_function, std::string file) {
    std::ofstream out(file);
    out << "{ \"data\": [";

    int min_size_bytes = 1024;
    int max_size_bytes = 1024 * 1024 * 8;
    int times = max_size_bytes * 4;
    float step = 1.1;

    for(float i = min_size_bytes; i < max_size_bytes; i *= step) {
        Result* result = measure(times, i);
        out << "{\"point\": " << result->point << ", \"value\": " << result->value;

        if (i * step > max_size_bytes) {
            out << "}";
        } else {
            out << "},";
        }

        printf("%f %f\n", result->point, result->value);
    }

    out << "]}";
    out.close();
}

int main() {
    start_benchmark(measure, "www/data.json");
    system("./open_graph.sh");
}
