#include "array.h"

struct Array
{
    Data* array;
    size_t size;
    Array(size_t size) : size(size), array(new Data[size]) {}
};

// create array
Array *array_create(size_t size)
{
    return new Array(size);
}

// delete array, free memory
void array_delete(Array *arr)
{
    delete arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    return arr->array[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    arr->array[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr->size;
}
