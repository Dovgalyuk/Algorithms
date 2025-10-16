#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"

Array* array_create_and_read(FILE* input, int *a, int *b)
{
    int n;
    if (fscanf(input, "%d", &n) != 1) 
        return NULL;

    Array* arr = array_create(n, NULL);
    if (!arr) 
        return NULL;

    for (int i = 0; i < n; ++i) {
        int x;
        if (fscanf(input, "%d", &x) != 1) {
            array_delete(arr);
            return NULL;
        }
        array_set(arr, i, (Data)x);
    }

    if (fscanf(input, "%d %d", a, b) != 2) { 
        array_delete(arr);
        return NULL;
    }

    return arr;
}

void task1(Array* arr)
{
    int month_days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    size_t start = 0;

    for (int m = 0; m < 12; ++m) {
        Data sum = 0;
        for (size_t i = 0; i < (size_t)month_days[m] && start + i < array_size(arr); ++i) {
            sum += array_get(arr, start + i);
        }
        printf("%lu ", sum);
        start += month_days[m];
    }
    printf("\n");
}

void task2(Array* arr, int a, int b)
{
    size_t write_index = 0;
    size_t n = array_size(arr);

    for (size_t i = 0; i < n; ++i) {
        Data val = array_get(arr, i);
        if (val < (Data)a || val > (Data)b) {
            array_set(arr, write_index++, val);
        }
    }

    while (write_index < n) {
        array_set(arr, write_index++, 0);
    }

    for (size_t i = 0; i < n; ++i) {
        printf("%lu ", array_get(arr, i));
    }
    printf("\n");
}

int main(int argc, char** argv)
{
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input_file> <task1|task2>\n", argv[0]);
        return 1;
    }

    FILE* input = fopen(argv[1], "r");
    if (!input) {
        fprintf(stderr, "Error: cannot open input file %s\n", argv[1]);
        return 1;
    }

    int a, b;
    Array* arr = array_create_and_read(input, &a, &b);
    fclose(input);

    if (!arr) {
        fprintf(stderr, "Error: failed to read array\n");
        return 1;
    }

    if (strcmp(argv[2], "task1") == 0) {
        task1(arr);
    } else if (strcmp(argv[2], "task2") == 0) {
        task2(arr, a, b);
    } else {
        fprintf(stderr, "Error: unknown task name '%s'\n", argv[2]);
        array_delete(arr);
        return 1;
    }

    array_delete(arr);
    return 0;
}
