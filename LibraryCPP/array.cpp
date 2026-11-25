#include "array.h"

struct Array
{
    Data* data;
    size_t size;
};

// create array
Array *array_create(size_t size)
{
    Array* arr = new Array;
    arr->size = size;
    arr->data = size ? new Data[size]() : nullptr;
    return arr;
}

// delete array, free memory
void array_delete(Array *arr)
{
    if (!arr) return;
    delete[] arr->data;
    delete arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    if (!arr || index >= arr->size)
        throw std::out_of_range("array_get: index out of range");
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (!arr || index >= arr->size)
        throw std::out_of_range("array_set: index out of range");
    arr->data[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr ? arr->size : 0;
}
