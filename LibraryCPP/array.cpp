#include "array.h"
#include <cassert>
#include <cstddef>

struct Array
{
    size_t size;  
    Data* data;
    FFree* free_fn;
};

// create array
Array *array_create(size_t size, FFree* free_fn)
{
    Array* arr = new Array;
    arr->size = size;
    arr->data = new Data[size];
    arr->free_fn = free_fn;
    for (size_t i = 0; i < size; ++i)
        arr->data[i] = (Data)0;
    
    return arr;
}

// delete array, free memory
void array_delete(Array *arr)
{
    
    if (arr->free_fn)
        for (size_t i = 0; i < arr->size; ++i)
            arr->free_fn(arr->data[i]);
    delete[] arr->data;
    delete arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    assert(arr != nullptr);
    assert(index < arr->size);
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    assert(arr != nullptr);
    assert(index < arr->size);
    arr->data[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    assert(arr != nullptr);
    return arr->size;
}
