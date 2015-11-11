#include <time.h>
#include <math.h>
#include <functional>
#include <fstream>
#include <algorithm>

struct node {
    struct node *next;
};

#define ONE p = p->next;
#define FIVE ONE ONE ONE ONE ONE
#define TEN FIVE FIVE
#define FIFTY TEN TEN TEN TEN TEN
#define HUNDRED FIFTY FIFTY
#define THOUSAND HUNDRED HUNDRED HUNDRED HUNDRED HUNDRED HUNDRED HUNDRED HUNDRED HUNDRED HUNDRED

double get_benchmark_sequence_34(int times, int bytes) {
    struct node *array;
    int array_size = bytes / sizeof(struct node);
    array = new node[array_size];
    
    for(unsigned long i = 0; i < array_size; i++) {
        array[i].next = &array[(i + 34) % array_size];
    }
    
    struct node *p = &array[0];
    clock_t start = clock();
    for(int count = 0; count < times; count++) {
        THOUSAND
    }

    delete[] array;
    return (double)(clock() - start) / times * 1000;
}

double get_benchmark_sequence(int times, int bytes) {
    struct node *array;
    int array_size = bytes / sizeof(struct node);
    array = new node[array_size];
    
    for(unsigned long i = 0; i < array_size; i++) {
        array[i].next = &array[(i + 1) % array_size];
    }
    
    struct node *p = &array[0];
    clock_t start = clock();
    for(int count = 0; count < times; count++) {
        THOUSAND
    }

    delete[] array;
    return (double)(clock() - start) / times * 1000;
}

double get_benchmark_random(int times, int bytes) {
    struct node *array;
    int array_size = bytes / sizeof(struct node);

    std::vector<int> random_vector;
    for (int i = 0; i < array_size; ++i) {
        random_vector.push_back(i);
    }

    std::random_shuffle(random_vector.begin(), random_vector.end());

    array = new node[array_size];
    
    for(unsigned long i = 0; i < array_size; i++) {
        array[i].next = &array[random_vector.at(i)];
    }
    
    struct node *p = &array[0];
    clock_t start = clock();
    for(int count = 0; count < times; count++) {
        THOUSAND
    }

    delete[] array;
    return (double)(clock() - start) / times * 1000;
}