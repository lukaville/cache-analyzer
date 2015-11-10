#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <functional>
#include <fstream>

struct Result {
    double point;
    double value;

    Result(double point, double value) {
        this->point = point;
        this->value = value;
    }
};

long MICRO_IN_SECOND = 1000000;

int q = 0;
static volatile unsigned int    use_result_dummy;
void
use_pointer(void *result) { use_result_dummy += (long)result; }

struct pt {
    struct pt *next;
};

#define ONE p = p->next;
#define FIVE    ONE ONE ONE ONE ONE
#define TEN FIVE FIVE
#define FIFTY   TEN TEN TEN TEN TEN
#define HUNDRED FIFTY FIFTY

Result* measure(int ntimes, int bytes) {
    srand(time(NULL));
    struct pt *array;
    int arr_sz = bytes / sizeof(struct pt);
    array = new pt[arr_sz];
    
    unsigned long i = 0;
    
    for(i = 0; i < arr_sz; i++) {
        array[i].next = &array[(i+33)%arr_sz];
    }
    
    int count = 0;
    struct pt *p = &array[0];
    
    ntimes /= 100;
    clock_t start = clock();
    for(; count < ntimes; count++) {
        HUNDRED
    }

    double timeTaken = (double)(clock() - start) / ntimes * 1000; 
    delete[] array;
    return new Result(bytes / 1024.0, timeTaken);
}

void start_benchmark(std::function<Result*(double, double)> benchmark_function) {
    std::ofstream out("www/data.json");
    out << "{ \"data\": [";

    int min_size_bytes = 1024;
    int max_size_bytes = 2048 * 1024 * 3;
    for(float j = min_size_bytes; j < max_size_bytes; j *= 1.1) {
        int i = j;
        Result* result = measure(6 * max_size_bytes, i);
        out << "{\"point\": " << result->point << ", \"value\": " << result->value;

        if (j * 1.1 > max_size_bytes) {
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
    start_benchmark(measure);
}
