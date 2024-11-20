#include "array.h"
#include <stdexcept>

struct Array
{
    size_t size;
    Data* element;
};

// create array
Array *array_create(size_t size)
{
    if (size == 0)
    {
        throw std::invalid_argument("The array size is zero, so no operations can be performed on it");
    }
    Array *arr = new Array;
    arr->size = size;
    arr->element = new Data[size];
    return arr;
}

// delete array, free memory
void array_delete(Array *arr)
{
    if (arr)
    {
        delete[] arr->element;
        delete arr;
    }
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    if (index >= arr->size)
    {
        throw std::out_of_range("The index is missing from this array");
    }
    return arr->element[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (index >= arr->size)
    {
        throw std::out_of_range("The index is missing from this array");
    }
    arr->element[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr->size;
}