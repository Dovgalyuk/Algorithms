#include "array.h"
#include <cstdlib>

Array* array_create(size_t size)
{
    Array* arr = new Array;
    arr->size = size;
    arr->data = new Data[size];
    arr->free_fn = nullptr;

    for (size_t i = 0; i < size; i++)
        arr->data[i] = nullptr;

    return arr;
}

void array_delete(Array* arr)
{
    if (!arr) return;

    if (arr->free_fn)
    {
        for (size_t i = 0; i < arr->size; i++)
        {
            if (arr->data[i])
                arr->free_fn(arr->data[i]);
        }
    }

    delete[] arr->data;
    delete arr;
}

Data array_get(const Array* arr, size_t index)
{
    return arr->data[index];
}

void array_set(Array* arr, size_t index, Data value)
{
    arr->data[index] = value;
}

size_t array_size(const Array* arr)
{
    return arr->size;
}
