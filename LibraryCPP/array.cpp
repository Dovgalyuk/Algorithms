#include "array.h"

struct Array
{
    size_t array_size;
    Data* pointer;

    void create(size_t size)
    {
        array_size = size;
        pointer = new Data[array_size];
    }
};

// create array
Array* array_create(size_t size)
{
    Array* pointer = new Array;
    pointer->create(size);
    return pointer;
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