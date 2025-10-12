#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include "array.h"
#include <iostream>
using namespace std;

Array* array_create_and_read(FILE* input)
{
    size_t n;
    fscanf(input, "%zu", &n);
    Array* arr = array_create(n);
    for (size_t i = 0; i < n; ++i)
    {
        Data x;
        fscanf(input, "%d", &x);
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array* arr)
{
    int CountEven = 0;
    for (size_t i = 0; i < array_size(arr); ++i)
    {
        if (array_get(arr, i) % 2 == 0) {
            CountEven += 1;
        }
    }
    
    Array* arrEven = nullptr;
    arrEven = array_create(CountEven);
    int arrEvenI = 0;

    for (size_t i = 0; i < array_size(arr); ++i)
    {
        if (array_get(arr, i) % 2 == 0) {
             array_set(arrEven, arrEvenI, i);
             arrEvenI += 1;
        }
    }
}

void task2(Array* arr)
{
    int a, b;
    printf("Enter interval [a, b] to remove elements: ");
    scanf("%d %d", &a, &b);
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }

    size_t write_index = 0;
    for (size_t read_index = 0; read_index < array_size(arr); ++read_index)
    {
        Data current = array_get(arr, read_index);
        if (current < a || current > b)
        {
            array_set(arr, write_index, current);
            write_index++;
        }
    }

    for (size_t i = write_index; i < array_size(arr); ++i)
    {
        array_set(arr, i, 0);
    }

    for (size_t i = 0; i < array_size(arr); ++i)
    {
        printf("%d ", array_get(arr, i));
    }
    printf("\n");

}

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    Array* arr = nullptr;
    FILE* input = fopen(argv[1], "r");

    if (input == nullptr) {
        printf("Error: Cannot open file %s\n", argv[1]);
        return 1;
    }

    arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);

    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);

    fclose(input);
    return 0;
}
