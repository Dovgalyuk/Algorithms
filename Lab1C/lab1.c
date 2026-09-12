#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include "array.h"

Array* array_create_and_read(FILE* input)
{
    int n;
    if (fscanf(input, "%d", &n) != 1) return NULL;

    Array* arr = array_create(n, NULL);
    for (int i = 0; i < n; ++i)
    {
        int x;
        if (fscanf(input, "%d", &x) == 1) {
            array_set(arr, i, x);
        }
    }
    return arr;
}

static Data factorial(Data n)
{
    if (n <= 1) return 1;
    Data res = 1;
    for (Data i = 2; i <= n; ++i) {
        res *= i;
    }
    return res;
}

void task1(Array* arr)
{
    if (!arr) return;

    size_t size = array_size(arr);
    for (size_t i = 0; i < size; ++i) {
        Data val = array_get(arr, i);
        array_set(arr, i, factorial(val));
    }

    for (size_t i = 0; i < size; ++i) {
        printf("%zu ", (size_t)array_get(arr, i));
    }
    printf("\n");
}

void task2(Array* arr)
{
    if (!arr) return;

    size_t size = array_size(arr);
    bool first = true;

    for (size_t i = 0; i < size; ++i) {
        Data val_i = array_get(arr, i);
        bool is_indivisible = true;

        for (size_t j = 0; j < size; ++j) {
            if (i == j) continue;
            Data val_j = array_get(arr, j);
            if (val_j != 0 && val_i % val_j == 0) {
                is_indivisible = false;
                break;
            }
        }

        if (is_indivisible) {
            if (!first) printf(" ");
            printf("%zu", (size_t)val_i);
            first = false;
        }
    }
    printf("\n");
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        return 1;
    }

    FILE* input = fopen(argv[1], "r");
    if (!input) {
        return 1;
    }

    Array* arr = NULL;

    arr = array_create_and_read(input);
    if (arr) {
        task1(arr);
        array_delete(arr);
    }

    arr = array_create_and_read(input);
    if (arr) {
        task2(arr);
        array_delete(arr);
    }

    fclose(input);
    return 0;
}
