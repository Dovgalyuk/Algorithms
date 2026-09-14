#include "array.h"

Array *array_create(size_t size)
{
    Array *arr = new Array;
    arr->size = size;
    arr->data = new int[size];
    for (size_t i = 0; i < size; i++) {
        arr->data[i] = 0;
    }
    return arr;
}

void array_delete(Array *arr)
{
    if (arr) {
        delete[] arr->data;
        delete arr;
    }
}

Data array_get(const Array *arr, size_t index)
{
    if (index < arr->size) {
        return arr->data[index];
    }
    return (Data)0;
}

void array_set(Array *arr, size_t index, Data value)
{
    if (index < arr->size) {
        arr->data[index] = value;
    }
}

size_t array_size(const Array *arr)
{
    return arr->size;
}