#include <stdexcept>
#include "array.h"

struct Array
{
    size_t size;
    Data *data;
};

// create array
Array *array_create(size_t size)
{
    Array *arr = new Array;
    arr->size = size;
    arr->data = new Data[size]();
    return arr;
}

// delete array, free memory
void array_delete(Array *arr)
{
    if (arr == nullptr)
        return;
    delete[] arr->data;
    delete arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    if (index >= arr->size)
        throw std::out_of_range("array_get: index out of range");
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (index >= arr->size)
        throw std::out_of_range("array_set: index out of range");
    arr->data[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr->size;
}
