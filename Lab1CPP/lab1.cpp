#include <cstdio>
#include <stdexcept>
#include "array.h"

Array* array_create_and_read(FILE* input)
{
    int n;
    if (fscanf_s(input, "%d", &n) < 1) throw std::invalid_argument("Failed to read size");
    /* Create array */
    Array* arr = array_create(n);
    /* Read array data */
    for (int i = 0; i < n; ++i)
    {
        int x;
        if (fscanf_s(input, "%d", &x) < 1) throw std::invalid_argument("Failed to read number");
        array_set(arr, i, x);
    }

    return arr;
}

void task1(Array* arr)
{
    int sum1 = 0;
    int sum2 = 0;
    size_t size = array_size(arr);

    for (size_t index{ 0 }; index < size; ++index) {
        if (array_get(arr, index) > 20) {
            sum1 += (int)array_get(arr, index);
        }
        if (array_get(arr, index) < 50) {
            sum2 += (int)array_get(arr, index);
        }
    }
    if (sum1 > 100) {
        printf("A: True\n");
    }
    else {
        printf("A: False\n");
    }
    if (sum2 % 2 == 0) {
        printf("B: True\n");
    }
    else {
        printf("B: False\n");
    }
}

void task2(Array* arr)
{
    size_t size = array_size(arr);
    int koll = 0;
    for (size_t index{ 0 }; index < size; ++index) {
        for (size_t index1{ 0 }; index1 < size; ++index1) {
            if (index == index1) {
                continue;
            }
            else if (array_get(arr, index1) == array_get(arr, index)) {
                koll++;
            }
        }
        if (koll == 2) {
            printf("%d", (int)array_get(arr, index));
        }
    }
}

int main(int argc, char** argv)
{
    Array* arr = NULL;
    FILE* input;
    fopen_s(&input, argv[1], "r");
    argc = 0;
    arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);
    /* Create another array here */
    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);

    fclose(input);
    return 0;
}