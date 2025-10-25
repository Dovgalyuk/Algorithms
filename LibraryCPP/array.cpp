#include "array.h"

struct Array
{
    size_t size;
    Data* arr;
};

// create array
Array* array_create(size_t size)
{
    Array* new_array = new Array;
    new_array->size = size;
    new_array->arr = new Data[size];
    return new_array;
}

// delete array, free memory
void array_delete(Array *arr)
{
    delete[] arr->arr;
    delete arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    return arr->arr[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    arr->arr[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr->size;
}
