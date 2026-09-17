#include "array.h"

#include <cstdlib>

struct Array
{
    Data *data;
    size_t size;
};

namespace
{
    void check_index(const Array *arr, size_t index)
    {
        if (arr == nullptr || index >= arr->size)
        {
            std::abort();
        }
    }
}

// create array
Array *array_create(size_t size)
{
    Array *arr = new Array{nullptr, size};

    try
    {
        arr->data = new Data[size]();
    }
    catch (...)
    {
        delete arr;
        throw;
    }

    return arr;
}

// delete array, free memory
void array_delete(Array *arr)
{
    if (arr == nullptr)
    {
        return;
    }

    delete[] arr->data;
    delete arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    check_index(arr, index);
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    check_index(arr, index);
    arr->data[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    if (arr == nullptr)
    {
        std::abort();
    }

    return arr->size;
}