#include "array.h"

struct Array
{
    size_t array_size;
    Data* pointer;
};

// create array
Array* array_create(size_t size)
{
    Array* ptr = new Array;
    ptr->array_size = size;
    ptr->pointer = new Data[size];
    return ptr;
}

// delete array, free memory
void array_delete(Array* arr)
{
    delete arr;
}

// returns specified array element
Data array_get(const Array* arr, size_t index)
{
    return arr->pointer[index];
}

// sets the specified array element to the value
void array_set(Array* arr, size_t index, Data value)
{
    arr->pointer[index] = value;
}

// returns array size
size_t array_size(const Array* arr)
{
    return arr->array_size;
}