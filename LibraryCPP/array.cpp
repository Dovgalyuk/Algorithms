#include "array.h"
#include <stdexcept>

struct Array
{
};

Array* array_create(size_t size)
{
    Array* arr = new Array;
    arr->size = size;
    arr->data = new Data[size];
    return arr;
}

void array_delete(Array* arr)
{
    if (arr) {
        delete[] arr->data;
        delete arr;
    }
}

Data array_get(const Array* arr, size_t index)
{
    if (!arr || index >= arr->size) {
        throw std::out_of_range("Index out of range");
    }
    return arr->data[index];
}

void array_set(Array* arr, size_t index, Data value)
{
    if (!arr || index >= arr->size) {
        throw std::out_of_range("Index out of range");
    }
    arr->data[index] = value;
}

size_t array_size(const Array* arr)
{
    return arr ? arr->size : 0;
}