#include "array.h"
#include <cassert>

struct Array
{
    Data *data;
    size_t size;
};

// create array
Array *array_create(size_t size)
{
    Array *arr = new Array;
    arr->size = size;
    arr->data = new Data[size];
    return arr;
}

// delete array, free memory
void array_delete(Array *arr)
{
    if (arr) {
        delete[] arr->data;
        delete arr;
    }
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    assert(arr && index < arr->size);
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    assert(arr && index < arr->size);
    arr->data[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    assert(arr);
    return arr->size;
}
