#include "array.h"
#include <cstddef>

Data* array_create(size_t size)
{
    return new Data[size];
}

void array_delete(Data* arr)
{
    delete[] arr;
}

Data array_get(const Data* arr, size_t index)
{
    return arr[index];
}

void array_set(Data* arr, size_t index, Data value)
{
    arr[index] = value;
}

size_t array_size(const Data*, size_t size)
{
    return size;
}
