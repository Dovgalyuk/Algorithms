#include "array.h"
#include <cstddef>

int* array_create(int size)
{
    return new int[size];
}

void array_delete(int* arr)
{
    delete[] arr;
}

int array_get(const int* arr, int index)
{
    return arr[index];
}

void array_set(int* arr, int index, int value)
{
    arr[index] = value;
}

int array_size(const int*, int size)
{
    return size;
}
