#include <time.h>
#include <math.h>
#include <functional>
#include <fstream>

struct node {
    struct node *next;
};

#define ONE p = p->next;
#define FIVE ONE ONE ONE ONE ONE
#define TEN FIVE FIVE
#define FIFTY TEN TEN TEN TEN TEN
#define HUNDRED FIFTY FIFTY

Result* measure(int times, int bytes) {
    srand(time(NULL));
    struct node *array;
    int array_size = bytes / sizeof(struct node);
    array = new node[array_size];
    
    for(unsigned long i = 0; i < array_size; i++) {
        array[i].next = &array[(i + 34) % array_size];
    }
    
    struct node *p = &array[0];
    times /= 100;
    clock_t start = clock();
    for(int count = 0; count < times; count++) {
        HUNDRED
    }

    double timeTaken = (double)(clock() - start) / times * 1000; 

    delete[] array;
    return new Result(bytes / 1024.0, timeTaken);
}