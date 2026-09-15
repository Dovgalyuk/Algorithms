
#include "array.h"

#include <stdexcept>

struct Array
{
    size_t size;
    Data* data;
};

// Create array.
Array* array_create(size_t size)
{
    Array* arr = new Array;

    arr->size = size;
    arr->data = new Data[size]();

    return arr;
}

// Delete array, free memory.
void array_delete(Array** arr)
{
    if (arr == nullptr || *arr == nullptr)
    {
        return;
    }

    delete[] (*arr)->data;
    delete *arr;

    *arr = nullptr;
}

// Returns specified array element.
Data array_get(const Array* arr, size_t index)
{
    if (arr == nullptr)
    {
        throw std::invalid_argument("Array is null");
    }

    if (index >= arr->size)
    {
        throw std::out_of_range("Array index out of range");
    }

    return arr->data[index];
}

// Sets the specified array element to the value.
void array_set(Array* arr, size_t index, Data value)
{
    if (arr == nullptr)
    {
        throw std::invalid_argument("Array is null");
    }

    if (index >= arr->size)
    {
        throw std::out_of_range("Array index out of range");
    }

    arr->data[index] = value;
}

// Returns array size.
size_t array_size(const Array* arr)
{
    if (arr == nullptr)
    {
        throw std::invalid_argument("Array is null");
    }

    return arr->size;
}
