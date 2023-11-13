#include "array.h"

struct Array
{
    // Data *arr;
    // size_t size;
    void *some_variable; // need to success build finish
};

// create array
Array *array_create(size_t size)
{
    // Array *arr = new Array();
    // arr->arr = new Data[size];
    // arr->size = size;
    // return arr;
    return nullptr;
}

// delete array, free memory
void array_delete(Array *arr)
{
    // delete arr->arr;
    // delete arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    return 0; // arr->arr[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    // arr->arr[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return 0; // arr->size;
}
