#include "array.h"
#include <cstdlib>
#include <cstdio>
struct Array
{
    Data* data;
    size_t size;
};

Array* array_create(size_t size)
{
    Array* arr = new Array;
    arr->data = new Data[size];
    arr->size = size;
    return arr;
}

void array_delete(Array* arr)
{
    if (arr)
    {
        delete[] arr->data;
        delete arr;
    }
}

Data array_get(const Array* arr, size_t index)
{
    if (index >= arr->size) return (Data)0;
    return arr->data[index];
}

void array_set(Array* arr, size_t index, Data value)
{
    if (index >= arr->size) return; 
    arr->data[index] = value;
}

size_t array_size(const Array* arr)
{
    return arr ? arr->size : 0;
}
