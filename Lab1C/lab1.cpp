#include <cstdio>
#include "array.h"

Array* array_create_and_read(FILE* input) {
    int n;
    fscanf(input, "%d", &n);
    Array* arr = array_create(n);
    for (int i = 0; i < n; ++i) {
        int x;
        fscanf(input, "%d", &x);
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array* arr) {
    size_t n = array_size(arr);
    if (n == 0) { printf("0.000000\n"); return; }
    double sum = 0.0;
    for (size_t i = 0; i < n; ++i) {
        int r = array_get(arr, i);
        if (r <= 0) { printf("Error\n"); return; }
        sum += 1.0 / r;
    }
    printf("%.6f\n", 1.0 / sum);
}

void task2(Array* arr) {
    size_t n = array_size(arr);
    if (n == 0) { printf("\n"); return; }
    size_t i = 0;
    while (i < n) {
        int val = array_get(arr, i);
        int count = 1;
        while (i + count < n && array_get(arr, i + count) == val)
            count++;
        printf("(%d,%d) ", val, count);
        i += count;
    }
    printf("\n");
}

int main(int argc, char** argv) {
    FILE* input = fopen(argv[1], "r");
    Array* arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);
    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);
    fclose(input);
    return 0;
}